# Makefile for raytracer.
# Robert Wertman
# 2012-03-21

#################           Set up global file lists           #################
GLOBALS = Makefile
MODULES = Alloc image list log main material model object plane projection \
		  raytracer sphere vector
DEBUG =
SRCS = $(addprefix src/,$(addsuffix .c,$(MODULES)))
OBJS = $(addprefix obj/,$(addsuffix .o,$(MODULES)))
DBGS = $(addprefix -DDEBUG_,$(DEBUG))

#################             Set up phony targets             #################
# Don't print the command being run.
.SILENT: analyze clean help
# Don't stop even if the targets fail.
.IGNORE: clean
# Don't look for files names after the targets.
.PHONY: all analyze clean debug help nolink profile
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

# If we do, use it.
ifeq (clang, ${HAS_CLANG})
    CC = clang -fcolor-diagnostics
    OPTIMIZE = -O4
    ANALYZE = $(CC) $(CMETA) $(INCLUDE) --analyze
    
    # See which version of clang we're using.
    CLANG_VER = $(shell \
    	clang -v 2>&1 | grep version | cut -f3 -d" " | cut -f1 -d. \
    )

    # If we're on an old version, we don't have -Weverything.
    ifeq (3, ${CLANG_VER})
        WARN = -Weverything -Werror
    else
        WARN = -Wall -Wextra -pedantic -Werror
    endif
else
    # Use boring, old gcc.
    CC = gcc -fno-builtin
    WARN = -Wall -Wextra -Werror -pedantic -Wmissing-prototypes
    OPTIMIZE = -O2
    ANALYZE = splint $(INCLUDE) -weak -fixedformalarray
endif

# Add the include folder to the search path.
INCLUDE = -I include

# Things about C itself. Use the C99 standard.
CMETA = -std=c99

# Enable optimizations, debug and profile symbols, speed up the build, include
# math library.
CFLAGS = -march=native -pipe

# Prifling information.
PROFILE = -pg
DEBUGS  = -g -O0 -ggdb

BUILD.debug = $(CC) -O0 $(INCLUDE) $(CMETA) $(WARN) $(DEBUGS) $(DBGS) -lm
BUILD.profile = $(CC) $(OPTIMIZE) $(INCLUDE) $(CMETA) $(WARN) $(PROFILE) -lm

# All rolled into one.
LINK  = $(CC) $(OPTIMIZE) $(INCLUDE) $(CFLAGS) $(WARN) $(DBGS) -lm
BUILD = $(CC) $(OPTIMIZE) $(INCLUDE) $(CFLAGS) $(WARN) $(CMETA)

#################         Actual Makefile targets list         #################
all: analyze ray

debug: clean
	-${BUILD.debug} -o ray $(SRCS)

profile: clean
	-${BUILD.profile} -o ray $(SRCS)

ray: $(OBJS)
	-$(LINK) -o ray $(OBJS) 2> main.err
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

nolink: analyze $(OBJS);

analyze:
	$(ANALYZE) $(SRCS)
	rm -f $(addsuffix .plist,$(MODULES))

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

help:
	cat .help
