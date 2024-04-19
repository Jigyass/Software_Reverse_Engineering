#TODO write a description for this script
#@author Jigyas_Sharma
#@category SoftwareReverseEng
#@keybinding 
#@menupath 
#@toolbar 


#TODO Add User Code Here

#Danger = ["atoi", "gets", "strcpy", "strcat", "sprintf"]
#Danger = ["strcat"]
Danger = ["sprintf"]

def is_dangerous_call(instruction):
    if instruction.getFlowType().isCall():
        called_function = getFunctionAt(instruction.getFlows()[0])
        if called_function and called_function.getName() in Danger:
            return True
    return False

def scan_for_dangerous_calls():
    instruction = getFirstInstruction()
    while instruction:
        if is_dangerous_call(instruction):
            func = getFunctionContaining(instruction.getAddress())
            called_function = getFunctionAt(instruction.getFlows()[0])
            print("Dangerous call to {} from {} at address {}".format(called_function.getName(), func.getName(), instruction.getAddress()))
        instruction = getInstructionAfter(instruction)

def main():
    scan_for_dangerous_calls()

if __name__ == "__main__":
    main()
