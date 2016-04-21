import sys

from itertools import permutations
def swap_between(code, x):
    i = 0
    while code[i] != x:
        i += 1
    
    first = i

    i += 1
    while code[i] != x:
        i += 1

    second = i

    code[first+1:second] = code[second-1:first:-1]

def do_swaps(code):
    code = [int(char) if char.isdigit() else char for char in code] 
    print code
    lo = min(n for n in code if isinstance(n, int))
    hi = max(n for n in code if isinstance(n, int))
    for x in range(lo, hi+1):
        swap_between(code, x)
    

    print
    print " ", " ".join(str(char) for char in code)
    print
    print
    print


#do_swaps("7897a8b9c")
#do_swaps("7897a9b8c")

#for p in permutations([7, 8, 9]):
#    s = "789a{}b{}c{}d".format(*p)
#    do_swaps(s)

for line in open(sys.argv[1]):
    do_swaps(line.strip())
