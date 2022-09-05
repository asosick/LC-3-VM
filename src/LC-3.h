//
// Created by August Sosick on 2022-09-05.
//

#ifndef LC_3_VM_LC_3_H
#define LC_3_VM_LC_3_H

#include "constants.h"

//utils
u16 sign_extend(u16 x, u32 bit_count);
void set_condition_codes(u16 r);
void read_image_file(FILE* file);
int read_image(const char* image_path);


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
void and(u16 instr);
void br(u16 instr);
void jmp(u16 instr);
void jsr(u16 instr);
void ld(u16 instr);
void ldi(u16 instr);
void ldr(u16 instr);
void lea(u16 instr);
void not(u16 instr);
void ret(u16 instr);
void rti(u16 instr);
void st(u16 instr);
void sti(u16 instr);
void str(u16 instr);
void trap(u16 instr);


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
void trap_puts();
void trap_getc();
void trap_out();
void trap_in();
void trap_putsp();
void trap_halt();

void trap_branch(u16 instr);

//memory
void mem_write(u16 address, u16 value);
u16 mem_read(u16 address);

//Memory mapped registers
enum MemoryMappedRegisters
{
    MR_KBSR = 0xFE00,    //keyboard status
    MR_KBDR = 0xFE02     //keyboard data
};

//Input buffering
void handle_interrupt(int signal);
void disable_input_buffering();
void restore_input_buffering();
uint16_t check_key();


#endif //LC_3_VM_LC_3_H
