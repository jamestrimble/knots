#include <stdio.h>
#include <stdlib.h>

#include "backtrack.h"

int main(int argc, char** argv) {
    if (argc<3) {
        printf("Usage: %s <number of crossings> <max crossing number to place>\n", argv[0]);
        exit(1);
    } else {
        int N = atoi(argv[1]); 
        if (N < 1 || N > MAX_N) {
            printf("Valid range for number of crossings is 1...%u\n", MAX_N);
            exit(1);
        }
        int max_i = atoi(argv[2]); 
        if (max_i < 1 || max_i >= N-1) {
            printf("Second argument must by >= 1 and < number of crossings-1\n");
            exit(1);
        }
        begin_partial_search_recursive(N, max_i);
    }
}
