#include "../common.hpp"
struct oitf{
    uint8_t rdidx   ;
    reg_t   pc      ;
    bool    rdwen   ;
    bool    rdfpu   ;
};
#define OITF_NUM 4
class exuOitf
{

public:
    bool    dis_ready           ;   //output--表项是否填满
    bool    dis_ena             ;   //input
    bool    ret_ena             ;   //input
    uint8_t dis_ptr             ;   //output
    uint8_t ret_ptr             ;
    uint8_t ret_rdidx           ;
    bool    ret_rdwen           ;
    bool    ret_rdfpu           ;
    reg_t   ret_pc              ;
    bool    disp_i_rs1en        ;   //input
    bool    disp_i_rs2en        ;
    bool    disp_i_rs3en        ;
    bool    disp_i_rdwen        ;
    bool    disp_i_rs1fpu       ;
    bool    disp_i_rs2fpu       ;
    bool    disp_i_rs3fpu       ;
    bool    disp_i_rdfpu        ;
    uint8_t disp_i_rs1idx       ;
    uint8_t disp_i_rs2idx       ;
    uint8_t disp_i_rs3idx       ;
    uint8_t disp_i_rdidx        ;
    reg_t   disp_i_pc           ;
    bool    oitfrd_match_disprs1;   //output
    bool    oitfrd_match_disprs2;
    bool    oitfrd_match_disprs3;
    bool    oitfrd_match_disprd ;
    bool    oitf_empty          ;
    exuOitf();

    void exu();
private:
    struct oitf fifo[OITF_NUM];
    reg_t   header_ptr;
    reg_t   footer_prt;   
    bool    full;
    bool    empty;
};

