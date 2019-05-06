/* RISC-V executer header file: */

#ifndef RISCVEXECUTE_H_
#define RISCVEXECUTE_H_

#include "RISCVmem.h"

/* Registers: */
#define BREG_SIZE 32
static int32_t pc, ri, breg[BREG_SIZE];

/* Instruction camps: */
static struct InstCamps{
    uint8_t opcode;
    uint8_t rs1,rs2,rd;
    uint8_t shamt;
    uint8_t funct3, funct7;
    int16_t imm12_i, imm12_s, imm13;
    int32_t imm20_u, imm21;
}  instCamps;

/* Registers enum */
enum REGISTERS{
    zero = 0, ra = 1, sp, gp, tp, t0, t1, t2, s0,
    s1, a0, a1, a2, a3, a4, a5, a6, a7, s2, s3, s4,
    s5, s6, s7, s8, s9, s10, s11, t3, t4, t5, t6
};

/* Enum for opcodes. */
enum OPCODES {  // lembrem que so sao considerados os 7 primeiros bits dessas constantes 
    LUI = 0x37, AUIPC = 0x17,    // atribui 20 bits mais significativos 
    ILType = 0x03,    // Load type 
    BType = 0x63,     // branch condicional 
    JAL = 0x6F, JALR = 0x67,     // jumps - JAL formato UJ, JALR formato I 
    StoreType = 0x23, // store 
    ILAType = 0x13,   // logico-aritmeticas com imediato 
    RegType = 0x33,   // operacoes LA com registradores 
    ECALL = 0x73      // chamada do sistema - formato I 
};

/* Enum for funct3 auxiliary camp. */
enum FUNCT3 { // campo auxiliar de 3 bits 
    BEQ3=0,  BNE3=01, BLT3=04,  BGE3=05,  BLTU3=0x06,  BGEU3=07,     // branches 
    LB3=0,   LH3=01,  LW3=02,  LBU3=04,  LHU3=05,     // loads 
    SB3=0,   SH3=01, SW3=02,  // stores 
    ADDSUB3=0,  SLL3=01,  SLT3=02,  SLTU3=03, // LA com 
    XOR3=04,  SR3=05,  OR3=06,  AND3=07, // registradores 
    ADDI3=0,  ORI3=06,  SLTI3=02,  XORI3=04,  ANDI3=07, // LA com  
    SLTIU3=03,  SLLI3=01,  SRI3=05    // imediatos     
};

/* Enum for funct7 auxiliary camp. */
enum FUNCT7 {  // campo auxiliar de 7 bits para as instrucoes SRLI/SRAI, ADD/SUB, SRL/SRA 
    ADD7=0, SUB7=0x20, SRA7=0x20, SRL7=0, SRLI7=0x00, SRAI7=0x20 
};

/* Enum for availiable system calls. */
enum SYSCALLS {
    PRINT_INT = 1, PRINT_STRING = 4, EXIT = 10
};

/* Variable to inform end of program */
extern uint8_t end;

/* Functions: */

/* Function 'dump_reg':
   Dup the content of tegister bank in hex and/or decimal.
   Input: format - format to the register content be printed, 'h' for hex, 'd' for decimal or 'b' for both. 
*/
void dump_reg(char format);

/* Function 'InitiateReg':
   Initiate register values. 
*/
void InitiateReg();

/* Function 'fetch':
   Get the next instruction, put it in ri and update pc.
*/ 
void fetch();

/* Function 'decode':
   Get the instruction word and decode it into the instruction camps.
*/ 
void decode();

/* Function 'execute':
   Execute the apropriate function, acording to instruction.
*/ 
void execute();

/* Function 'step':
   Make a RISC-V step: fetch()->decode()->execute()
*/ 
void step();

/* Funtion 'run':
   Execute a program until 2Kwords executed or syscall
*/ 
void run();

#endif
