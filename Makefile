.PHONY: all analyze clean examples install memcheck tests

CC := gcc

CFLAGS := -std=c23 -Wall -Wextra -g -O1 -DDEBUG \
          -D_FORTIFY_SOURCE=2 -fstack-protector-strong \
          -fsanitize=address,undefined

BUILDDIR := build
EXAMPLE := $(wildcard examples/*.c)
EXAMPLE_TARGETS := $(EXAMPLE:examples/%.c=$(BUILDDIR)/examples/%)
TEST := $(wildcard tests/*.c)
TEST_TARGETS := $(TEST:test/%.c=$(BUILDDIR)/test/%)

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
