import os
import sys

ex = str(sys.argv[1])
if ex == "1":
    name = "teleports"
else:
    name = "shops2"

for i in range(1, 34):
    f = open(f'{name}/output' + str(i) + '.txt', 'r')

    print("Testing case:", i)
    print("Output should be:", f.read())
    os.system(f'time ./{ex} < {name}/input' + str(i) + '.txt')
    print("\n")
    f.close()