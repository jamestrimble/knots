#include <stdio.h>
#include <stdlib.h>

#include "backtrack.h"

int main(int argc, char** argv) {
    if (argc==1) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    } else {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (!fp) {
            printf("Could not open file.");
            exit(1);
        }

        int N;
        crossing code[MAX_N * 2];

        while (fscanf(fp, "%d", &N) == 1) {
            for (int i=0; i<N*2; i++) {
                if (1 != fscanf(fp, "%d", &(code[i]))) {
                    printf("Could not read code.");
                    exit(1);
                }
            }
            int max_i = 0;
            int position_of_second_0 = 0;
            for (int i=0; i<N*2; i++) {
                if (code[i] < NONE || code[i] >= N) {
                    printf("Crossing number outside valid range.\n");
                    exit(1);
                }
                if (code[i] > max_i) max_i = code[i];
                if (i>0 && code[i]==0) position_of_second_0 = i;
            }
            if (position_of_second_0==0) {
                printf("Code must contain two zeroes.\n");
                exit(1);
            }
            search_recursive(code, N, max_i+1, position_of_second_0-1);
        }
        fclose(fp);
    }
}
