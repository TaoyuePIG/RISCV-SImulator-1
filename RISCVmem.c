/* RISC-V memory access code file: */

#include "./include/RISCVmem.h"

int32_t mem[MEM_SIZE];

/* Functions: */

void dump_mem(uint32_t start, uint32_t end, char format){
    // Verify if start is a 4 multiple, if not, round to the 4 multiple before addr
    while( start % 4 != 0){
        start--;
    }

    // Verify if addr exceeds memory size, if it does, return
    if(start >= MEM_SIZE*4){
        printf("ERROR: Address surprass memory size\n\n");
        return;
    }

    // Verify if end is greater than start
    if(start > end){
        printf("ERROR: 'start' is greater than 'end'\n\n");
        return;
    }

    // Dump memory
    for(uint32_t i = start; (i <= end) && (i < MEM_SIZE*4); i += 4){
        if((format == 'h') || (format == 'b')){
            printf("-mem[0x%08X] = 0x%08X\n", i, mem[i/4]);
        }
        if((format == 'd') || (format == 'b')){
            printf("mem[0x%08X] = %d\n", i, mem[i/4]);
        }
    }
}

int32_t lw(uint32_t address, int32_t kte){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Verify if address is aligned with memory
    if( addr % 4 != 0){
        printf("ERROR: Load address not aligned to word boundary");
        exit(1);
    }

    // Get word on memory and return
    int32_t ret = mem[address/4];

    return ret;
}

int32_t lh(uint32_t address, int32_t kte){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Verify if address is aligned with memory
    if( addr % 2 != 0){
        printf("ERROR: Load address not aligned to halfword boundary");
        exit(1);
    }

    // Get word address where halfword is
    uint32_t word_addr = address;
    if( word_addr % 4 != 0){
        word_addr -= 2;
    }

    // Get halfword on memory and return
    int32_t ret = mem[word_addr/4];
    // Case when halfword if on the least significant halfword
    if(word_addr == address){
        ret = ret << 16;
    }
    ret = ret >> 16;

    return ret;
}

int32_t lhu(uint32_t address, int32_t kte){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Verify if address is aligned with memory
    if( addr % 2 != 0){
        printf("ERROR: Load address not aligned to halfword boundary");
        exit(1);
    }

    // Get word address where halfword is
    uint32_t word_addr = address;
    if( word_addr % 4 != 0){
        word_addr -= 2;
    }

    // Get halfword on memory and return
    uint32_t ret = (uint32_t)mem[word_addr/4];
    // Case when halfword if on the least significant halfword
    if(word_addr == address){
        ret = ret << 16;
        ret = ret >> 16;
    }
    // Case when halfword if on the most significant halfword
    else{
        ret = ret >> 16;
    }

    return (int32_t)ret;
}

int32_t lb(uint32_t address, int32_t kte){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Get word address where byte is
    uint32_t word_addr = address;
    while( word_addr % 4 != 0){
        word_addr--;
    }

    // Get byte on memory and return:
    int32_t ret = mem[word_addr/4];
    // Get difference between memory address and byte address
    int32_t position = address - word_addr;
    // Shift ret to the left acording to position
    ret = ret << 8*(3-position);
    // Shift right to take byte to the least significant position
    ret = ret >> 24;

    return ret;
}

int32_t lbu(uint32_t address, int32_t kte){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Get word address where byte is
    uint32_t word_addr = address;
    while( word_addr % 4 != 0){
        word_addr--;
    }

    // Get byte on memory and return:
    uint32_t ret = (uint32_t)mem[word_addr/4];
    // Get difference between memory address and byte address
    int32_t position = address - word_addr;
    // Shift ret to the left acording to position
    ret = ret << 8*(3-position);
    // Shift right to take byte to the least significant position
    ret = ret >> 24;

    return (int32_t)ret;
}

void sw(uint32_t address, int32_t kte, int32_t dado){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Verify if address is aligned with memory
    if( addr % 4 != 0){
        printf("ERROR: Store address not aligned to word boundary\n\n");
        return;
    }

    // Get word on memory and return
    mem[address/4] = dado;
}

void sh(uint32_t address, int32_t kte, int32_t dado){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Verify if address is aligned with memory
    if( addr % 2 != 0){
        printf("ERROR: Store address not aligned to halfword boundary\n\n");
        return;
    }

    // Get word address where halfword is
    uint32_t word_addr = address;
    if( word_addr % 4 != 0){
        word_addr -= 2;
    }

    // Read memory content
    int32_t mem_data = mem[word_addr/4];

    // Get difference between memory address and halfword address
    int32_t position = address - word_addr;

    // Create mask with what needs to continue on memory
    int32_t mask;
    switch(position){
        case 0:
            mask = 0xFFFF0000;
        break;
        case 2:
            mask = 0x0000FFFF;
        break;
    }

    // Shift data acording to position
    dado = dado << 8*position;

    // Use mask to clear area where data will go on mem_data
    mem_data &= mask;
    // Use negated mask to clear area on data that cant me modified on mem_data
    dado &= ~(mask);

    // Store
    mem[word_addr/4] = mem_data + dado;
}

void sb(uint32_t address, int32_t kte, int32_t dado){
    // Add kte with address
    int32_t addr = (int32_t)address + kte;
    address = (uint32_t)addr;

    // Get word address where halfword is
    uint32_t word_addr = address;
    while( word_addr % 4 != 0){
        word_addr--;
    }

    // Read memory content
    int32_t mem_data = mem[word_addr/4];

    // Get difference between memory address and byte address
    int32_t position = address - word_addr;

    // Create mask with what needs to continue on memory
    int32_t mask;
    switch(position){
        case 0:
            mask = 0xFFFFFF00;
        break;
        case 1:
            mask = 0xFFFF00FF;
        break;
        case 2:
            mask = 0xFF00FFFF;
        break;
        case 3:
            mask = 0x00FFFFFF;
    }

    // Shift data acording to position
    dado = dado << 8*position;

    // Use mask to clear area where data will go on mem_data
    mem_data &= mask;
    // Use negated mask to clear area on data that cant me modified on mem_data
    dado &= ~(mask);

    // Store
    mem[word_addr/4] = mem_data + dado;
}
