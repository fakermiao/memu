 //disp相当于派遣，将指令送往发射队列；alu相当于发射，将指令从队列送往不同的执行单元
 //alu送往各运算单元执行并返回执行结果
 class exuAlu
 {
 public:
    exuAlu(/* args */);
    ~exuAlu();
    void exu();
    
 };
 
 exuAlu::exuAlu(/* args */)
 {
 }
 
 exuAlu::~exuAlu()
 {
 }
 