#include <stdio.h>
#include <stdlib.h>
#include "LC-3.h"

u16 memory[MEMORY_MAX];
u16 reg[R_COUNT];

int main(int argc, const char* argv[]) {
    if(argc < 2)
    {
        printf("lc3 [image-file1] ...\n");
        exit(EXIT_FAILURE);
    }

    reg[R_COND] = FL_ZRO;

    enum {PC_START = 0x3000};
    reg[R_PC] = PC_START;

    int running = 1;
    while(running)
    {
        u16 instr = mem_read(reg[R_PC]++);
        u16 op = instr >> 12;

        switch (op) {
            case OP_ADD:
                break;
            case OP_AND:
                break;
            case OP_NOT:
                break;
            case OP_BR:
                break;
            case OP_JMP:
                break;
            case OP_JSR:
                break;
            case OP_LD:
                break;
            case OP_LDI:
                break;
            case OP_LDR:
                break;
            case OP_LEA:
                break;
            case OP_ST:
                break;
            case OP_STI:
                break;
            case OP_STR:
                break;
            case OP_TRAP:
                break;
            case OP_RES:
            case OP_RTI:
            default:
                printf("Invalid opcode");
                return 1;
        }
    }


    return 0;
}
