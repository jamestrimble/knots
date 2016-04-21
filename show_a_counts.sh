pypy backtrack2.py 10 | grep -B1 "^a\+\$" | awk '/a+/ {print "*** " length($0) " ***"; next} {print}'
