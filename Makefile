GLOBALS = Makefile
FILES = Alloc list
INCS = $(addprefix src/,$(addsuffix .h,$(FILES))) $(GLOBALS)
SRCS = $(addprefix src/,$(addsuffix .c,$(FILES))) $(GLOBALS)
OBJS = $(addprefix obj/,$(addsuffix .o,$(FILES))) $(GLOBALS)

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

obj/%.o: src/%.c include/%.h
	@# Build the .o file from the .c file, and don't link.
	$(BUILD) -c -o $@ $<

clean:
	rm -f bin/*
	rm -f obj/*
