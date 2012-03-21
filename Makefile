# Makefile for raytracer.
# Robert Wertman
# 2012-03-21

#################           Set up global file lists           #################
GLOBALS = Makefile
FILES = Alloc list main
OBJS = $(addprefix obj/,$(addsuffix .o,$(FILES)))

#################             Set up phony targets             #################
# Don't print the command being run.
.SILENT: clean
# Don't stop even if the targets fail.
.IGNORE: clean
# Don't look for files names after the targets.
.PHONY: all clean nolink
# Don't look at all the default suffixes.
.SUFFIXES:

#################           Set up compilation flags           #################
# Use the C99 standard. (I'd like to use C11, but our gcc doesn't support it)
# Also, add ./include/ to our include path so our #includes don't need to be
# relative.
CC = gcc -std=c99 -I include

# Enable tons of warnings and make them errors. No GNU extensions.
WARN = -Wall -Wextra -Werror -pedantic -Wmissing-prototypes

# Enable optimizations, debug and profile symbols, speed up the build, include
# math library.
CFLAGS = -O2 -g -pg -march=native -pipe -lm

# All rolled into one.
BUILD = $(CC) $(CFLAGS) $(WARN)

#################         Actual Makefile targets list         #################
all: ray

ray: $(OBJS)
	-$(BUILD) -o ray $(OBJS) 2> main.err
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
