import os
import sys

ex = str(sys.argv[1])
if ex == "teleports":
    start = 0
    end = 34
else:
    start = 1
    end = 26

for i in range(start, end):
    f = open(f'tests/{ex}/output' + str(i) + '.txt', 'r')

    print("Testing case:", i)
    print("Output should be:", f.read())
    os.system(f'time ./{ex} < tests/{ex}/input' + str(i) + '.txt')
    print("\n")
    f.close()