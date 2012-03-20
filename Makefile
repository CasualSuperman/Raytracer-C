FILES = main list
SRCS = $(addprefix src/,$(addsuffix .c,$(FILES)))
OBJS = $(addprefix obj/,$(addsuffix .o,$(FILES)))

.SILENT: clean


# Use the C11 standard.
CC = gcc -std=c11
# Enable tons of warnings and make them errors. No GNU extensions.
WARN = -Wall -Wextra -Werror -pedantic -Wmissing-prototypes
# Enable optimizations, debug symbols, also speed up the build.
CFLAGS = -O2 -g -march=native -pipe
BUILD = $(CC) $(CFLAGS) $(WARN)

all: bin/ray
	@ echo "$(FILES)"
	@ echo "$(SRCS)"
	@ echo "$(OBJS)"

bin/ray: 

clean:
	@ rm -f bin/*
	@ rm -f obj/*
