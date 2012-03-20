GLOBALS = Makefile
FILES = Alloc list
INCS = $(addprefix src/,$(addsuffix .h,$(FILES)))
SRCS = $(addprefix src/,$(addsuffix .c,$(FILES)))
OBJS = $(addprefix obj/,$(addsuffix .o,$(FILES)))

# Avoid prefixing every command in clean.
.SILENT: clean
.PHONY: ray clean

# Use the C11 standard.
CC = gcc -std=c99

# Enable tons of warnings and make them errors. No GNU extensions.
WARN = -Wall -Wextra -Werror -pedantic -Wmissing-prototypes

# Enable optimizations, debug and profile symbols, speed up the build, include
# math library.
CFLAGS = -O2 -g -pg -march=native -pipe -lm

# All rolled into one.
BUILD = $(CC) $(CFLAGS) $(WARN)

ray: $(OBJS)
	-$(BUILD) -o ray $(OBJS) 2> main.err
	@cat main.err

# Build the .o file from the .c file, and don't link.
obj/%.o: src/%.c include/%.h $(GLOBALS)
	-$(BUILD) -c -o $@ $< 2> err/$*.err
	@cat err/$*.err

clean:
	rm -f obj/*.o
	rm -f err/*.err
	rm -f main.err
