CC=gcc
CFLAGS=-std=c99 -Wall -O2 -march=native

.PHONY: all
all: backtrack partial_search finish_search

backtrack_debug: backtrack.c backtrack.h
	$(CC) -o backtrack_debug $(CFLAGS) -g backtrack.c

backtrack: backtrack.c backtrack.h
	$(CC) -o backtrack $(CFLAGS) backtrack.c

partial_search: partial_search.c backtrack.h
	$(CC) -o partial_search $(CFLAGS) partial_search.c

finish_search: finish_search.c backtrack.h
	$(CC) -o finish_search $(CFLAGS) finish_search.c

test: test_backtrack
	./test_backtrack

test_backtrack: test_backtrack.c backtrack.h
	$(CC) -o test_backtrack $(CFLAGS) test_backtrack.c
    
