#ifndef COMMON_HPP
#define COMMON_HPP
    #define ANSI_FG_BLACK   "\33[1;30m"
    #define ANSI_FG_RED     "\33[1;31m"
    #define ANSI_FG_GREEN   "\33[1;32m"
    #define ANSI_FG_YELLOW  "\33[1;33m"
    #define ANSI_FG_BLUE    "\33[1;34m"
    #define ANSI_FG_MAGENTA "\33[1;35m"
    #define ANSI_FG_CYAN    "\33[1;36m"
    #define ANSI_FG_WHITE   "\33[1;37m"
    #define ANSI_BG_BLACK   "\33[1;40m"
    #define ANSI_BG_RED     "\33[1;41m"
    #define ANSI_BG_GREEN   "\33[1;42m"
    #define ANSI_BG_YELLOW  "\33[1;43m"
    #define ANSI_BG_BLUE    "\33[1;44m"
    #define ANSI_BG_MAGENTA "\33[1;35m"
    #define ANSI_BG_CYAN    "\33[1;46m"
    #define ANSI_BG_WHITE   "\33[1;47m"
    #define ANSI_NONE       "\33[0m"

    #define ANSI_FMT(str, fmt) fmt str ANSI_NONE
    #define _Log(...) \
        do { \
            printf(__VA_ARGS__); \
        } while (0)

    #include <cstdint>
    #include <stdio.h>
    #include <assert.h>
    #include <string.h>
    typedef uint32_t reg_t;
    typedef uint32_t inst_t;
    #define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
    #define RESET_VECTOR 0X80000000
    #define REG_N 32
    inline reg_t getbits(inst_t inst, int start, int count, int shamt = 0){
        return ((inst >> start) & ((1 << count) - 1)) << shamt;
    }
    inline reg_t zero_extended(reg_t reg, int bits){
        return (reg & (-1ULL >> (64 - bits)));
    }
    inline reg_t sign_extended(reg_t reg, int bits){
        reg = (-1ULL << bits) | reg;
        reg += (((reg >> (bits - 1)) & 1) ^ 1) << bits;
        return reg;
    }

    #define Log(format, ...) \
    _Log(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)


    #define Assert(cond, format, ...) \
        do { \
            if (!(cond)) { \
                extern FILE* log_fp; fflush(log_fp); \
                extern void assert_fail_msg(); \
                assert_fail_msg(); \
                assert(cond); \
            } \
        } while (0)

    #define PG_ALIGN __attribute((aligned(4096)))
    #define FMT_PADDR "0x%016"PRIx64

    struct CPU_state
    {
        reg_t gpr[32];
        reg_t pc;
    };
    extern CPU_state cpu;
#endif