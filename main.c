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
                add(instr);
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


u16 sign_extend(u16 x, u32 bit_count)
{
    if((x >> (bit_count)) & 0x1)
    {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

void update_flags(u16 r)
{
    if(reg[r] == 0)
    {
        reg[R_COND] = FL_ZRO;
    }
    else if (reg[r] >> 15)
    {
        reg[R_COND] = FL_NEG;
    }
    else
    {
        reg[R_COND] = FL_POS;
    }
}



/* opcode implementations */
void add(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 sr1 = (instr >> 6) & 0x7;
    u16 imm_flag = (instr >> 5) & 0x1;

    if(imm_flag)
    {
        u16 imm5 = sign_extend(instr & 0x1F, 5);
        reg[dr] = reg[sr1] + imm5;
    }
    else
    {
        u16 sr2 = instr & 0x7;
        reg[dr] = reg[sr1] & reg[sr2];
    }
    update_flags(dr);
}

