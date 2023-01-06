#include "../common.hpp"
#include <stdint.h>
class decode{
public:
    reg_t       pc;
    inst_t      inst;
    bool        prdt_taken;
    bool        misalgn;
    bool        buserr;
    bool        muldiv_b2b;//the back2back case for mul/div

    bool        dbg_mode;

    bool        dec_rs1x0;
    bool        dec_rs2x0;
    bool        dec_rs1en;
    bool        dec_rs2en;
    bool        dec_rdwen;
    uint8_t     dec_rs1idx;
    uint8_t     dec_rs2idx;
    uint8_t     dec_rdidx;
    uint64_t    dec_info;
    reg_t       dec_imm;
    reg_t       dec_pc;
    bool        dec_misalgn;
    bool        dec_buserr;
    bool        dec_ilegl;

    bool        dec_mulhsu;
    bool        dec_mul;
    bool        dec_div;
    bool        dec_rem;
    bool        dec_divu;
    bool        dec_remu;

    bool        dec_rv32;
    bool        dec_bjp;
    bool        dec_jal;
    bool        dec_jalr;
    bool        dec_bxx;

    uint8_t     dec_jalr_rs1idx;
    reg_t       dec_bjp_imm;

    void parse_inst();
    void info_print();
};