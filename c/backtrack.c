#include <stdio.h>
#include <stdlib.h>

#include "backtrack.h"

int main(int argc, char** argv) {
    if (argc==1) {
        printf("Usage: %s <number of crossings>\n", argv[0]);
        exit(1);
    } else {
        unsigned N = atoi(argv[1]); 
        if (N < 1 || N > MAX_N) {
            printf("Valid range for number of crossings is 1...%u\n", MAX_N);
            exit(1);
        }
//        printf("%u\n", N);
        begin_search_recursive(N);
    }
}
