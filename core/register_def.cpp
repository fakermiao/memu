#include "register_def.hpp"
#include <stdio.h>
void PipeReg::print_inst(){
    printf("inst:%s\n",asm_str.c_str());
}