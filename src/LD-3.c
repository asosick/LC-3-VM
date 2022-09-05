#include <stdio.h>
#include <stdlib.h>
#include "LC-3.h"

u16 mem[MEMORY_MAX];
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
                trap_branch(instr);
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

void trap_branch(u16 instr)
{
    reg[R_R7] = reg[R_PC];

    switch(instr & 0xFF)
    {
        case TRAP_GETC:
            break;
        case TRAP_OUT:
            break;
        case TRAP_PUTS:
            break;
        case TRAP_IN:
            break;
        case TRAP_PUTSP:
            break;
        case TRAP_HALT:
            break;
        default:
            printf("Unrecognized trap code");
            exit(EXIT_FAILURE);
    }
}

u16 sign_extend(u16 x, u32 bit_count)
{
    if((x >> (bit_count)) & 0x1)
    {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

void set_condition_codes(u16 r)
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

/* trap implementations */
void trap_puts()
{
    u16* c = mem + reg[R_R0];
    while(*c)
    {
        putc((char)*c, stdout);
        ++c;
    }
    fflush(stdout);
}

void trap_getc()
{
    reg[R_R0] = (u16)getchar();
}

void trap_out()
{
    putc((char)reg[R_R0], stdout);
    fflush(stdout);
}

void trap_in()
{
    printf("Please enter char..");
    char c = getchar();
    putc(c, stdout);
    fflush(stdout);
    reg[R_R0] = (u16)c;
    set_condition_codes(R_R0);
}

void trap_putsp()
{
    u16* w = memory + reg[R_R0];
    while(*w)
    {
        char char1 = (*w) & 0xFF;
        putc(char1, stdout);
        char char2 = (*w) >> 8;
        if(char2) putc(char2, stdout);
        ++w;
    }
    fflush(stdout);
}

void trap_halt()
{
    printf("Halting Execution");
    exit(EXIT_SUCCESS);
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
    set_condition_codes(dr);
}

void and(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 sr1 = (instr >> 6) & 0x7;
    u16 imm_flag = (instr >> 5) & 0x1;

    if(imm_flag)
    {
        u16 imm5 = sign_extend(instr & 0x1F, 5);
        reg[dr] = reg[sr1] & imm5;
    }
    else
    {
        u16 sr2 = instr & 0x7;
        reg[dr] = reg[sr1] & reg[sr2];
    }
    set_condition_codes(reg[dr]);
}

void br(u16 instr)
{
    u16 n_flag = (instr >> 11) & 0x1;
    u16 z_flag = (instr >> 10) & 0x1;
    u16 p_flag = (instr >> 9) & 0x1;

    if(    (n_flag && reg[R_COND] == FL_NEG)
        || (z_flag && reg[R_COND] == FL_ZRO)
        || (p_flag && reg[R_COND] == FL_POS))
    {
        u16 pcoffset9 = sign_extend(instr & 0x1FF, 9);
        reg[R_PC] += pcoffset9;
    }
}

void jmp(u16 instr)
{
    u16 base_r = (instr >> 6) & 0x7;
    if(base_r == R_R7)
    {
        reg[R_PC] = reg[R_R7];
    }
    else
    {
        reg[R_PC] = reg[base_r];
    }
}

void jsr(u16 instr)
{
    reg[R_R7] = reg[R_PC];

    u16 r_flag = (instr >> 11) & 0x1;
    if(r_flag == 0)
    {
        u16 base_r = (instr >> 6) & 0x7;
        reg[R_PC] = reg[base_r];
    }
    else
    {
        u16 pcoffset11 = sign_extend(instr & 0x7FF, 11);
        reg[R_PC] += pcoffset11;
    }
}

void ld(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 pcoffset9 = sign_extend(instr & 0x1FF, 9);

    u16 loaded = mem[reg[R_PC] + pcoffset9];
    reg[dr] = loaded;
    set_condition_codes(loaded);
}

void ldi(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 pcoffset9 = sign_extend(instr & 0x1FF, 9);

    u16 loaded = mem(mem[reg[R_PC] + pcoffset9]);
    reg[dr] = loaded;
    set_condition_codes(loaded);
}

void ldr(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 base_r = (instr >> 6) & 0x7;
    u16 offset6 = sign_extend(instr & 0x3F, 6);

    u16 loaded = mem[base_r + offset6];
    reg[dr] = loaded;
    set_condition_codes(loaded);
}

void lea(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 pcoffset9 = sign_extend(instr & 0x1FF, 9);
    reg[dr] = reg[R_PC] + pcoffset9;
    set_condition_codes(reg[dr]);
}

void not(u16 instr)
{
    u16 dr = (instr >> 9) & 0x7;
    u16 sr = (instr >> 6) & 0x7;
    u16 bitwise_complement = ~sr;
    reg[dr] = bitwise_complement;
    set_condition_codes(bitwise_complement); //double check this
}

void ret(u16 instr)
{
    reg[R_PC] = reg[R_R7];
}

void rti(u16 instr)
{
    abort();
}

void st(u16 instr)
{
    u16 sr = (instr >> 9) & 0x7;
    u16 pcoffset9 = sign_extend(instr & 0x1FF, 9);
    mem[reg[R_PC] + pcoffset9] = reg[sr];
}

void sti(u16 instr)
{
    u16 sr = (instr >> 9) & 0x7;
    u16 pcoffset9 = sign_extend(instr & 0x1FF, 9);
    mem[mem[reg[R_PC] + pcoffset9]] = reg[sr];
}

void str(u16 instr)
{
    u16 sr = (instr >> 9) & 0x7;
    u16 base_r = (instr >> 6) & 0x7;
    u16 pcoffset6 = sign_extend(instr & 0x3F, 6);

    mem[base_r + pcoffset6] = reg[sr];
}

void trap(u16 instr)
{
    reg[R_R7] = reg[R_PC];
    u16 trapvect8 = instr & 0xFF;
    reg[R_PC] = mem[trapvect8];
}