from pprint import pprint
import datetime
import time
import sys

START_TIME = time.time()

def is_connect_sum(arr):
    arr_len = len(arr)
    for i in range(1, arr_len - 1):
        is_used = [False] * (arr_len/2)
        is_used[arr[i]] = True
        n_used = 1
        for j in range(i+1, arr_len-1):
            if not is_used[arr[j]]:
                is_used[arr[j]] = True
                n_used += 1
            if n_used*2 == j-i+1:
                return True
    return False

def swap_between_occurrences(arr, i):
    """Between the two occurrences of i in arr, swaps all values"""
    for j in xrange(len(arr)):
        if arr[j] == i:
            first_pos = j
            break
        
    for j in xrange(first_pos+1, len(arr)):
        if arr[j] == i:
            second_pos = j

    # http://stackoverflow.com/a/22257860/3347737
    arr[first_pos+1:second_pos] = arr[first_pos+1:second_pos][::-1]

def create_adj_mat(arr):
    "Creates adjacency matrix for bipartite testing"
    N = len(arr)/2
    adj_mat = [[False] * N for row in range(N)]
    between = [False] * N # between[i] iff we're between the two occurrences of i
    for x in arr:
        between[x] = not between[x]
        for i in range(N):
            if between[i] and i!=x:
                adj_mat[i][x] = not adj_mat[i][x]
    return adj_mat

def follow_edges(adj_mat, colours, i):
    for j in range(len(adj_mat)):
        if adj_mat[i][j]:
            if colours[j] is not None:
                if colours[j] == colours[i]:
                    return False
            else:
                colours[j] = 12345 if colours[i]==67890 else 67890
                valid = follow_edges(adj_mat, colours, j)
                if not valid:
                    return False
    return True

def is_bipartite(adj_mat):
    colours = [None] * len(adj_mat)
    for i in range(len(adj_mat)):
        if colours[i] is None:
            colours[i] = 12345
            valid = follow_edges(adj_mat, colours, i)
            if not valid:
                return False
    return True

def is_dually_paired(arr_):
    arr = arr_[:]
    for i in range(len(arr)/2):
        swap_between_occurrences(arr, i)

    adj_mat = create_adj_mat(arr)
    return is_bipartite(adj_mat)

def is_lex_leq_rotation(arr, pos_of_second_zero_in_arr, arr_, rotate_by):
    "Returns True iff arr is <= the given rotation of arr_"
    if arr_[pos_of_second_zero_in_arr-rotate_by] != arr_[0-rotate_by]:
        return True

    #Re-number only as much of the array as we need to for the lex comparison"
    old_to_new_num = [-1] * (len(arr)/2)
    i = 0
    for j in range(len(arr_)):
        x = arr_[j-rotate_by]
        if old_to_new_num[x] == -1:
            # These if statements are repeated to optimise for speed
            if arr[j] < i:
                return True
            elif arr[j] > i:
                return False
            old_to_new_num[x] = i
            i += 1
        else:
            new_num = old_to_new_num[x]
            if arr[j] < new_num:
                return True
            elif arr[j] > new_num:
                return False
    return True


def is_lex_leq_rotations(arr, pos_of_second_zero_in_arr, arr_):
    "Returns True iff arr is <= all rotations of arr_ lexicographically"
    for i in xrange(1, len(arr)):
        if not is_lex_leq_rotation(arr, pos_of_second_zero_in_arr, arr_, i):
            return False
    return True


def is_lex_min_in_group(arr, pos_of_second_zero_in_arr):
    return (
            is_lex_leq_rotations(arr, pos_of_second_zero_in_arr, arr) and
            is_lex_leq_rotations(arr, pos_of_second_zero_in_arr, list(reversed(arr))) and
            is_lex_leq_rotation(arr, pos_of_second_zero_in_arr, list(reversed(arr)), 0))


def search_recursive(N, i, min_permissible_gap, arr, results):
    first_empty = i
    while arr[first_empty] != -1:
        first_empty += 1
        
    if first_empty == i*2 and i>0:
    #    print "First i*2 elements of array are full. Returning."
        return

    arr[first_empty] = i
    j = first_empty + min_permissible_gap + 1

    # An ugly wee bit of symmetry breaking. TODO: generalise this?
    if j < N*2:
        if i==1 and j==4:
            # Array can't start with 01201 (because of dually pairedness)
            j+=2
##        elif arr[min_permissible_gap+2]!=1:
##            if i>1 and arr[first_empty-1]==arr[j-1]:
##                j+=2
##            elif i>2 and arr[first_empty-2]==arr[j-2] and arr[min_permissible_gap+3]!=2:
##                j+=2

    while j < N*2:
#        if i==2 and j==2*N-1:
#            # can't have 0120....2 (for same reason we can't have 01201)
#            break
#        if i<4:
#            print "{:4.2f} s".format(time.time()-START_TIME), " " * i, "i == {}, j == {}".format(i, j)

        if arr[j] == -1:
            gap = j-first_empty-1
            gap = min(gap, N*2-gap-2)
            if gap >= min_permissible_gap:
                arr[j] = i
                if i < N-1:
                    if i==2:
                        print
                        print " ".join(["." if c==-1 else str(c) for c in arr])
                    search_recursive(N, i+1, min_permissible_gap, arr, results)
                else:
                    candidate = arr[:]
                    if(is_lex_min_in_group(candidate, min_permissible_gap+1) and
                             is_dually_paired(candidate) and
                             not is_connect_sum(candidate)):
                        results.append([x+1 for x in candidate])
                        sys.stdout.write(".")
                    else:
                        if not is_dually_paired(candidate):
                            sys.stdout.write("a")
                        elif not is_lex_min_in_group(candidate, min_permissible_gap+1):
                            sys.stdout.write("B")
                        elif is_connect_sum(candidate):
                            sys.stdout.write("C")
                        else:
                            sys.stdout.write("!")
                arr[j] = -1 
        j+=2
    arr[first_empty] = -1

def begin_search_recursive(N):
    results = []
    arr = [-1] * (N*2)
    arr[0] = 0
    for j in range(3, min(N+1, N*2-2), 2):
#        print "{:4.2f} s".format(time.time()-START_TIME), " i == {}, j == {}".format(0, j)
        arr[j] = 0
        search_recursive(N, 1, j-1, arr, results)
        arr[j] = -1 

    return results

results = begin_search_recursive(int(sys.argv[1]))

print "done"
print "Number of results:", len(results)

results.sort()
for i in range(len(results)-1):
    assert results[i] != results[i+1]

#pprint(results)
#for r in results:
#    print "".join(str(x)+", " for x in r)
print "Time elapsed: ", time.time() - START_TIME

