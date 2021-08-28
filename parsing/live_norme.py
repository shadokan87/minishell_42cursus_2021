import  subprocess
import  os
import  sys
import  time

ENDL = "\n"
buffer = ""

def execCmd(prog, concat):
        if (concat == ""):   
	    proc=subprocess.Popen(prog, shell=True, stdout=subprocess.PIPE)
        else:
	    proc=subprocess.Popen(prog + " " + concat, shell=True, stdout=subprocess.PIPE)
	output=proc.communicate()[0]
	return (output)
def getArgs():
    args = []
    i = 1
    while (i < len(sys.argv)):
        args += [sys.argv[i]]
        i += 1
    return (args)

def toBuffer(buffer, str):
    ret = buffer
    ret = ret + str
    buffer = ret
def printBuffer(buffer):
    os.system("clear")
    os.write(1, buffer)
def main():
    execOutput = ""
    cycle = 0
    cycle_end = 5
    args = getArgs()
    os.system("clear")
    while (1):
        execOutput = execCmd("norminette", ' '.join(args))
        if (execOutput != ""):
            printBuffer(execOutput)
        time.sleep(.50)
        cycle += 1

if __name__ == "main":
    main()

main()
