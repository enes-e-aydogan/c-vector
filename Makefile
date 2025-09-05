.PHONY: all analyze clean examples install memcheck tests

CC := gcc

CFLAGS := -std=c23 -pedantic -Wall -Wextra -Werror -Wformat=2 -Wformat-security -Wnull-dereference \
       -Wstack-protector -Warray-bounds=2 -Wimplicit-fallthrough=3 -Wtraditional-conversion \
       -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wstrict-overflow=2 \
       -Wstringop-overflow=4 -Winit-self -Wlogical-op -Wduplicated-cond -Wduplicated-branches \
       -Wfloat-equal -Wshadow=local -Wpointer-arith -Wcast-align=strict -Wstrict-aliasing=2 \
       -Wwrite-strings -Wdate-time -g3

SECURITY_FLAGS := -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fcf-protection
DEBUG_FLAGS := -O1 -DDEBUG -fsanitize=address -fsanitize=undefined

BUILDDIR := build
EXAMPLE := $(wildcard examples/*.c)
EXAMPLE_TARGETS := $(EXAMPLE:examples/%.c=$(BUILDDIR)/examples/%)
TEST := $(wildcard tests/*.c)
TEST_TARGETS := $(TEST:test/%.c=$(BUILDDIR)/test/%)

CFLAGS += $(DEBUG_FLAGS) $(SECURITY_FLAGS)

all: examples tests

examples: $(EXAMPLE_TARGETS)
tests: $(TEST_TARGETS)

$(BUILDDIR)/examples/%: examples/%.c cvector.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. $< -o $@

$(BUILDDIR)/tests/%: tests/%.c cvector.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. $< -o $@

analyze: examples tests
	cppcheck --enable=all --platform=unix64 \
		--suppress=missingIncludeSystem \
		-I. $(EXAMPLE) $(TEST)

memcheck: examples tests
	valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --verbose $(EXAMPLE_TARGETS) $(TEST_TARGETS)

clean:
	rm -rf $(BUILDDIR)/*

install:
	install -d /usr/local/include
	install -m 644 cvector.h /usr/local/include
