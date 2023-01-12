 //disp相当于派遣，将指令送往发射队列；alu相当于发射，将指令从队列送往不同的执行单元
 //alu送往各运算单元执行并返回执行结果
 #include "../common.hpp"
 class exuAlu
 {
 public:
   exuAlu(/* args */);
   ~exuAlu();
   void exu();

   bool     i_valid;          //input
   bool     i_ready;          //output
   bool     i_longpipe;       //output

   bool     amo_wait;         //output
   bool     oitf_empty;       //input
   //disp input
   reg_t    i_itag;           //oitf表项指针
   uint8_t  i_rs1;
   uint8_t  i_rs2; 
   reg_t    i_imm; 
   uint32_t i_info;
   reg_t    i_pc;
   inst_t   i_instr;
   bool     i_pc_vld;
   uint8_t  i_rdidx;
   bool     i_rdwen;
   bool     i_ilegl;
   bool     i_buserr;
   bool     i_misalgn;

   //commit冲刷指示
   bool     flush_req;
   bool     flush_pulse;
   //commit interface
   bool     cmt_o_valid;      //output
   bool     cmt_o_ready;      //input
   bool     cmt_o_pc_vald;    //output
   reg_t    cmt_o_pc;
   inst_t   cmt_o_instr;
   reg_t    cmt_o_imm;
   //branch and jump commit
   bool     cmt_o_rv32;
   bool     cmt_o_bjp;
   bool     cmt_o_mret;
   bool     cmt_o_dret;
   bool     cmt_o_ecall;
   bool     cmt_o_ebreak;
   bool     cmt_o_fencei;
   bool     cmt_o_wfi;
   bool     cmt_o_ifu_misalgn;
   bool     cmt_o_ifu_buserr;
   bool     cmt_o_bjp_prdt;      //预测结果
   bool     cmt_o_bjp_rslv;      //计算的实际结果
   //agu exception
   bool     cmt_o_misalgn;
   bool     cmt_o_ld;
   bool     cmt_o_stamo;
   bool     cmt_o_buserr;
   reg_t    cmt_o_badaddr;
   //ALU write-back interface

 };
 
 exuAlu::exuAlu(/* args */)
 {
 }
 
 exuAlu::~exuAlu()
 {
 }
 