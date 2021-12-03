from subprocess import PIPE, Popen

for n in range(0,34):
    inputFile = f'teleports/input{n}.txt'
    outputFile = f'teleports/output{n}.txt'
    f = open(outputFile)
    output = f.read()
    command = "./1 < " + inputFile
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if output == producedOutput.decode("utf-8"):
        print(f'+++ Testcase {n} passed!')
    else:
        print(f'--- Testcase {n} failed!')
        print(f'Expected Output:\n{output}')
        print(f'Produced Output:\n{producedOutput.decode("utf-8")}')