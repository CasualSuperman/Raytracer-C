# Makefile for raytracer.
# Robert Wertman
# 2012-03-21

#################           Set up global file lists           #################
GLOBALS = Makefile
FILES = Alloc list main model object
SRCS = $(addprefix src/,$(addsuffix .c,$(FILES)))
OBJS = $(addprefix obj/,$(addsuffix .o,$(FILES)))

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
	if which clang > /dev/null; \
	then \
		echo "clang"; \
	else \
		echo "gcc"; \
	fi)

ifeq (clang, ${HAS_CLANG})
CC = clang -fcolor-diagnostics
WARN = -Weverything -Werror
OPTIMIZE = -O4
ANALYZE = $(CC) --analyze
else
CC = gcc
WARN = -Wall -Wextra -Werror -pedantic -Wmissing-prototypes
OPTIMIZE = -O2
ANALYZE = splint $(CMETA) $(WARN) $(CFLAGS) -badflag
endif

# Things about C itself. Use the C99 standard, and add the include folder to
# the search path.
CMETA = -std=c99 -I include

# Enable optimizations, debug and profile symbols, speed up the build, include
# math library.
CFLAGS = -march=native -pipe

PROFILE        = -pg
DEBUG          = -g

# All rolled into one.
BUILD = $(CC) $(OPTIMIZE) $(CMETA) $(CFLAGS) $(WARN)

#################         Actual Makefile targets list         #################
all: ray

ray: $(OBJS)
	-$(BUILD) -lm -o ray $(OBJS) 2> main.err
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

nolink: $(OBJS);

analyze:
	$(ANALYZE) $(SRCS)

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
