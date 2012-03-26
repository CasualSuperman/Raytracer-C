# Makefile for raytracer.
# Robert Wertman
# 2012-03-21

#################           Set up global file lists           #################
GLOBALS = Makefile
MODULES = Alloc image list log main material model object plane projection sphere vector
SRCS = $(addprefix src/,$(addsuffix .c,$(MODULES)))
OBJS = $(addprefix obj/,$(addsuffix .o,$(MODULES)))

#################             Set up phony targets             #################
# Don't print the command being run.
.SILENT: clean
# Don't stop even if the targets fail.
.IGNORE: clean
# Don't look for files names after the targets.
.PHONY: all analyze clean nolink
# Don't look at all the default suffixes.
.SUFFIXES:

#################           Set up compilation flags           #################
# See if we have clang installed.
HAS_CLANG = $(shell \
  if which clang &> /dev/null; \
  then \
    echo "clang"; \
  else \
    echo "gcc"; \
  fi)

ifeq (clang, ${HAS_CLANG})
  CLANG_VER = $(shell \
  	clang -v 2>&1 | grep version | cut -f3 -d" " | cut -f1 -d. \
  )
  CC = clang -fcolor-diagnostics
  OPTIMIZE = -O0
  ANALYZE = $(CC) $(CMETA) $(INCLUDE) --analyze
  ifeq (3, ${CLANG_VER})
    WARN = -Weverything -Werror
  else
    WARN = -Weverything -Werror
  endif
else
  CC = gcc -fno-builtin
  WARN = -Wall -Wextra -Werror -pedantic -Wmissing-prototypes
  OPTIMIZE = -O2
  ANALYZE = splint $(INCLUDE) -weak
endif

# Add the include folder to the search path.
INCLUDE = -I include

# Things about C itself. Use the C99 standard.
CMETA = -std=c99

# Enable optimizations, debug and profile symbols, speed up the build, include
# math library.
CFLAGS = -march=native -pipe

PROFILE = -pg
DEBUG   = -g -O0

# All rolled into one.
LINK  = $(CC) $(OPTIMIZE) $(INCLUDE) $(CFLAGS) $(WARN) -lm
BUILD = $(CC) $(OPTIMIZE) $(INCLUDE) $(CFLAGS) $(WARN) $(CMETA)

#################         Actual Makefile targets list         #################
all: ray

ray: $(OBJS)
	-$(LINK) -lm -o ray $(OBJS) 2> main.err
	@if [[ "`du -s main.err | cut -f1`" == 0 ]]; \
	then \
		rm main.err; \
	else \
		cat main.err; \
	fi
	@if [[ -d err ]] || [[ -e main.err ]]; \
	then \
		echo "There were errors building the project."; \
	fi

debug: $(OBJS)
	-$(BUILD) $(DEBUG) -o ray $(OBJS)

nolink: analyze $(OBJS);

analyze:
	@$(ANALYZE) $(SRCS)
	@rm -f $(addsuffix .plist,$(MODULES))

# Build the .o file from the .c file, and don't link.
obj/%.o: src/%.c include/%.h $(GLOBALS)
	@mkdir -p obj err
	-$(BUILD) -c -o $@ $< 2> err/$*.err
	@if [[ "`du -s err/$*.err | cut -f1`" == 0 ]]; \
	then \
		rm err/$*.err; \
	else \
		cat err/$*.err; \
	fi
	@if [[ "`ls err`" == "" ]]; \
	then \
		rm -r err; \
	fi

clean:
	rm -rf obj/
	rm -rf err/
	rm -f main.err
	rm -f ray
	rm -f gmon.out
