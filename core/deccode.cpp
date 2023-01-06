#include "decode.hpp"

void decode::parse_inst(){
    uint8_t     rv32_opcode =   getbits(inst,0,7);
    uint8_t     rv32_func3  =   getbits(inst,12,3);
    uint8_t     rv32_func7  =   getbits(inst,25,7);
    uint8_t     rv32_rd     =   getbits(inst,7,5);
    uint8_t     rv32_rs1    =   getbits(inst,15,5);
    uint8_t     rv32_rs2    =   getbits(inst,20,5);

    uint8_t     rv16_rd     =   rv32_rd;
    uint8_t     rv16_rs1    =   rv16_rd;
    uint8_t     rv16_rs2    =   getbits(inst,2,5);
    uint8_t     rv16_rdd    =   getbits(inst,2,3);
    uint8_t     rv16_rss1   =   getbits(inst,7,3);
    uint8_t     rv16_rss2   =   rv16_rss1;
    uint8_t     rv16_func3  =   getbits(inst,13,3);

    uint8_t     opcode_1_0  =   getbits(rv32_opcode,0,2);
    uint8_t     opcode_4_2  =   getbits(rv32_opcode,2,3);
    uint8_t     opcode_6_5  =   getbits(rv32_opcode,5,2);

    bool        rv32        =   (getbits(inst,2,3) != 0x03) & (opcode_1_0 == 0x03);

    bool        rv32_rs1_x0 =   (rv32_rs1 == 0);
    bool        rv32_rs2_x0 =   (rv32_rs2 == 0);
    //bool        rv32_rs2_x1 =   (rv32_rs2 == 0x01);
    bool        rv32_rd_x0  =   (rv32_rd  == 0);
    bool        rv32_rd_x2  =   (rv32_rd  == 0x02);
    bool        rv32_rs1_x31=   (rv32_rs1 == 0x1f);
    bool        rv32_rs2_x31=   (rv32_rs2 == 0x1f);
    bool        rv32_rd_x31 =   (rv32_rd  == 0x1f);

    bool        rv16_rs1_x0 =   (rv16_rs1 == 0);
    bool        rv16_rs2_x0 =   (rv16_rs2 == 0);
    bool        rv16_rd_x0  =   (rv16_rd  == 0);
    bool        rv16_rd_x2  =   (rv16_rd  == 0x02);

    bool        rv32_load   =   (rv32_opcode == 0x03);
    bool        rv32_store  =   (rv32_opcode == 0x23);
    //bool        rv32_madd   =   (rv32_opcode == 0x43);
    bool        rv32_branch =   (rv32_opcode == 0x63);
    //bool        rv32_load_fp=   (rv32_opcode == 0x07);
    //bool        rv32_store_fp=  (rv32_opcode == 0x27);
    //bool        rv32_msub   =   (rv32_opcode == 0x47);
    bool        rv32_jalr   =   (rv32_opcode == 0x67);
    //bool        rv32_custom0=   (rv32_opcode == 0x0B);
    //bool        rv32_custom1=   (rv32_opcode == 0x2B);
    //bool        rv32_nmsub  =   (rv32_opcode == 0x4B);
    //bool        rv32_resved0=   (rv32_opcode == 0x6B);
    bool        rv32_miscmem=   (rv32_opcode == 0x0F);

    bool        rv32_amo    =   (rv32_opcode == 0x2F);

    //bool        rv32_nmadd  =   (rv32_opcode == 0x4F);
    bool        rv32_jal    =   (rv32_opcode == 0x6F);
    bool        rv32_op_imm =   (rv32_opcode == 0x13);
    bool        rv32_op     =   (rv32_opcode == 0x33);
    //bool        rv32_op_fp  =   (rv32_opcode == 0x53);
    bool        rv32_system =   (rv32_opcode == 0x73);
        
    bool        rv32_auipc  =   (rv32_opcode == 0x17);
    bool        rv32_lui    =   (rv32_opcode == 0x37);
    //bool        rv32_resved1=   (rv32_opcode == 0x57);
    //bool        rv32_resved2=   (rv32_opcode == 0x77);
    //bool        rv32_op_imm_32  =   (rv32_opcode == 0x1B);
    //bool        rv32_op_32  =   (rv32_opcode == 0x3B);
    //bool        rv32_custom2=   (rv32_opcode == 0x5B);
    //bool        rv32_custom3=   (rv32_opcode == 0x7B);

    bool        rv16_addi4spn   =   (opcode_1_0 == 0x00) & (rv16_func3 == 0x00);
    bool        rv16_lw     =   (opcode_1_0 == 0x00) & (rv16_func3 == 0x02);
    bool        rv16_sw     =   (opcode_1_0 == 0x00) & (rv16_func3 == 0x06);
    bool        rv16_addi   =   (opcode_1_0 == 0x01) & (rv16_func3 == 0x00);
    bool        rv16_jal    =   (opcode_1_0 == 0x01) & (rv16_func3 == 0x01);
    bool        rv16_li     =   (opcode_1_0 == 0x01) & (rv16_func3 == 0x02);
    bool        rv16_lui_addi16sp   =   (opcode_1_0 == 0x02) & (rv16_func3 == 0x03);
    bool        rv16_miscalu=   (opcode_1_0 == 0x01) & (rv16_func3 == 0x04);
    bool        rv16_j      =   (opcode_1_0 == 0x01) & (rv16_func3 == 0x05);
    bool        rv16_beqz   =   (opcode_1_0 == 0x01) & (rv16_func3 == 0x06);
    bool        rv16_bnez   =   (opcode_1_0 == 0x01) & (rv16_func3 == 0x07);
    bool        rv16_slli   =   (opcode_1_0 == 0x02) & (rv16_func3 == 0x00);
    bool        rv16_lwsp   =   (opcode_1_0 == 0x02) & (rv16_func3 == 0x02);
    bool        rv16_jalr_mv_add   =   (opcode_1_0 == 0x02) & (rv16_func3 == 0x04);
    bool        rv16_swsp   =   (opcode_1_0 == 0x02) & (rv16_func3 == 0x06);
    #ifndef E203_HAS_FPU
    bool    rv16_flw    =   false;
    bool    rv16_fld    =   false;
    bool    rv16_fsw    =   false;
    bool    rv16_fsd    =   false;
    bool    rv16_fldsp  =   false;
    bool    rv16_flwsp  =   false;
    bool    rv16_fsdsp  =   false;
    bool    rv16_fswsp  =   false;
    #endif
    bool    rv16_lwsp_ilgl  =   rv16_lwsp & rv16_rd_x0;
    bool    rv16_nop    =   rv16_addi & (!getbits(inst,12,1)) & rv16_rd_x0 & rv16_rs2_x0;
    bool    rv16_srli   =   rv16_miscalu & (getbits(inst,10,2) == 0);
    bool    rv16_srai   =   rv16_miscalu & (getbits(inst,10,2) == 1);
    bool    rv16_andi   =   rv16_miscalu & (getbits(inst,10,2) == 2);

    bool    rv16_instr_12_is0   =   (getbits(inst,12,1) == 0);
    bool    rv16_instr_6_2_is0s =   (getbits(inst,2,5) == 0x00);
    bool    rv16_sxxi_shamt_legl=   rv16_instr_12_is0 & (!(rv16_instr_6_2_is0s));
    bool    rv16_sxxi_shamt_ilgl=   (rv16_slli | rv16_srli | rv16_srai) & (!rv16_sxxi_shamt_legl);//是移位指令且立即数有效
    
    bool    rv16_addi16sp       =   rv16_lui_addi16sp & rv32_rd_x2;
    bool    rv16_lui    =   rv16_lui_addi16sp & (!rv32_rd_x0) & (!rv32_rd_x2);
    //C.LI is only valid when rd!=x0.
    bool    rv16_li_ilgl=   rv16_li & (rv16_rd_x0);
    //C.LUI is only valid when rd!=x0 or x2, and when the immediate is not equal to zero.
    bool    rv16_lui_ilgl       =   rv16_lui & (rv16_rd_x0 | rv16_rd_x2 | (rv16_instr_6_2_is0s & rv16_instr_12_is0));
    bool    rv16_li_lui_ilgl    =   rv16_li_ilgl | rv16_lui_ilgl;
    bool    rv16_addi4spn_ilgl  =   rv16_addi4spn & (rv16_instr_12_is0 & rv16_rd_x0 & (opcode_6_5 == 0x00));//(RES, nzimm=0, bits[12:5])
    bool    rv16_addi16sp_ilgl  =   rv16_addi16sp & rv16_instr_12_is0 & rv16_instr_6_2_is0s;//(RES, nzimm=0, bits 12,6:2)

    bool    rv16_subxororand    =   rv16_miscalu & (getbits(inst,10,3) == 0x03);
    bool    rv16_sub    =   rv16_subxororand & (getbits(inst,5,2) == 0x00);
    bool    rv16_xor    =   rv16_subxororand & (getbits(inst,5,2) == 0x01);
    bool    rv16_or     =   rv16_subxororand & (getbits(inst,5,2) == 0x02);
    bool    rv16_and    =   rv16_subxororand & (getbits(inst,5,2) == 0x03);
    bool    rv16_jr     =   rv16_jalr_mv_add & (!(getbits(inst,12,1) == 0x01)) & (!rv16_rs1_x0) & (rv16_rs2_x0);
    bool    rv16_mv     =   rv16_jalr_mv_add & (!(getbits(inst,12,1) == 0x01)) & (!rv16_rd_x0) & (!rv16_rs2_x0);
    bool    rv16_ebreak =   rv16_jalr_mv_add & (getbits(inst,12,1) == 0x01) & (rv16_rd_x0) & (rv16_rs2_x0);
    bool    rv16_jalr   =   rv16_jalr_mv_add & (getbits(inst,12,1) == 0x01) & (!rv16_rs1_x0) & (rv16_rs2_x0);
    bool    rv16_add    =   rv16_jalr_mv_add & (getbits(inst,12,1) == 0x01) & (!rv16_rd_x0) & (!rv16_rs2_x0);

    // ===========================================================================
    // Branch Instructionsr
    bool rv32_beq   =   rv32_branch & (rv32_func3 == 0x00);
    bool rv32_bne   =   rv32_branch & (rv32_func3 == 0x01);
    bool rv32_blt   =   rv32_branch & (rv32_func3 == 0x04);
    bool rv32_bgt   =   rv32_branch & (rv32_func3 == 0x05);
    bool rv32_bltu  =   rv32_branch & (rv32_func3 == 0x06);
    bool rv32_bgtu  =   rv32_branch & (rv32_func3 == 0x07);

    // ===========================================================================
    // System Instructions
    bool rv32_ecall =   rv32_system & (rv32_func3 == 0x00) & (getbits(inst,20,12) == 0x000);
    bool rv32_ebreak=   rv32_system & (rv32_func3 == 0x00) & (getbits(inst,20,12) == 0x001);
    bool rv32_mret  =   rv32_system & (rv32_func3 == 0x00) & (getbits(inst,20,12) == 0x302);
    bool rv32_dret  =   rv32_system & (rv32_func3 == 0x00) & (getbits(inst,20,12) == 0x7B2);
    bool rv32_wfi   =   rv32_system & (rv32_func3 == 0x00) & (getbits(inst,20,12) == 0x105);
    // We dont implement the WFI and MRET illegal exception when the rs and rd is not zeros

    bool rv32_csrrw = rv32_system & (rv32_func3 == 0x01);
    bool rv32_csrrs = rv32_system & (rv32_func3 == 0x02);
    bool rv32_csrrc = rv32_system & (rv32_func3 == 0x03);
    bool rv32_csrrwi= rv32_system & (rv32_func3 == 0x05);
    bool rv32_csrrsi= rv32_system & (rv32_func3 == 0x06);
    bool rv32_csrrci= rv32_system & (rv32_func3 == 0x07);

    bool rv32_dret_ilgl = rv32_dret;//目前没有debug模式故可以不用
    bool rv32_ecall_ebreak_ret_wfi  =   rv32_system & (rv32_func3 == 0x00);
    bool rv32_csr   =   rv32_system & (!(rv32_func3 == 0x00));
    
    dec_jal     =   rv32_jal | rv16_jal | rv16_j;
    dec_jalr    =   rv32_jalr | rv16_jalr | rv16_jr;
    dec_bxx     =   rv32_branch | rv16_beqz | rv16_bnez;
    dec_bjp     =   dec_jal | dec_jalr | dec_bxx;

    // ===========================================================================
    // ALU Instructions
    bool rv32_addi  =   rv32_op_imm & (rv32_func3 == 0x00);
    bool rv32_slti  =   rv32_op_imm & (rv32_func3 == 0x02);
    bool rv32_sltiu =   rv32_op_imm & (rv32_func3 == 0x03);
    bool rv32_xori  =   rv32_op_imm & (rv32_func3 == 0x04);
    bool rv32_ori   =   rv32_op_imm & (rv32_func3 == 0x06);
    bool rv32_andi  =   rv32_op_imm & (rv32_func3 == 0x07);
    bool rv32_slli  =   rv32_op_imm & (rv32_func3 == 0x01) & (getbits(inst,26,6) == 0x00);
    bool rv32_srli  =   rv32_op_imm & (rv32_func3 == 0x05) & (getbits(inst,26,6) == 0x00);
    bool rv32_srai  =   rv32_op_imm & (rv32_func3 == 0x05) & (getbits(inst,26,6) == 0x10);

    bool rv32_sxxi_shamt_legl   =   (getbits(inst,25,1) == 0x00);
    bool rv32_sxxi_shamt_ilgl   =   (rv32_slli | rv32_srli | rv32_srai) & (!rv32_sxxi_shamt_legl);

    bool rv32_add   =   rv32_op & (rv32_func3 == 0x00) & (rv32_func7 == 0x00);
    bool rv32_sub   =   rv32_op & (rv32_func3 == 0x00) & (rv32_func7 == 0x20);
    bool rv32_sll   =   rv32_op & (rv32_func3 == 0x01) & (rv32_func7 == 0x00);
    bool rv32_slt   =   rv32_op & (rv32_func3 == 0x02) & (rv32_func7 == 0x00);
    bool rv32_sltu  =   rv32_op & (rv32_func3 == 0x03) & (rv32_func7 == 0x00);
    bool rv32_xor   =   rv32_op & (rv32_func3 == 0x04) & (rv32_func7 == 0x00);
    bool rv32_srl   =   rv32_op & (rv32_func3 == 0x05) & (rv32_func7 == 0x00);
    bool rv32_sra   =   rv32_op & (rv32_func3 == 0x05) & (rv32_func7 == 0x20);
    bool rv32_or    =   rv32_op & (rv32_func3 == 0x06) & (rv32_func7 == 0x00);
    bool rv32_and   =   rv32_op & (rv32_func3 == 0x07) & (rv32_func7 == 0x00);

    bool rv32_nop   =   rv32_addi & rv32_rs1_x0 & rv32_rd_x0 & (getbits(inst,20,12) == 0x000);
    // The ALU group of instructions will be handled by 1cycle ALU-datapath
    bool ecall_ebreak   =   rv32_ecall | rv32_ebreak | rv16_ebreak;

    bool alu_op =   (!rv32_sxxi_shamt_ilgl) & (!rv16_sxxi_shamt_ilgl) & (!rv16_li_lui_ilgl) &
                    (!rv16_addi4spn_ilgl) & (!rv16_addi16sp_ilgl) & 
                    (rv32_op_imm | (rv32_op & (rv32_func7 != 0x01)) | rv32_auipc | rv32_lui |
                    rv16_addi4spn | rv16_addi | rv16_lui_addi16sp | rv16_li | rv16_mv |
                    rv16_slli | rv16_miscalu | rv16_add | rv16_nop | rv32_nop |
                    rv32_wfi | ecall_ebreak);
    
    //muldiv instructions
    bool rv32_mul   =   rv32_op & (rv32_func3 == 0x00) & (rv32_func7 == 0x01);
    bool rv32_mulh  =   rv32_op & (rv32_func3 == 0x01) & (rv32_func7 == 0x01);
    bool rv32_mulhsu=   rv32_op & (rv32_func3 == 0x02) & (rv32_func7 == 0x01);
    bool rv32_mulhu =   rv32_op & (rv32_func3 == 0x03) & (rv32_func7 == 0x01);
    bool rv32_div   =   rv32_op & (rv32_func3 == 0x04) & (rv32_func7 == 0x01);
    bool rv32_divu  =   rv32_op & (rv32_func3 == 0x05) & (rv32_func7 == 0x01);
    bool rv32_rem   =   rv32_op & (rv32_func3 == 0x06) & (rv32_func7 == 0x01);
    bool rv32_remu  =   rv32_op & (rv32_func3 == 0x07) & (rv32_func7 == 0x01);
    bool muldiv_op  =   rv32_op & (rv32_func7 == 0x01);
    dec_mulhsu  =   rv32_mulh | rv32_mulhsu | rv32_mulhu;
    dec_mul     =   rv32_mul;
    dec_div     =   rv32_div;
    dec_divu    =   rv32_divu;
    dec_rem     =   rv32_rem;
    dec_remu    =   rv32_remu;

    // Reuse the common signals as much as possible to save gatecounts
    bool    rv32_all0s_ilgl =   (rv32_func7 == 0x00) & (rv32_rs2_x0) & (rv32_rs1_x0) & 
                                (rv32_func3 == 0x00) & (rv32_rd_x0) & (opcode_6_5 == 0x00) & 
                                (opcode_4_2 == 0x00) & (opcode_1_0 == 0x00);
    bool    rv32_all1s_ilgl =   (rv32_func7 == 0x7f) & (rv32_rs2_x31) & (rv32_rs1_x31) & (rv32_func3 == 0x03) & 
                                (rv32_rd_x31) & (rv32_opcode == 0x7f);
    bool    rv16_all0s_ilgl =   (rv16_func3 == 0x00) & (rv32_func3 == 0x00) & (rv32_rd_x0) & 
                                (rv32_opcode == 0x00);
    bool    rv16_all1s_ilgl =   (rv16_func3 == 0x03) & (rv32_func3 == 0x03) & (rv32_rd_x31) &
                                (rv32_opcode == 0x7f);
    bool    rv_all0s1s_ilgl =   rv32 ? (rv32_all0s_ilgl | rv32_all1s_ilgl) : (rv16_all0s_ilgl | rv16_all1s_ilgl);

    bool rv32_fence = rv32_miscmem & (rv32_func3 == 0x00);
    bool rv32_fence_i = rv32_miscmem & (rv32_func3 == 0x01);
    bool rv32_fence_fencei = rv32_miscmem;
    bool bjp_op = dec_bjp | rv32_mret | (rv32_dret & (!rv32_dret_ilgl)) | rv32_fence_fencei;

    bool need_imm;
    uint32_t alu_info_bus;

    // ===========================================================================
    // Load/Store Instructions
    // bool rv32_lb    =   rv32_load & (rv32_func3 == 0x00);
    // bool rv32_lh    =   rv32_load & (rv32_func3 == 0x01);
    // bool rv32_lw    =   rv32_load & (rv32_func3 == 0x02);
    // bool rv32_lbu   =   rv32_load & (rv32_func3 == 0x04);
    // bool rv32_lhu   =   rv32_load & (rv32_func3 == 0x05);
    // bool rv32_sb    =   rv32_store & (rv32_func3 == 0x00);
    // bool rv32_sh    =   rv32_store & (rv32_func3 == 0x01);
    // bool rv32_sw    =   rv32_store & (rv32_func3 == 0x02);
    // ===========================================================================
    // Atomic Instructions
    bool rv32_lr_w      =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x02);
    bool rv32_sc_w      =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x03);
    bool rv32_amoswap_w =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x01);
    bool rv32_amoadd_w  =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x00);
    bool rv32_amoxor_w  =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x04);
    bool rv32_amoand_w  =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x0C);
    bool rv32_amoor_w   =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x08);
    bool rv32_amomin_w  =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x10);
    bool rv32_amomax_w  =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x14);
    bool rv32_amominu_w =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x18);
    bool rv32_amomaxu_w =   rv32_amo & (rv32_func3 == 0x02) & (getbits(rv32_func7,2,5) == 0x1C);
    bool amoldst_op     =   rv32_amo | rv32_load | rv32_store | rv16_lw | rv16_sw | 
                            (rv16_lwsp & (!rv16_lwsp_ilgl)) | rv16_swsp;
    
    //
    // All the RV32IMA need RD register except the Branch, Store, fence, fence_i, ecall, ebreak  
    bool    rv32_need_rd    =   (!rv32_rd_x0) & ((!rv32_branch) & (!rv32_store) & (!rv32_fence_fencei) &
                                 (!rv32_ecall_ebreak_ret_wfi));
    
    // All the RV32IMA need RS1 register except the lui, auipc, jal, fence, fence_i, ecall, ebreak  
    //   * csrrwi, csrrsi, csrrci
    bool rv32_need_rs1      =   (!rv32_rs1_x0) & ((!rv32_lui) & (!rv32_auipc) & (!rv32_jal) & 
                                (!rv32_fence_fencei) & (!rv32_ecall_ebreak_ret_wfi) & 
                                (!rv32_csrrwi) & (!rv32_csrrsi) & (!rv32_csrrci));

    // Following RV32IMA instructions need RS2 register: branch, store, rv32_op, rv32_amo except the rv32_lr_w
    bool rv32_need_rs2      =   (!rv32_rs2_x0) & ((rv32_branch) | (rv32_store) | (rv32_op) |
                                (rv32_amo & (!rv32_lr_w)));

    uint32_t    rv32_i_imm  =   getbits(inst,20,12);
    uint32_t    rv32_s_imm  =   sign_extended((getbits(inst,25,7,5) | getbits(inst,7,5)),12);
    uint32_t    rv32_b_imm  =   sign_extended((getbits(inst,31,1,12) | getbits(inst,7,1,11) | getbits(inst,25,6,5) | getbits(inst,8,4,1)),13);
    uint32_t    rv32_u_imm  =   getbits(inst,12,20,13);
    uint32_t    rv32_j_imm  =   sign_extended((getbits(inst,21,10,1) | getbits(inst,20,1,11) | getbits(inst,12,8,12) |
                                getbits(inst,31,1,20)),21);
    // It will select i-type immediate when rv32_op_imm, rv32_jalr, rv32_load
    bool    rv32_imm_sel_i  =   rv32_op_imm | rv32_jalr | rv32_load;
    //bool    rv32_imm_sel_jalr   =   rv32_jalr;
    uint32_t rv32_jalr_imm  =   rv32_i_imm;
    // It will select u-type immediate when rv32_lui, rv32_auipc                             
    bool    rv32_imm_sel_u  =   rv32_lui | rv32_auipc;
    bool    rv32_imm_sel_j  =   rv32_jal;
    //bool    rv32_imm_sel_jal=   rv32_jal;
    uint32_t rv32_jal_imm   =   rv32_j_imm;
    // It will select b-type immediate when rv32_branch
    bool    rv32_imm_sel_b  =   rv32_branch;
    //bool    rv32_imm_sel_bxx=   rv32_branch;
    uint32_t    rv32_bxx_imm=   rv32_b_imm;
    // It will select s-type immediate when rv32_store
    bool    rv32_imm_sel_s  =   rv32_store;


    //   * Note: this CIS/CILI/CILUI/CI16SP-type is named by myself, because in ISA doc, the CI format for LWSP is different
    //     with other CI formats in terms of immediate
  
    // It will select CIS-type immediate when rv16_lwsp
    bool    rv16_imm_sel_cis=   rv16_lwsp;
    uint32_t rv16_cis_imm   =   getbits(inst,2,2,6) | getbits(inst,12,1,5) | getbits(inst,4,3,2);
    //uint32_t rv16_cis_d_imm =   getbits(inst,2,3,6) | getbits(inst,12,1,5) | getbits(inst,5,2,3);
    // It will select CILI-type immediate when rv16_li, rv16_addi, rv16_slli, rv16_srai, rv16_srli, rv16_andi
    bool    rv16_imm_sel_cili   =   rv16_li | rv16_addi | rv16_slli | rv16_srai | rv16_srli | rv16_andi;
    uint32_t rv16_cili_imm  =   sign_extended((getbits(inst,12,1,5) | getbits(inst,2,5)),7);
    // It will select CILUI-type immediate when rv16_lui
    bool    rv16_imm_sel_cilui  =   rv16_lui;
    uint32_t rv16_cilui_imm =   sign_extended((getbits(inst,12,1,17) | getbits(inst,2,5,12)),18);
    // It will select CI16SP-type immediate when rv16_addi16sp
    bool    rv16_imm_sel_ci16sp = rv16_addi16sp;
    uint32_t rv16_ci16sp_imm=   sign_extended((getbits(inst,12,1,9) | getbits(inst,4,1,8) | getbits(inst,3,1,7) |
                                getbits(inst,5,1,6) | getbits(inst,2,1,5) | getbits(inst,6,1,4)),10);
    // It will select CSS-type immediate when rv16_swsp
    bool    rv16_imm_sel_css    =   rv16_swsp;
    uint32_t rv16_css_imm   =   getbits(inst,7,2,6) | getbits(inst,9,4,2);
    //uint32_t rv16_css_d_imm =   getbits(inst,7,3,6) | getbits(inst,10,3,3);
    // It will select CIW-type immediate when rv16_addi4spn
    bool    rv16_imm_sel_ciw    =   rv16_addi4spn;
    uint32_t rv16_ciw_imm   =   getbits(inst,7,4,6) | getbits(inst,12,1,5) | getbits(inst,11,1,4) | getbits(inst,5,1,3) |
                                getbits(inst,6,1,2);
    // It will select CL-type immediate when rv16_lw
    bool    rv16_imm_sel_cl = rv16_lw;
    uint32_t rv16_cl_imm    =   getbits(inst,5,1,6) | getbits(inst,12,1,5) | getbits(inst,11,1,4) | getbits(inst,10,1,3) |
                                getbits(inst,6,1,2);
    //uint32_t rv16_cl_d_imm  =   getbits(inst,6,1,7) | getbits(inst,5,1,6) | getbits(inst,12,1,5) | getbits(inst,11,1,4) |
                                getbits(inst,10,1,3);
    // It will select CS-type immediate when rv16_sw
    bool rv16_imm_sel_cs    =   rv16_sw;
    uint32_t rv16_cs_imm    =   getbits(inst,5,1,6) | getbits(inst,12,1,5) | getbits(inst,11,1,4) | getbits(inst,10,1,3) |
                                getbits(inst,6,1,2);
    //uint32_t rv16_cs_d_imm  =   getbits(inst,6,1,7) | getbits(inst,5,1,6) | getbits(inst,12,1,5) | getbits(inst,11,1,4) |
                                getbits(inst,10,1,3);
    // It will select CB-type immediate when rv16_beqz, rv16_bnez
    bool rv16_imm_sel_cb    =   rv16_beqz | rv16_bnez;
    uint32_t rv16_cb_imm    =   getbits(inst,12,1,8) | getbits(inst,5,2,6) | getbits(inst,2,1,5) | getbits(inst,10,2,3) | 
                                getbits(inst,3,2,1);                           
    uint32_t rv16_bxx_imm   =   rv16_cb_imm;
    // It will select CJ-type immediate when rv16_j, rv16_jal
    bool rv16_imm_sel_cj    =   rv16_j | rv16_jal;
    uint32_t rv16_cj_imm    =   sign_extended((getbits(inst,12,1,11) | getbits(inst,8,1,10) | getbits(inst,9,2,8) | 
                                getbits(inst,6,1,7) | getbits(inst,7,1,6) | getbits(inst,2,1,5) | getbits(inst,11,1,4) |
                                getbits(inst,3,3,1)),12);
    uint32_t rv16_jjal_imm  = rv16_cj_imm;
    // It will select CR-type register (no-imm) when rv16_jalr_mv_add
    uint32_t rv16_jrjalr_imm= 0x00;
    // It will select CSR-type register (no-imm) when rv16_subxororand
    //uint32_t rv32_load_fp_imm = rv32_i_imm;
    //uint32_t rv32_store_fp_imm= rv32_s_imm;
    uint32_t rv32_imm       =   rv32_imm_sel_i ? rv32_i_imm :
                                rv32_imm_sel_s ? rv32_s_imm :
                                rv32_imm_sel_b ? rv32_b_imm : 
                                rv32_imm_sel_u ? rv32_u_imm :
                                rv32_imm_sel_j ? rv32_j_imm : 0;
    bool    rv32_need_imm   =   rv32_imm_sel_i | rv32_imm_sel_s | rv32_imm_sel_b | rv32_imm_sel_u | rv32_imm_sel_j;
    uint32_t rv16_imm       =   rv16_imm_sel_cis    ? rv16_cis_imm    :
                                rv16_imm_sel_cili   ? rv16_cili_imm   :
                                rv16_imm_sel_cilui  ? rv16_cilui_imm  :
                                rv16_imm_sel_ci16sp ? rv16_ci16sp_imm :
                                rv16_imm_sel_css    ? rv16_css_imm    :
                                rv16_imm_sel_ciw    ? rv16_ciw_imm    :
                                rv16_imm_sel_cl     ? rv16_cl_imm     :
                                rv16_imm_sel_cs     ? rv16_cs_imm     :
                                rv16_imm_sel_cb     ? rv16_cb_imm     :
                                rv16_imm_sel_cj     ? rv16_cj_imm     : 0;
    bool    rv16_need_imm   =   rv16_imm_sel_cis | rv16_imm_sel_cili | rv16_imm_sel_cilui | rv16_imm_sel_ci16sp |
                                rv16_imm_sel_css | rv16_imm_sel_ciw  | rv16_imm_sel_cl    | rv16_imm_sel_cs | 
                                rv16_imm_sel_cb  | rv16_imm_sel_cj; 
    need_imm = rv32 ? rv32_need_imm : rv16_need_imm;


    //===================================
    //ALU info bus
    alu_info_bus = 0x00 | (rv32 << 3) | ((rv32_add | rv32_addi | rv32_auipc | rv16_addi4spn | rv16_addi |
                        // We also decode LI and MV as the add instruction, becuase
                        //   they all add x0 with a RS2 or Immeidate, and then write into RD
                    rv16_addi16sp | rv16_add | rv16_li | rv16_mv) << 4) |
                    ((rv32_sub | rv16_sub) << 5) | ((rv32_slt | rv32_slti) << 6) |
                    ((rv32_sltu | rv32_sltiu) << 7) | ((rv32_xor | rv32_xori | rv16_xor) << 8) |
                    ((rv32_sll | rv32_slli | rv16_slli) << 9) | ((rv32_srl | rv32_srli | rv16_srli) << 10) |
                    ((rv32_sra | rv32_srai | rv16_srai) << 11) | ((rv32_or | rv32_ori | rv16_or) << 12) |
                    ((rv32_and | rv32_andi | rv16_addi | rv16_and) << 13) |
                    ((rv32_lui | rv16_lui) << 14) | (need_imm << 15) | (rv32_auipc << 16) |
                    ((rv32_nop | rv16_nop) << 17) | (rv32_ecall << 18) | ((rv32_ebreak | rv16_ebreak) << 19) |
                    (rv32_wfi << 20);
        
    //===================================
    //AGU info bus
    reg_t lsu_info_size  =   rv32 ? getbits(rv32_func3,0,2) : 0x02;// The RV16 always is word
    bool  lsu_info_usign =   rv32 ? (getbits(rv32_func3,2,1) == 0x01) : false;// The RV16 always is signed
    uint32_t    agu_info_bus;
    agu_info_bus        =   0x01 | (rv32 << 3) | ((rv32_load | rv32_lr_w | rv16_lw | rv16_lwsp) << 4) |
                            ((rv32_store | rv32_sc_w | rv16_sw | rv16_swsp) << 5) | (lsu_info_size << 6) | 
                            (lsu_info_usign << 7) | ((rv32_lr_w | rv32_sc_w) << 8) |
                            // We seperated the EXCL out of AMO in LSU handling
                            ((rv32_amo & (!(rv32_lr_w | rv32_sc_w))) << 9) |
                            (rv32_amoswap_w << 10) | (rv32_amoadd_w << 11) | (rv32_amoand_w << 12) |
                            (rv32_amoor_w << 13) | (rv32_amoxor_w << 14) | (rv32_amomax_w << 15) |
                            (rv32_amomin_w << 16) | (rv32_amomaxu_w << 17) | (rv32_amominu_w << 18) |
                            (need_imm << 19);
    
    //===================================
    //BJP info bus
    uint32_t bjp_info_bus;//传递给各运算单元的控制信息，最后处理
    bjp_info_bus = 0x02 | (rv32 << 3) | ((dec_jal | dec_jalr) << 4) | (prdt_taken << 5) |
                    ((rv32_beq | rv16_beqz) << 6) | ((rv32_bne | rv16_bnez) << 7) | (rv32_blt << 8) |
                    (rv32_bgt << 9) | (rv32_bltu << 10) | (rv32_bgtu << 11) | (dec_bxx << 12) |
                    (rv32_mret << 13) | (rv32_dret << 14) | (rv32_fence << 15) | (rv32_fence_i << 16);

    //===================================
    //CSR info bus
    bool csr_op =   rv32_csr;
    uint32_t csr_info_bus;
    csr_info_bus = 0x03 | (rv32 << 3) | ((rv32_csrrw | rv32_csrrwi) << 4) | 
                    ((rv32_csrrs | rv32_csrrsi)  << 5) | ((rv32_csrrc | rv32_csrrci) << 6) |
                    ((rv32_csrrwi | rv32_csrrsi | rv32_csrrci) << 7) | (rv32_rs1 << 8) |
                    (rv32_rs1_x0 << 9) | ((uint32_t)getbits(inst,20,12,10));

    //===================================
    //MULDIV info bus
    uint32_t muldiv_info_bus;
    muldiv_info_bus =   0x04 | (rv32 << 3) | (rv32_mul << 4) | (rv32_mulh << 5) | (rv32_mulhsu << 6) | 
                        (rv32_mulhu << 7) | (rv32_div << 8) | (rv32_divu << 9) | (rv32_rem << 10) |
                        (rv32_remu << 11) | (muldiv_b2b << 12);
    
    dec_imm  = rv32 ? rv32_imm      : rv16_imm;
    dec_pc   = pc;
    dec_info =  alu_op      ? alu_info_bus  :
                amoldst_op  ? agu_info_bus  :
                bjp_op      ? bjp_info_bus  :
                csr_op      ? csr_info_bus  :
                muldiv_op   ? muldiv_info_bus : 0;
    bool legl_ops   =   alu_op | amoldst_op | bjp_op | csr_op | muldiv_op;


    // To decode the registers for Rv16, divided into 8 groups
    bool rv16_format_cr =   rv16_jalr_mv_add;
    bool rv16_format_ci =   rv16_lwsp | rv16_flwsp | rv16_fldsp | rv16_li | rv16_lui_addi16sp | rv16_addi | rv16_slli;
    bool rv16_format_css=   rv16_swsp | rv16_fswsp | rv16_fsdsp;
    bool rv16_format_ciw=   rv16_addi4spn;
    bool rv16_format_cl =   rv16_lw   | rv16_flw   | rv16_fld;
    bool rv16_format_cs =   rv16_sw   | rv16_fsw   | rv16_fsd   | rv16_subxororand;
    bool rv16_format_cb =   rv16_beqz | rv16_bnez  | rv16_srli  | rv16_srai | rv16_andi;
    bool rv16_format_cj =   rv16_j    | rv16_jal;
    
    // In CR Cases:
    //   * JR:     rs1= rs1(coded),     rs2= x0 (coded),   rd = x0 (implicit)
    //   * JALR:   rs1= rs1(coded),     rs2= x0 (coded),   rd = x1 (implicit)
    //   * MV:     rs1= x0 (implicit),  rs2= rs2(coded),   rd = rd (coded)
    //   * ADD:    rs1= rs1(coded),     rs2= rs2(coded),   rd = rd (coded)
    //   * eBreak: rs1= rs1(coded),     rs2= x0 (coded),   rd = x0 (coded)
    bool rv16_need_cr_rs1   =   rv16_format_cr;
    bool rv16_need_cr_rs2   =   rv16_format_cr;
    bool rv16_need_cr_rd    =   rv16_format_cr;
    uint8_t rv16_cr_rs1     =   rv16_mv ? 0x00 : rv16_rs1;
    uint8_t rv16_cr_rs2     =   rv16_rs2;
    // The JALR and JR difference in encoding is just the rv16_instr[12]
    uint8_t rv16_cr_rd      =   (rv16_jalr | rv16_jr) ? ((getbits(inst,12,1) == 0x01) ? 0xff : 0x00) :
                                rv16_rd;
    
    // In CI Cases:
    //   * LWSP:     rs1= x2 (implicit),  rd = rd 
    //   * LI/LUI:   rs1= x0 (implicit),  rd = rd
    //   * ADDI:     rs1= rs1(implicit),  rd = rd
    //   * ADDI16SP: rs1= rs1(implicit),  rd = rd
    //   * SLLI:     rs1= rs1(implicit),  rd = rd
    bool rv16_need_ci_rs1 = rv16_format_ci;
    bool rv16_need_ci_rs2 = false;
    bool rv16_need_ci_rd  = rv16_format_ci;
    uint8_t rv16_ci_rs1   = (rv16_lwsp | rv16_flwsp | rv16_fldsp) ? 0x02 :
                            (rv16_li | rv16_lui) ? 0x00 : rv16_rs1;
    uint8_t rv16_ci_rs2   = 0x00;
    uint8_t rv16_ci_rd    = rv16_rd;

    // In CSS Cases:
    //   * SWSP:     rs1 = x2 (implicit), rs2= rs2 
    bool rv16_need_css_rs1= rv16_format_css;
    bool rv16_need_css_rs2= rv16_format_css;
    bool rv16_need_css_rd = false;
    uint8_t rv16_css_rs1  = 0x02;
    uint8_t rv16_css_rs2  = rv16_rs2;
    uint8_t rv16_css_rd   = 0x00;

    // In CIW cases:
    //   * ADDI4SPN:   rdd = rdd, rss1= x2 (implicit)
    bool rv16_need_ciw_rss1= rv16_format_ciw;
    bool rv16_need_ciw_rss2= false;
    bool rv16_need_ciw_rdd = rv16_format_ciw;
    uint8_t rv16_ciw_rss1  = 0x02;
    uint8_t rv16_ciw_rss2  = 0x00;
    uint8_t rv16_ciw_rdd   = rv16_rdd;

    // In CL cases:
    //   * LW:   rss1 = rss1, rdd= rdd
    bool rv16_need_cl_rss1 = rv16_format_cl;
    bool rv16_need_cl_rss2 = false;
    bool rv16_need_cl_rdd  = rv16_format_cl;
    uint8_t rv16_cl_rss1   = rv16_rss1;
    uint8_t rv16_cl_rss2   = 0x00;
    uint8_t rv16_cl_rdd    = rv16_rdd;

    // In CS cases:
    //   * SW:            rdd = none(implicit), rss1= rss1       , rss2=rss2
    //   * SUBXORORAND:   rdd = rss1,           rss1= rss1(coded), rss2=rss2
    bool rv16_need_cs_rss1 = rv16_format_cs;
    bool rv16_need_cs_rss2 = rv16_format_cs;
    bool rv16_need_cs_rdd  = rv16_format_cs & rv16_subxororand;
    uint8_t rv16_cs_rss1   = rv16_rss1;
    uint8_t rv16_cs_rss2   = rv16_rss2;
    uint8_t rv16_cs_rdd    = rv16_rss1;

    // In CB cases:
    //   * BEQ/BNE:            rdd = none(implicit), rss1= rss1, rss2=x0(implicit)
    //   * SRLI/SRAI/ANDI:     rdd = rss1          , rss1= rss1, rss2=none(implicit)
    bool rv16_need_cb_rss1 = rv16_format_cb;
    bool rv16_need_cb_rss2 = rv16_format_cb & (rv16_beqz | rv16_bnez);
    bool rv16_need_cb_rdd  = rv16_format_cb & (!(rv16_beqz | rv16_bnez));
    uint8_t rv16_cb_rss1   = rv16_rss1;
    uint8_t rv16_cb_rss2   = 0x00;
    uint8_t rv16_cb_rdd    = rv16_rss1;

    // In CJ cases:
    //   * J:            rdd = x0(implicit)
    //   * JAL:          rdd = x1(implicit)
    bool rv16_need_cj_rss1 = false;
    bool rv16_need_cj_rss2 = false;
    bool rv16_need_cj_rdd  = rv16_format_cj;
    uint8_t rv16_cj_rss1   = 0x00;
    uint8_t rv16_cj_rss2   = 0x00;
    uint8_t rv16_cj_rdd    = rv16_j ? 0x00 : 0x01;

    bool rv16_need_rs1     = rv16_need_cr_rs1 | rv16_need_ci_rs1 | rv16_need_css_rs1;
    bool rv16_need_rs2     = rv16_need_cr_rs2 | rv16_need_ci_rs2 | rv16_need_css_rs2;
    bool rv16_need_rd      = rv16_need_cr_rd  | rv16_need_ci_rd  | rv16_need_css_rd;
    bool rv16_need_rss1    = rv16_need_ciw_rss1 | rv16_need_cl_rss1 | rv16_need_cs_rss1 | rv16_need_cb_rss1 | rv16_need_cj_rss1; 
    bool rv16_need_rss2    = rv16_need_ciw_rss2 | rv16_need_cl_rss2 | rv16_need_cs_rss2 | rv16_need_cb_rss2 | rv16_need_cj_rss2;
    bool rv16_need_rdd     = rv16_need_ciw_rdd  | rv16_need_cl_rdd  | rv16_need_cs_rdd  | rv16_need_cb_rdd  | rv16_need_cj_rdd;

    bool rv16_rs1en        = (rv16_need_rs1 | rv16_need_rss1);
    bool rv16_rs2en        = (rv16_need_rs2 | rv16_need_rss2);
    bool rv16_rden         = (rv16_need_rd  | rv16_need_rdd);
    uint8_t rv16_rs1idx;
    uint8_t rv16_rs2idx;
    uint8_t rv16_rdidx;
    rv16_rs1idx =   rv16_need_cr_rs1    ? rv16_cr_rs1   :
                    rv16_need_ci_rs1    ? rv16_ci_rs1   :
                    rv16_need_css_rs1   ? rv16_css_rs1  :
                    rv16_need_ciw_rss1  ? rv16_ciw_rss1 :
                    rv16_need_cl_rss1   ? rv16_cl_rss1  :
                    rv16_need_cs_rss1   ? rv16_cs_rss1  :
                    rv16_need_cb_rss1   ? rv16_cb_rss1  :
                    rv16_need_cj_rss1   ? rv16_cj_rss1  : 0;
    rv16_rs2idx =   rv16_need_cr_rs2    ? rv16_cr_rs2   :
                    rv16_need_ci_rs2    ? rv16_ci_rs2   :
                    rv16_need_css_rs2   ? rv16_css_rs2  :
                    rv16_need_ciw_rss2  ? rv16_ciw_rss2 :
                    rv16_need_cl_rss2   ? rv16_cl_rss2  :
                    rv16_need_cs_rss2   ? rv16_cs_rss2  :
                    rv16_need_cb_rss2   ? rv16_cb_rss2  :
                    rv16_need_cj_rss2   ? rv16_cj_rss2  : 0;
    rv16_rdidx  =   rv16_need_cr_rd     ? rv16_cr_rd    :
                    rv16_need_ci_rd     ? rv16_ci_rd    :
                    rv16_need_css_rd    ? rv16_css_rd   :
                    rv16_need_ciw_rdd   ? rv16_ciw_rdd  :
                    rv16_need_cl_rdd    ? rv16_cl_rdd   :
                    rv16_need_cs_rdd    ? rv16_cs_rdd   :
                    rv16_need_cb_rdd    ? rv16_cb_rdd   :
                    rv16_need_cj_rdd    ? rv16_cj_rdd   : 0;

    dec_rs1idx  = rv32 ? rv32_rs1 : rv16_rs1idx;
    dec_rs2idx  = rv32 ? rv32_rs2 : rv16_rs2idx;
    dec_rdidx   = rv32 ? rv32_rd  : rv16_rdidx;
    dec_rs1en   = rv32 ? rv32_need_rs1 : (rv16_rs1en & (rv16_rs1idx != 0x00));
    dec_rs2en   = rv32 ? rv32_need_rs2 : (rv16_rs2en & (rv16_rs2idx != 0x00));
    dec_rdwen   = rv32 ? rv32_need_rd  : (rv16_rden & (rv16_rdidx != 0x00));

    dec_rs1x0   = (dec_rs1idx == 0x00);
    dec_rs2x0   = (dec_rs2idx == 0x00);

    bool rv_index_ilgl = false;    
    dec_rv32    = rv32;
    dec_bjp_imm =   (rv16_jal | rv16_j)     ?   rv16_jjal_imm   :
                    (rv16_jalr_mv_add)      ?   rv16_jrjalr_imm :
                    (rv16_beqz | rv16_bnez) ?   rv16_bxx_imm    :
                    rv32_jal                ?   rv32_jal_imm    :
                    rv32_jalr               ?   rv32_jalr_imm   :
                    rv32_branch             ?   rv32_bxx_imm    : 0;
    dec_jalr_rs1idx =   rv32 ? rv32_rs1 : rv16_rs1;
    dec_misalgn     = misalgn;
    dec_buserr      = buserr;

    dec_ilegl       = (rv_all0s1s_ilgl) | (rv_index_ilgl) | (rv16_addi16sp_ilgl) |
                        (rv16_addi4spn_ilgl) | (rv16_li_lui_ilgl) | (rv16_sxxi_shamt_ilgl) |
                        (rv32_sxxi_shamt_ilgl) | (rv32_dret_ilgl) | (rv16_lwsp_ilgl) | (!legl_ops);


}