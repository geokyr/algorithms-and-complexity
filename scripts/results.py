import os
import sys

from subprocess import PIPE, Popen

data = {
    'shops2': [1, 26, 1],
    'teleports': [0, 34, 1],
    'bazaar': [0, 20, 2],
    'salaries': [1, 26, 2],
    'roadtrips': [1, 21, 3],
    'traintrips': [0, 21, 3],
}

ex = str(sys.argv[1])
start, end = data[ex][0], data[ex][1]

lab = f"/lab{data[ex][2]:02d}/"
script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(script_dir, ".."))
lab_dir = project_root + lab

for i in range(start, end):
    inputFile = lab_dir + f"tests/{ex}/input{i}.txt"
    outputFile = lab_dir + f"tests/{ex}/output{i}.txt"
    command = lab_dir + f"{ex} < " + inputFile

    f = open(outputFile)
    output = f.read()

    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if output == producedOutput.decode("utf-8"):
        print(f"+++ Testcase {i} passed")
    else:
        print(f"--- Testcase {i} failed")
        print(f"Expected Output:\n{output}")
        print(f"Produced Output:\n{producedOutput.decode('utf-8')}")