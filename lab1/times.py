import os
import sys

ex = str(sys.argv[1])
if ex == "1":
    name = "teleports"
    start = 0
    end = 34
else:
    name = "shops2"
    start = 1
    end = 26

for i in range(start, end):
    f = open(f'{name}/output' + str(i) + '.txt', 'r')

    print("Testing case:", i)
    print("Output should be:", f.read())
    os.system(f'time ./{ex} < {name}/input' + str(i) + '.txt')
    print("\n")
    f.close()