CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude
SRC     = src/hawkalloc.c src/allocator.c src/arena.c
TESTDIR = tests

# ======================
# Default target
# ======================
all: tests stress

# ======================
# Unit tests
# ======================
tests: \
	test_malloc_basic \
	test_malloc_zero \
	test_free_null \
	test_calloc_zeroed \
	test_realloc_null \
	test_realloc_to_zero \
	test_realloc_grow_preserves \
	test_realloc_shrink_preserves_prefix

test_malloc_basic:
	$(CC) $(CFLAGS) $(TESTDIR)/test_malloc_basic.c $(SRC) -o $@

test_malloc_zero:
	$(CC) $(CFLAGS) $(TESTDIR)/test_malloc_zero.c $(SRC) -o $@

test_free_null:
	$(CC) $(CFLAGS) $(TESTDIR)/test_free_null.c $(SRC) -o $@

test_calloc_zeroed:
	$(CC) $(CFLAGS) $(TESTDIR)/test_calloc_zeroed.c $(SRC) -o $@

test_realloc_null:
	$(CC) $(CFLAGS) $(TESTDIR)/test_realloc_null.c $(SRC) -o $@

test_realloc_to_zero:
	$(CC) $(CFLAGS) $(TESTDIR)/test_realloc_to_zero.c $(SRC) -o $@

test_realloc_grow_preserves:
	$(CC) $(CFLAGS) $(TESTDIR)/test_realloc_grow_preserves.c $(SRC) -o $@

test_realloc_shrink_preserves_prefix:
	$(CC) $(CFLAGS) $(TESTDIR)/test_realloc_shrink_preserves_prefix.c $(SRC) -o $@

# ======================
# Stress tests
# ======================
stress: stress_test stress_test_v2

stress_test:
	$(CC) $(CFLAGS) $(TESTDIR)/stress_test.c  $(SRC) -o $@

stress_test_v2:
	$(CC) $(CFLAGS) $(TESTDIR)/stress_test_v2.c $(SRC) -o $@

# ======================
# Run all tests
# ======================
run-tests: tests
	./test_malloc_basic
	./test_malloc_zero
	./test_free_null
	./test_calloc_zeroed
	./test_realloc_null
	./test_realloc_to_zero
	./test_realloc_grow_preserves
	./test_realloc_shrink_preserves_prefix

run-stress: stress
	./stress_test
	./stress_test_v2

# ======================
# Cleanup
# ======================
clean:
	rm -f test_* stress_test_v2 stress_test
