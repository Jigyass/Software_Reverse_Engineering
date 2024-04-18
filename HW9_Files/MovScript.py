#TODO write a description for this script
#@author Jigyas_Sharma
#@category SoftwareReverseEng
#@keybinding 
#@menupath 
#@toolbar 


#TODO Add User Code Here

def count_mov_instructions_in_function(function):
    mov_count = 0
    instruction = getFirstInstruction(function)
    while instruction is not None:
        if instruction.getMnemonicString() == "MOV":
            mov_count += 1
        instruction = getInstructionAfter(instruction)
    return mov_count

function = getFirstFunction()
while function is not None:
    mov_count = count_mov_instructions_in_function(function)
    print("Function: {}, MOV count: {}".format(function.getName(), mov_count))
    function = getFunctionAfter(function)

