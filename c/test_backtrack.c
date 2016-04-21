#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "backtrack.h"

void assert(bool x, char* message) {
    if (!x) {
        printf("%s\n", message);
        exit(1);
    }
}

void test_is_connect_sum() {
    assert(is_connect_sum((crossing[]) {0,0,2,3,1,1,2,3,4,4}, 5), "Connect sum_");
    assert(!is_connect_sum((crossing[]) {0,2,1,3,1,0,2,3}, 4), "Not connect sum");
    assert(is_connect_sum((crossing[]) {0,0,1,2,1,2,3,3}, 4), "Connect sum");
}

void test_swap_between_occurrences() {
    crossing code[] = {1,0,2,3,4,0,5};
    swap_between_occurrences(code, 0);
    crossing rev[] = {1,0,4,3,2,0,5};
    for (unsigned i=0; i<7; i++) {
        assert(code[i]==rev[i], "swap");
    }
    
    crossing code2[] = {1,0,2,3,0,4,5};
    swap_between_occurrences(code2, 0);
    crossing rev2[] = {1,0,3,2,0,4,5};
    for (unsigned i=0; i<7; i++) {
        assert(code2[i]==rev2[i], "swap");
    }
}

void test_create_adj_mat() {
    bool adj_mat[MAX_N*MAX_N];
    create_adj_mat((crossing[]) {0,1,0,1,2,2}, 3, adj_mat);
    assert(adj_mat[0*3 + 0]==false, "adjmat");
    assert(adj_mat[0*3 + 1]==true, "adjmat");
    assert(adj_mat[0*3 + 2]==false, "adjmat");
    assert(adj_mat[1*3 + 0]==true, "adjmat");
    assert(adj_mat[1*3 + 1]==false, "adjmat");
    assert(adj_mat[1*3 + 2]==false, "adjmat");
    assert(adj_mat[2*3 + 0]==false, "adjmat");
    assert(adj_mat[2*3 + 1]==false, "adjmat");
    assert(adj_mat[2*3 + 2]==false, "adjmat");
    bool adj_mat2[MAX_N*MAX_N];
    create_adj_mat((crossing[]) {0,1,2,0,1,2}, 3, adj_mat2);
    assert(adj_mat2[0*3 + 0]==false, "adjmat");
    assert(adj_mat2[0*3 + 1]==true, "adjmat");
    assert(adj_mat2[0*3 + 2]==true, "adjmat");
    assert(adj_mat2[1*3 + 0]==true, "adjmat");
    assert(adj_mat2[1*3 + 1]==false, "adjmat");
    assert(adj_mat2[1*3 + 2]==true, "adjmat");
    assert(adj_mat2[2*3 + 0]==true, "adjmat");
    assert(adj_mat2[2*3 + 1]==true, "adjmat");
    assert(adj_mat2[2*3 + 2]==false, "adjmat");
}

void test_is_bipartite() {
    bool adj_mat[] = {0, 1, 1,
                      1, 0, 1,
                      1, 1, 0};
    assert(!is_bipartite(adj_mat, 3), "not bipartite");

    bool adj_mat2[] = {0, 0, 1,
                       0, 0, 1,
                       1, 1, 0};
    assert(is_bipartite(adj_mat2, 3), "_bipartite");

    bool adj_mat3[] = {0, 0, 0, 0,
                       0, 0, 1, 1,
                       0, 1, 0, 1,
                       0, 1, 1, 0};
    assert(!is_bipartite(adj_mat3, 4), "not bipartite");

}

void test_is_lex_leq_rotation() {
    crossing code[] = {0, 1, 2, 0, 1, 2};
    assert(is_lex_leq_rotation(code, 3, 3, 0), "rotation");
    assert(is_lex_leq_rotation(code, 3, 3, 1), "rotation");
    assert(is_lex_leq_rotation(code, 3, 3, 2), "rotation");
    assert(is_lex_leq_rotation(code, 3, 3, 3), "rotation");
    crossing code2[] = {0, 2, 1, 0, 2, 1};
    assert(!is_lex_leq_rotation(code2, 3, 3, 0), "rotation");
    crossing code3[] = {0, 0, 1, 2, 1, 2, 3, 3};
    assert(is_lex_leq_rotation(code3, 4, 1, 0), "rotation");
    assert(is_lex_leq_rotation(code3, 4, 1, 1), "rotation");
    assert(!is_lex_leq_rotation(code3, 4, 1, 6), "rotation");
}

void test_is_lex_leq_rev_rotation() {
    crossing code[] = {0, 1, 2, 0, 1, 2};
    assert(is_lex_leq_rev_rotation(code, 3, 3, 0), "rev_rotation");
    assert(is_lex_leq_rev_rotation(code, 3, 3, 1), "rev_rotation");
    assert(is_lex_leq_rev_rotation(code, 3, 3, 2), "rev_rotation");
    assert(is_lex_leq_rev_rotation(code, 3, 3, 3), "rev_rotation");
    crossing code2[] = {0, 2, 1, 0, 2, 1};
    assert(!is_lex_leq_rev_rotation(code2, 3, 3, 0), "rev_rotation");
    crossing code3[] = {0, 0, 1, 2, 1, 2, 3, 3};
    assert(is_lex_leq_rev_rotation(code3, 4, 1, 0), "rev_rotation");
    assert(is_lex_leq_rev_rotation(code3, 4, 1, 1), "rev_rotation");
    assert(is_lex_leq_rev_rotation(code3, 4, 1, 6), "rev_rotation");
    assert(!is_lex_leq_rev_rotation(code3, 4, 1, 2), "rev_rotation");
}

int main() {
    test_is_connect_sum();
    test_swap_between_occurrences();
    test_create_adj_mat();
    test_is_bipartite();
    test_is_lex_leq_rotation();
    test_is_lex_leq_rev_rotation();
}
