from subprocess import PIPE, Popen
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

for n in range(start, end):
    inputFile = f'{name}/input{n}.txt'
    outputFile = f'{name}/output{n}.txt'
    f = open(outputFile)
    output = f.read()
    command = f'./{ex} < ' + inputFile
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if output == producedOutput.decode("utf-8"):
        print(f'+++ Testcase {n} passed!')
    else:
        print(f'--- Testcase {n} failed!')
        print(f'Expected Output:\n{output}')
        print(f'Produced Output:\n{producedOutput.decode("utf-8")}')