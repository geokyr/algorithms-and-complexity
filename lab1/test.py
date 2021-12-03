import os

for i in range(1, 34):
    f = open('teleports/output' + str(i) + '.txt', 'r')

    print("Testing case:", i)
    print("Output should be:", f.read())
    os.system('time ./1Bonus < teleports/input' + str(i) + '.txt')
    print("\n")
    f.close()