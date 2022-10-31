import os
import sys

ex = str(sys.argv[1])
if ex == "traintrips":
    start = 0
    end = 21
else:
    start = 1
    end = 21

for i in range(start, end):
    f = open(f'tests/{ex}/output' + str(i) + '.txt', 'r')

    print("Testing case:", i)
    print("Output should be:", f.read())
    os.system(f'time ./{ex} < tests/{ex}/input' + str(i) + '.txt')
    print("\n")
    f.close()