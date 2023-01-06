#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "common.hpp"
#define MBASE 0x80000000
#define MSIZE 0x8000000

#define PMEM_LEFT  ((uint32_t)MBASE)
#define PMEM_RIGHT ((uint32_t)MBASE + MSIZE - 1)
#endif