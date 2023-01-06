#include "../common.hpp"
class exuDisp{
    //disp相当于派遣，将指令送往发射队列；alu相当于发射，将指令从队列送往不同的执行单元
    //disp判断指令是否是长指令（多个周期执行），进行raw相关性检查等
public:
    bool    wfi_halt_exu_req;   //input
    bool    wfi_halt_exu_ack;   //output
    bool    oitf_empty      ;   //input
    bool    amo_wait        ;   
    bool    disp_i_valid    ;   //handshake valid
    bool    disp_i_ready    ;   //output ,handshake ready
    //the operand 1/2 read-enable signals and indexes
    bool    disp_i_rs1x0    ;   //input
    bool    disp_i_rs2x0    ;
    bool    disp_i_rs1en    ;
    bool    disp_i_rs2en    ;
    uint8_t disp_i_rs1idx   ;
    uint8_t disp_i_rs2idx   ;
    reg_t   disp_i_rs1      ;
    reg_t   disp_i_rs2      ;
    bool    disp_i_rdwen    ;
    uint8_t disp_i_rdidx    ;
    uint32_t disp_i_info    ;
    reg_t   disp_i_imm      ;
    reg_t   disp_i_pc       ;
    bool    disp_i_misalgn  ;
    bool    disp_i_buserr   ;
    bool    disp_i_ilegl    ;
    //dispatch to ALU
    bool    disp_o_alu_valid;   //output
    bool    disp_o_alu_ready;   //input
    bool    disp_o_alu_longpipe;//input
    uint8_t disp_o_alu_rs1  ;   //output
    uint8_t disp_o_alu_rs2  ;   
    bool    disp_o_alu_rdwen;
    uint8_t disp_o_alu_rdidx;
    uint32_t disp_o_alu_info;
    reg_t   disp_o_alu_imm  ;
    reg_t   disp_o_alu_pc   ;
    uint8_t disp_o_alu_itag ;
    bool    disp_o_alu_misalgn;
    bool    disp_o_alu_buserr;
    bool    disp_o_alu_ilegl;
    //dispatch to OITF
    bool    oitfrd_match_disprs1;   //input
    bool    oitfrd_match_disprs2;
    bool    oitfrd_match_disprs3;
    bool    oitfrd_match_disprd ;
    uint8_t disp_oitf_ptr       ;   //oitf默认深度为2个表项
    bool    disp_oitf_ena       ;   //output
    bool    disp_oitf_ready     ;   //input
    bool    disp_oitf_rs1fpu    ;   //output
    bool    disp_oitf_rs2fpu    ;   
    bool    disp_oitf_rs3fpu    ;
    bool    disp_oitf_rdfpu     ;
    bool    disp_oitf_rs1en     ;
    bool    disp_oitf_rs2en     ;
    bool    disp_oitf_rs3en     ;
    bool    disp_oitf_rdwen     ;
    uint8_t disp_oitf_rs1idx    ;
    uint8_t disp_oitf_rs2idx    ;
    uint8_t disp_oitf_rs3idx    ;
    uint8_t disp_oitf_rdidx     ;
    reg_t   disp_oitf_pc        ;

    void    exu_disp();
};