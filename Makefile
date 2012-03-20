#!/usr/bin/make
# Makefile for raytracer.

#################           Set up global file lists           #################
GLOBALS = Makefile
FILES = Alloc list
INCS = $(addprefix src/,$(addsuffix .h,$(FILES)))
SRCS = $(addprefix src/,$(addsuffix .c,$(FILES)))
OBJS = $(addprefix obj/,$(addsuffix .o,$(FILES)))

#################             Set up phony targets             #################
# Don't print the command being run.
.SILENT: clean
# Don't stop even if the targets fail.
.IGNORE: clean
# Don't look for files names after the targets.
.PHONY: ray clean

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
ray: $(OBJS)
	-$(BUILD) -o ray main.c $(OBJS) 2> main.err
	@cat main.err

# Build the .o file from the .c file, and don't link.
obj/%.o: src/%.c include/%.h $(GLOBALS)
	-$(BUILD) -c -o $@ $< 2> err/$*.err
	@cat err/$*.err

clean:
	rm -f obj/*.o
	rm -f err/*.err
	rm -f main.err
