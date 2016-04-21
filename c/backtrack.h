#include <stdio.h>
//#include <stdbool.h>
#include <string.h>

#define MAX_N 20

#define COLOUR_NONE 0
#define COLOUR_BLUE 1
#define COLOUR_RED 2

#define NONE -1

#define bool int
#define true 1
#define false 0

typedef int crossing;
typedef int colour;

int min(int i, int j) {
    return i<=j ? i : j;
}

bool is_connect_sum(crossing* code, int N) {
    bool is_used[MAX_N];
    for (int i=1; i<N*2-1; i++) {
        int n_used = 0;
        for (int j=0; j<N; j++) is_used[j] = false;
        for (int j=i; j<N*2-1; j++) {
            if (!is_used[code[j]]) {
                is_used[code[j]] = true;
                n_used += 1;
            }
            if (n_used*2 == j-i+1)
                return true;
        }
    }
    return false;
}

void swap_between_occurrences(crossing* code, crossing i) {
    int first_pos = 0;
    while (code[first_pos] != i) first_pos++;
    int second_pos = first_pos + 1;
    while (code[second_pos] != i) second_pos++;
    int gap = second_pos - first_pos - 1;
    for (int i=1; i<=gap/2; i++) {
        crossing tmp = code[first_pos + i];
        code[first_pos + i] = code[second_pos - i];
        code[second_pos - i] = tmp;
    }
}

void create_adj_mat(crossing* code, int N, bool* mat /*out*/) {
    memset(mat, 0, MAX_N*MAX_N*sizeof(bool));

    bool between[MAX_N];
    for (int i=0; i<N; i++)
        between[i] = false;

    for (int i=0; i<2*N-1; i++) {
        between[code[i]] = !between[code[i]];
        for (int j=0; j<N; j++) {
            if (between[j] && j!=code[i])
                mat[j*N + code[i]] = !mat[j*N + code[i]];
        }
    }
}

bool follow_edges(bool* mat, int N, colour* colours, int i) {
    for (int j=0; j<N; j++) {
        if (mat[i*N + j]) {
            if (colours[j]) { 
                if (colours[j]==colours[i]) return false;
            } else {
                colours[j] = 3 - colours[i]; // Blue if red; red if blue
                bool valid = follow_edges(mat, N, colours, j);
                if (!valid) return false;
            }
        }
    }
    return true;
}

bool is_bipartite(bool* mat, int N) {
    colour colours[N];
    for (int i=0; i<N; i++) colours[i] = COLOUR_NONE;
    for (int i=0; i<N; i++) {
        if (!colours[i]) {
            colours[i] = COLOUR_BLUE;
            bool valid = follow_edges(mat, N, colours, i);
            if (!valid) return false;
        }
    }
    return true;    
}

bool is_dually_paired(crossing* code_, int N) {
    crossing code[MAX_N*2];
    for (int i=0; i<N*2; i++) code[i] = code_[i];

    for (crossing i=0; i<N; i++) {
        swap_between_occurrences(code, i);
    }
    
    bool mat[MAX_N*MAX_N];

    create_adj_mat(code, N, mat);
    return is_bipartite(mat, N);
}

bool is_lex_leq_rotation(crossing* code, const int N, int p, int by) {
    // p is Position of second zero in code
    // by is Rotate-by
    if (code[(p+by)%(N*2)] != code[by%(N*2)]) return true;

    crossing old_to_new[N];
    for (int i=0; i<N; i++) old_to_new[i] = NONE;

    crossing i = 0;
    for (int j=0; j<N*2; j++) {
        crossing x = code[(j+by)%(2*N)];
        if (old_to_new[x] == NONE) {
            if (code[j] < i)
                return true;
            else if (code[j] > i)
                return false;
            old_to_new[x] = i;
            i++;
        } else {
            crossing new_num = old_to_new[x];
            if (code[j] < new_num)
                return true;
            else if (code[j] > new_num)
                return false;
        }
    }
    return true;
}

bool is_lex_leq_rev_rotation(crossing* code, int N, int p, int by) {
    // Is the code lex less than or equal to a rotation of the reversed-code?
    // Note: Signed numbers are used because of %
    // p is Position of second zero in code
    // by is Rotate-by


    int top = N*2-1; // Index of last element of array

    if (code[(top-p+by)%(N*2)] != code[(top+by)%(N*2)]) return true;

    crossing old_to_new[N];
    for (int i=0; i<N; i++) old_to_new[i] = NONE;

    crossing i = 0;
    // TODO: optimisation: finish one element earlier here and in is_lex_leq_rotation?
    for (int j=0; j<N*2; j++) {
        crossing x = code[(top-j+by)%(2*N)];
        if (old_to_new[x] == NONE) {
            if (code[j] < i)
                return true;
            else if (code[j] > i)
                return false;
            old_to_new[x] = i;
            i++;
        } else {
            crossing new_num = old_to_new[x];
            if (code[j] < new_num)
                return true;
            else if (code[j] > new_num)
                return false;
        }
    }
    return true;
}

bool is_lex_min_in_group_part_2(crossing* code, int N, int p) {
    /*
    for (int i=0; i<N*2; i++)
        if (!is_lex_leq_rev_rotation(code, N, p, i)) {
            printf("rev %d\n", i);
        }
    for (int i=1; i<N*2; i++)
        if (!is_lex_leq_rotation(code, N, p, i)) {
            printf("for %d\n", i);
        }
    */
    
    for (int i=0; i<4; i++)
        if (!is_lex_leq_rev_rotation(code, N, p, i)) return false;
    for (int i=1; i<N*2; i++)
        if (!is_lex_leq_rotation(code, N, p, i)) return false;
    return true;
}

bool is_lex_min_in_group_part_1(crossing* code, int N, int p) {
    
    /*
    for (int i=0; i<N*2; i++)
        if (!is_lex_leq_rev_rotation(code, N, p, i)) {
            printf("rev %d\n", i);
        }
    for (int i=1; i<N*2; i++)
        if (!is_lex_leq_rotation(code, N, p, i)) {
            printf("for %d\n", i);
        }
    */ 
    
    for (int i=4; i<N*2; i++)
        if (!is_lex_leq_rev_rotation(code, N, p, i)) return false;
    return true;
}

void print_code(crossing* code, int N) {
    for (int j=0; j<N*2; j += 2) {
        printf("%d %d ", code[j], code[j+1]);
    }
    printf("\n");
}

void search_recursive(crossing* code, int N, int i, int mpg) {
    // mpg is Min permissible gap
    
    // Find first empty position in code
    int first_empty = i;
    while (code[first_empty] != NONE) first_empty++;

    // Mustn't have connect sum in which first i*2 slots are already filled
    if (first_empty==i*2) return;

    code[first_empty] = i;

    // j is position of second occurrence of crossing i
    int j = first_empty + mpg + 1;

    if (j<N*2 && code[mpg+2]!=1 && i>1 && code[first_empty-1]==code[j-1])
        j += 2;

    while (j < N*2) {
        if (code[j] == NONE) {
            int gap = j - first_empty - 1;
            gap = min(gap, N*2-gap-2);
            if (gap >= mpg) {
                if (i==2 && mpg==2 && j==N*2-1 && code[4]!=1) {
                    // More symmetry breaking
                    j+=2;
                    continue;
                }
                code[j] = i;
                if (i < N-1) {
                    search_recursive(code, N, i+1, mpg);
                } else {
                    if (
                            is_lex_min_in_group_part_1(code, N, mpg+1) &&
                            is_dually_paired(code, N) &&
                            !is_connect_sum(code, N) &&
                            is_lex_min_in_group_part_2(code, N, mpg+1)
                            ) {
                        print_code(code, N);
                    }
                }
                code[j] = NONE;
            }
        }

        j += 2;
    }

    code[first_empty] = NONE;
}

void begin_search_recursive(int N) {
    crossing code[MAX_N*2];
    for (int i=1; i<N*2; i++) code[i] = NONE;
    code[0] = 0;
    int top = min(N+1, N*2-2);
    for (int j=3; j<top; j+=2) {
        code[j] = 0;
        search_recursive(code, N, 1, j-1);
        code[j] = NONE;
    }
}




/*************** Partial search *****************/

void partial_search_recursive(crossing* code, int N, int i, int mpg, int max_i) {
    // mpg is Min permissible gap
    
    // Find first empty position in code
    int first_empty = i;
    while (code[first_empty] != NONE) first_empty++;

    // Mustn't have connect sum in which first i*2 slots are already filled
    if (first_empty==i*2) return;

    code[first_empty] = i;

    // j is position of second occurrence of crossing i
    int j = first_empty + mpg + 1;

    if (j<N*2 && code[mpg+2]!=1 && i>1 && code[first_empty-1]==code[j-1])
        j += 2;

    while (j < N*2) {
        if (code[j] == NONE) {
            int gap = j - first_empty - 1;
            gap = min(gap, N*2-gap-2);
            if (gap >= mpg) {
                if (i==2 && mpg==2 && j==N*2-1 && code[4]!=1) {
                    // More symmetry breaking
                    j+=2;
                    continue;
                }
                code[j] = i;
                if (i < max_i) {
                    partial_search_recursive(code, N, i+1, mpg, max_i);
                } else {
                    printf("%d ", N);
                    print_code(code, N);
                }
                code[j] = NONE;
            }
        }

        j += 2;
    }

    code[first_empty] = NONE;
}

void begin_partial_search_recursive(int N, int max_i) {
    crossing code[MAX_N*2];
    for (int i=1; i<N*2; i++) code[i] = NONE;
    code[0] = 0;
    int top = min(N+1, N*2-2);
    for (int j=3; j<top; j+=2) {
        code[j] = 0;
        partial_search_recursive(code, N, 1, j-1, max_i);
        code[j] = NONE;
    }
}
