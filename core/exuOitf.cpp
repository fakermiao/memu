#include "exuOitf.hpp"

exuOitf::exuOitf(){
    full    =   false   ;
    empty   =   true    ;
    header_ptr  =   0;
    footer_prt  =   0;
    for(int i=0;i<OITF_NUM;i++){
        fifo[i].pc      =   0;
        fifo[i].rdfpu   =   0;
        fifo[i].rdidx   =   0;
        fifo[i].rdwen   =   0;
    }
}

void exuOitf::exu(){
    ret_ptr =   footer_prt;
    dis_ptr =   header_ptr;

    if(dis_ena & (!full)){
        fifo[header_ptr].pc     =   disp_i_pc;
        fifo[header_ptr].rdidx  =   disp_i_rdidx;
        fifo[header_ptr].rdfpu  =   disp_i_rdfpu;
        fifo[header_ptr].rdwen  =   disp_i_rdidx;
        header_ptr  =   (header_ptr + 1) % OITF_NUM;
        if(header_ptr == footer_prt){
            full     =   true;
            dis_ready=  false;
        }else{
            full     =   false;
            dis_ready=   true;
        }            
        empty   =   false;  
    }

    if(ret_ena & (!empty)){
        ret_rdidx   =   fifo[footer_prt].rdidx;
        ret_pc      =   fifo[footer_prt].pc;
        ret_rdwen   =   fifo[footer_prt].rdwen;
        ret_rdfpu   =   fifo[footer_prt].rdfpu;
        fifo[footer_prt].rdidx  =   0;
        fifo[footer_prt].pc     =   0;
        fifo[footer_prt].rdwen  =   0;
        fifo[footer_prt].rdfpu  =   0;
        if(header_ptr == footer_prt){
            empty   =   true;
        }else{
            footer_prt  =   (footer_prt + 1) % OITF_NUM;
        }
        full    =   false;
        dis_ready=  true;
    }
    
    bool flag_rs1   =   false;
    bool flag_rs2   =   false;
    bool flag_rs3   =   false;
    bool flag_rd    =   false;
    for(int i=0 ;i < OITF_NUM; i++){
        if(disp_i_rs1en & fifo[i].rdwen & (fifo[i].rdfpu == disp_i_rs1fpu) &
            (disp_i_rs1idx == fifo[i].rdidx) & (disp_i_rs1idx != 0)){
                flag_rs1 = true;
            }
        if(disp_i_rs2en & fifo[i].rdwen & (fifo[i].rdfpu == disp_i_rs2fpu) &
            (disp_i_rs2idx == fifo[i].rdidx) & (disp_i_rs2idx != 0)){
                flag_rs2 = true;
            }
        if(disp_i_rs3en & fifo[i].rdwen & (fifo[i].rdfpu == disp_i_rs3fpu) &
            (disp_i_rs3idx == fifo[i].rdidx) & (disp_i_rs3idx != 0)){
                flag_rs3 = true;
            }
        if(disp_i_rdwen & fifo[i].rdwen & (fifo[i].rdfpu == disp_i_rdfpu) &
            (disp_i_rdidx == fifo[i].rdidx) & (disp_i_rdidx != 0)){
                flag_rd = true;
            }
    }
    oitfrd_match_disprs1    =   flag_rs1;
    oitfrd_match_disprs2    =   flag_rs2;
    oitfrd_match_disprs3    =   flag_rs3;
    oitfrd_match_disprd     =   flag_rd;
    oitf_empty              =   empty;
}