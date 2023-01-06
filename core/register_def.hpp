#ifndef REGESTER_DEF_HPP
#define REGISTER_DEF_HPP
#include <string>
#include "../common.hpp"

struct PipeReg {
	bool ready,valid;
        std::string asm_str;
        void print_inst();	
};
struct IFReg : public PipeReg{
        reg_t pc;
        void update(const IFReg& c);
        void print();
};
#endif
