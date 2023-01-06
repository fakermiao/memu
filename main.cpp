#include <stdio.h>
#include "core/register_def.hpp"
#include "common.hpp"
#include "memory.hpp"


void init_monitor(int,char *[]);
void engine_start();

int main(int argc,char *argv[]){
    init_monitor(argc,argv);

    engine_start();
// inst_fetch:
//     uint8_t * memory = (uint8_t *)malloc(sizeof(char) * 0x8000000);

//     reg_t pc;
//     reg_t fetch_pc;
//     reg_t new_pc;

//     inst_t inst = vaddr_read(memory + pc,4);
//     fetch_pc    = pc;
//     //简单译码
//     uint8_t opcode      = getbits(inst,0,7);
//     uint8_t singal      = getbits(inst,31,1);
//     reg_t   jal_imme    = getbits(inst,31,1,20) | getbits(inst,21,10,1) |
//                             getbits(inst,20,1,11) | getbits(inst,12,8,12);
//     reg_t   jalr_imme   = getbits(inst,20,12);
//     reg_t   jalr_rs1    = getbits(inst,15,5);
//     reg_t   br_imme     = getbits(inst,31,1,12) | getbits(inst,25,6,5) |
//                             getbits(inst,8,4,1) | getbits(inst,7,1,11);
    
//     //bpu
//     bool    jump        = (opcode == 0x6f) | (opcode == 0x67) | ((opcode == 0x63) && (singal == 0x01));
//     reg_t   jal_op      = sign_extended(jal_imme,21);
//     reg_t   jalr_op     = sign_extended(jalr_imme,12);
//     reg_t   br_op       = sign_extended(br_imme,13); //?
//     reg_t   jump_dest   = (opcode == 0x6f) ? (jal_op + pc) : (opcode == 0x67) ? (gpr[jalr_rs1] + jalr_op) :
//                             (br_op + pc);
//     //生成pc
//     new_pc  = jump ? jump_dest : (pc + 4);
//     pc      = new_pc;
// decode_exe_mem_wb:
    //译码：输入---指令、pc、是否跳转jump、是否遭遇取值非对齐异常、是否遭遇取指存储器访问错误
    /*
    //输出---源操作数1/2寄存器索引为x0、指令需要读取源操作数1/2、指令需要写结果操作数 \
    //     源操作数1/2寄存器索引、结果寄存器索引、指令其他信息打包成一组称之为信号总线、指令使用 \
    //     的立即数的值、译码发现是非法指令  
    */        
    return 0;
}

void assert_fail_msg(){
    printf("exec error\n");
}
CPU_state cpu;