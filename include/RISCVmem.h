/* RISC-V memory access header file: */

#ifndef RISCVMEM_H_
#define RISCVMEM_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Define memory size and create global memory */
#define MEM_SIZE 4096
extern int32_t mem[];

/* Functions: */

/* Function 'dump_mem':
   Receives a memory address and prints memory content in hex or/and decimal until address specified.
   Inputs: start - initial memory address;
           end - final memory address;
           format - format to the memory be printed, 'h' for hex, 'd' for decimal or 'b' for both.
*/
void dump_mem(uint32_t start, uint32_t end, char format);

/* Fuction 'lw'
   Loads a word (32-bits) from memory.
   Inputs: address - base address from where to load;
           kte - constant to add to address.
   Output: Returns the loaded word.
*/
int32_t lw(uint32_t address, int32_t kte);

/* Fuction 'lh'
   Loads a halfword (16-bits) from memory.
   Inputs: address - base address from where to load;
           kte - constant to add to address.
   Output: Returns the loaded halfword.
*/
int32_t lh(uint32_t address, int32_t kte);

/* Fuction 'lhu'
   Loads an unsigned halfword (16-bits) from memory.
   Inputs: address - base address from where to load;
           kte - constant to add to address.
   Output: Returns the loaded unsigned halfword.
*/
int32_t lhu(uint32_t address, int32_t kte);

/* Fuction 'lb'
   Loads a byte (8-bits) from memory.
   Inputs: address - base address from where to load;
           kte - constant to add to address.
   Output: Returns the loaded byte.
*/
int32_t lb(uint32_t address, int32_t kte);

/* Fuction 'lbu'
   Loads an unsigned byte (8-bits) from memory.
   Inputs: address - base address from where to load;
           kte - constant to add to address.
   Output: Returns the loaded unsigned byte.
*/
int32_t lbu(uint32_t address, int32_t kte);

/* Fuction 'sw'
   Stores a word (32-bits) in memory.
   Inputs: address - base address from where to store;
           kte - constant to add to address;
           dado - data to store.
*/
void sw(uint32_t address, int32_t kte, int32_t dado);

/* Fuction 'sh'
   Stores a halfword (16-bits) in memory.
   Inputs: address - base address from where to store;
           kte - constant to add to address;
           dado - data to store.
*/
void sh(uint32_t address, int32_t kte, int32_t dado);

/* Fuction 'sb'
   Stores a byte (8-bits) in memory.
   Inputs: address - base address from where to store;
           kte - constant to add to address;
           dado - data to store.
*/
void sb(uint32_t address, int32_t kte, int32_t dado);

#endif
