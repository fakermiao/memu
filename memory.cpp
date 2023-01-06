#include <stdint.h>
#include <stdlib.h>
#include "memory.hpp"

static uint8_t pmem[MSIZE] PG_ALIGN = {};

uint8_t* guest_to_host(uint32_t paddr) { return pmem + paddr - MBASE; }
uint32_t host_to_guest(uint8_t *haddr) { return haddr - pmem + MBASE; }

void init_mem(){
  uint32_t *p = (uint32_t *)pmem;
  for(int i = 0;i < (int) (MSIZE / sizeof(p[0])); i++){
    p[i] = rand();
  }
  Log("physical memory area [" "0x%016x" ", " "0x%016x" "]", PMEM_LEFT, PMEM_RIGHT);
}

static inline reg_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    //case 8: return *(uint64_t *)addr;
    default: return 0;
  }
}

static inline void host_write(void *addr, int len, reg_t data) {
  switch (len) {
    case 1: *(uint8_t  *)addr = data; return;
    case 2: *(uint16_t *)addr = data; return;
    case 4: *(uint32_t *)addr = data; return;
    //case 8: *(uint64_t *)addr = data; return;
    default: return;
  }
}
reg_t paddr_read(reg_t addr,int len){
  return host_read(guest_to_host(addr),len);//没有out-of-bound越界检查
}
void paddr_write(reg_t addr,int len,reg_t data){
  host_write(guest_to_host(addr),len,data);//没有out-of-bound越界检查
}
