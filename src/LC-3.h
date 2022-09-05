//
// Created by August Sosick on 2022-09-05.
//

#ifndef LC_3_VM_LC_3_H
#define LC_3_VM_LC_3_H

#include "stdint.h"

#define MEMORY_MAX (1<<16)
#define u16 uint16_t
#define u32 uint32_t
#define s16 int16_t
#define s32 int32_t



//Registers
enum Registers
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

//opcodes RISC
enum Opcodes
{
    OP_BR = 0,  //branch
    OP_ADD,     //add
    OP_LD,      //load
    OP_ST,      //store
    OP_JSR,     //jump register
    OP_AND,     //bitwise and
    OP_LDR,     //load register
    OP_STR,     //store register
    OP_RTI,     //unused
    OP_NOT,     //bitwise not
    OP_LDI,     //load indirect
    OP_STI,     //store indirect
    OP_JMP,     //jump
    OP_RES,     //reserved
    OP_LEA,     //load effective address
    OP_TRAP     //execute trap
};

void add(u16 instr);

//Condition Flags (stored information about previous calculation)
enum Conditions
{
    FL_POS = 1 << 0,    //Result was positive
    FL_ZRO = 1 << 1,    //Result was zero
    FL_NEG = 1 << 2,    //Result was negative
};

//Traps
enum TRAPS
{
    TRAP_GETC = 0x20,   //get char from keyboard
    TRAP_OUT = 0x21,    //output a char
    TRAP_PUTS = 0x22,   //output a word string
    TRAP_IN = 0x23,     //get character from keyboard and echo out
    TRAP_PUTSP = 0x24,  //output a byte string
    TRAP_HALT = 0x25    //halt the program
};
void trap_branch(u16 instr);

#endif //LC_3_VM_LC_3_H
