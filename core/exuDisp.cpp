#include "exuDisp.hpp"

void exuDisp::exu_disp(){
    uint8_t disp_i_info_grp = getbits(disp_i_info,0,3);
    bool    disp_csr        = (disp_i_info_grp == 0x03);
    bool    disp_alu_longp_prdt = (disp_i_info_grp == 0x01);
    bool    disp_alu_longp_real = disp_o_alu_longpipe;

    // Both fence and fencei need to make sure all outstanding instruction have been completed
    bool    disp_fence_fencei   = (disp_i_info_grp == 0x02) & ((getbits(disp_i_info,15,1) == 0x01) |
                                    (getbits(disp_i_info,16,1) == 0x01));


    //////////////////////////////////////////////////////////////
    // The Dispatch Scheme Introduction for two-pipeline stage
    //  #1: The instruction after dispatched must have already have operand fetched, so
    //      there is no any WAR dependency happened.
    //  #2: The ALU-instruction are dispatched and executed in-order inside ALU, so
    //      there is no any WAW dependency happened among ALU instructions.
    //      Note: LSU since its AGU is handled inside ALU, so it is treated as a ALU instruction
    //  #3: The non-ALU-instruction are all tracked by OITF, and must be write-back in-order, so 
    //      it is like ALU in-ordered. So there is no any WAW dependency happened among
    //      non-ALU instructions.
    //  Then what dependency will we have?
    //  * RAW: This is the real dependency
    //  * WAW: The WAW between ALU an non-ALU instructions
    //  So #1, The dispatching ALU instruction can not proceed and must be stalled when
    //      ** RAW: The ALU reading operands have data dependency with OITF entries
    //         *** Note: since it is 2 pipeline stage, any last ALU instruction have already
    //             write-back into the regfile. So there is no chance for ALU instr to depend 
    //             on last ALU instructions as RAW. 
    //             Note: if it is 3 pipeline stages, then we also need to consider the ALU-to-ALU 
    //                   RAW dependency.
    //      ** WAW: The ALU writing result have no any data dependency with OITF entries
    //           Note: Since the ALU instruction handled by ALU may surpass non-ALU OITF instructions
    //                 so we must check this.
    //  And #2, The dispatching non-ALU instruction can not proceed and must be stalled when
    //      ** RAW: The non-ALU reading operands have data dependency with OITF entries
    //         *** Note: since it is 2 pipeline stage, any last ALU instruction have already
    //             write-back into the regfile. So there is no chance for non-ALU instr to depend 
    //             on last ALU instructions as RAW. 
    //             Note: if it is 3 pipeline stages, then we also need to consider the non-ALU-to-ALU 
    //                   RAW dependency.
    bool raw_dep = oitfrd_match_disprs1 | oitfrd_match_disprs2 | oitfrd_match_disprs3;
    bool dep     = raw_dep | oitfrd_match_disprd;   //oitfrd_match_disprd means WAW depency
    // The WFI halt exu ack will be asserted when the OITF is empty
    //    and also there is no AMO oustanding uops 
    wfi_halt_exu_ack = oitf_empty & (!amo_wait);

    bool disp_condition = (disp_csr ? oitf_empty : true) & (disp_fence_fencei ? oitf_empty : true);
                            (!wfi_halt_exu_req) & (!dep) & (disp_alu_longp_prdt ? disp_oitf_ready : true);

    // Since any instruction will need to be dispatched to ALU, we dont need the gate here
    disp_o_alu_valid    =   disp_condition & disp_i_valid;
    disp_i_ready        =   disp_condition & disp_i_valid;
    
    disp_o_alu_rs1      =   (disp_i_rs1x0 ? 0 : disp_i_rs1);
    disp_o_alu_rs2      =   (disp_i_rs2x0 ? 0 : disp_i_rs2);
    disp_o_alu_rdwen    =   disp_i_rdwen;
    disp_o_alu_rdidx    =   disp_i_rdidx;
    disp_o_alu_info     =   disp_i_info;
    
    disp_oitf_ena       =   disp_o_alu_valid & disp_o_alu_ready & (disp_i_info_grp == 0x01);

    disp_o_alu_imm      =   disp_i_imm;
    disp_o_alu_pc       =   disp_i_pc;
    disp_o_alu_itag     =   disp_oitf_ptr;
    disp_o_alu_misalgn  =   disp_i_misalgn;
    disp_o_alu_buserr   =   disp_i_buserr;
    disp_o_alu_ilegl    =   disp_i_ilegl;

    disp_oitf_rs1fpu    =   false;
    disp_oitf_rs2fpu    =   false;
    disp_oitf_rs3fpu    =   false;
    disp_oitf_rdfpu     =   false;

    disp_oitf_rs1en     =   disp_i_rs1en;
    disp_oitf_rs2en     =   disp_i_rs2en;
    disp_oitf_rs3en     =   false;
    disp_oitf_rdwen     =   disp_i_rdwen;

    disp_oitf_rs1idx    =   disp_i_rs1idx;
    disp_oitf_rs2idx    =   disp_i_rs2idx;
    disp_oitf_rs3idx    =   0x00;
    disp_oitf_rdidx     =   disp_i_rdidx;

    disp_oitf_pc        =   disp_i_pc;


}