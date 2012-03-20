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
# Enable optimizations, debug symbols, speed up the build, include math library.
CFLAGS = -O2 -g -march=native -pipe -lm
# All rolled into one.
BUILD = $(CC) $(CFLAGS) $(WARN)

ray: $(OBJS)
	$(BUILD) -o bin/ray $(OBJS)

obj/%.o: src/%.c include/%.h $(GLOBALS)
	@# Build the .o file from the .c file, and don't link.
	$(BUILD) -c -o $@ $<

clean:
	rm -f bin/*
	rm -f obj/*
