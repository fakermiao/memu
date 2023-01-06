#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#include "../common.hpp"
void init_rand();
void init_log(const char *log_file);
void init_mem();
void init_isa();
void init_difftest(char *ref_so_file,long img_size,int port);
void init_sdb();

uint8_t* guest_to_host(uint32_t paddr);

void sdb_set_batch_mode();

static void welcome(){
    Log("Build time:%s,%s",__TIME__,__DATE__);
    printf("Welcome to %s!\n",ANSI_FMT("RISC V-MEMU", ANSI_FG_YELLOW ANSI_BG_RED));
    printf("For help,type \"help\"\n");
}

static char *log_file = NULL;
static char *diff_so_file = NULL;
static char *img_file = NULL;
//static int difftest_port = 1234;

static long load_img(){
    if(img_file == NULL){
        Log("No image is given. Use the default build-in image.");
        return 4096; // built-in image size
    }
    FILE *fp = fopen(img_file, "rb");
    Assert(fp, "Can not open '%s'", img_file);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    Log("The image is %s, size = %ld", img_file, size);

    fseek(fp, 0, SEEK_SET);
    int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
    assert(ret == 1);

    fclose(fp);
    Log("hello");
    return size;
}

static int parse_args(int argc,char *argv[]){
    const struct option table[] =
    {
        /* data */
        {"batch"    ,no_argument       ,NULL,'b'},
        {"log"      ,required_argument ,NULL,'l'},
        {"diff"     ,required_argument ,NULL,'d'},
        {"help"     ,required_argument ,NULL,'h'},
        {0          ,0                 ,NULL, 0},
    };
    int o;
    while ((o = getopt_long(argc,argv,"-bhl:d:",table,NULL)) != -1)
    {
        switch (o)
        {
            case 'b': sdb_set_batch_mode(); break;
            case 'l': log_file = optarg; break;
            case 'd': diff_so_file = optarg; break;
            case 1: img_file = optarg; return 0;
            default:
                printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
                printf("\t-b,--batch              run with batch mode\n");
                printf("\t-l,--log=FILE           output log to FILE\n");
                printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
                printf("\n");
                break;
        }
    }
    
    return 0;
}

void init_monitor(int argc,char *argv[]){
    parse_args(argc,argv);
    /* Set random seed. */
    init_rand();

    /* Open the log file. */
    init_log(log_file);

    /* Initialize memory. */
    init_mem();

    /* Initialize devices.暂时不需要 */
    //init_device();

    /* Perform ISA dependent initialization. */
    init_isa();

    /* Load the image to memory. This will overwrite the built-in image. */
    long img_size = load_img();
    img_size++;

    /* Initialize differential testing. */
    //init_difftest(diff_so_file, img_size, difftest_port);

    /* Initialize the simple debugger. */
    //init_sdb();

    //init_disasm();--------反汇编指令，暂时不需要

    /* Display welcome message. */
    welcome();
    return ;
}

void init_rand(){
    srand(time(0));
}

FILE *log_fp = NULL;

void init_log(const char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
static const uint32_t img [] = {
  0x00000297,  // auipc t0,0
  0x0002b823,  // sd  zero,16(t0)
  0x0102b503,  // ld  a0,16(t0)
  0x00100073,  // ebreak (used as nemu_trap)
  0xdeadbeef,  // some data
};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = RESET_VECTOR;

  /* The zero register is always 0. */
  cpu.gpr[0] = 0;
}

void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
}