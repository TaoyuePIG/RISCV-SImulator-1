/* RISC-V executer code file: */

#include "./include/RISCVexecuter.h"

/* Functions: */

void dump_reg(char format){
    /* Dump register bank in hex format. */
    if(format == 'h' || format == 'b'){
        printf("\nRegister Dump in Hex:\n");
        printf("-zero = 0x%08X\n", breg[zero]);
        printf("-ra = 0x%08X\n", breg[ra]);
        printf("-sp = 0x%08X\n", breg[sp]);
        printf("-gp = 0x%08X\n", breg[gp]);
        printf("-tp = 0x%08X\n", breg[tp]);
        printf("-t0 = 0x%08X\n", breg[t0]);
        printf("-t1 = 0x%08X\n", breg[t1]);
        printf("-t2 = 0x%08X\n", breg[t2]);
        printf("-s0 = 0x%08X\n", breg[s0]);
        printf("-s1 = 0x%08X\n", breg[s1]);
        printf("-a0 = 0x%08X\n", breg[a0]);
        printf("-a1 = 0x%08X\n", breg[a1]);
        printf("-a2 = 0x%08X\n", breg[a2]);
        printf("-a3 = 0x%08X\n", breg[a3]);
        printf("-a4 = 0x%08X\n", breg[a4]);
        printf("-a5 = 0x%08X\n", breg[a5]);
        printf("-a6 = 0x%08X\n", breg[a6]);
        printf("-a7 = 0x%08X\n", breg[a7]);
        printf("-s2 = 0x%08X\n", breg[s2]);
        printf("-s3 = 0x%08X\n", breg[s3]);
        printf("-s4 = 0x%08X\n", breg[s4]);
        printf("-s5 = 0x%08X\n", breg[s5]);
        printf("-s6 = 0x%08X\n", breg[s6]);
        printf("-s7 = 0x%08X\n", breg[s7]);
        printf("-s8 = 0x%08X\n", breg[s8]);
        printf("-s9 = 0x%08X\n", breg[s9]);
        printf("-s10 = 0x%08X\n", breg[s10]);
        printf("-s11 = 0x%08X\n", breg[s11]);
        printf("-t3 = 0x%08X\n", breg[t3]);
        printf("-t4 = 0x%08X\n", breg[t4]);
        printf("-t5 = 0x%08X\n", breg[t5]);
        printf("-t6 = 0x%08X\n", breg[t6]);
    }

    /* Dump register bank in decimal format. */
    if(format == 'd' || format == 'b'){
        printf("\nRegister Dump in Decimal:\n");
        printf("-zero = %d\n", breg[zero]);
        printf("-ra = %d\n", breg[ra]);
        printf("-sp = %d\n", breg[sp]);
        printf("-gp = %d\n", breg[gp]);
        printf("-tp = %d\n", breg[tp]);
        printf("-t0 = %d\n", breg[t0]);
        printf("-t1 = %d\n", breg[t1]);
        printf("-t2 = %d\n", breg[t2]);
        printf("-s0 = %d\n", breg[s0]);
        printf("-s1 = %d\n", breg[s1]);
        printf("-a0 = %d\n", breg[a0]);
        printf("-a1 = %d\n", breg[a1]);
        printf("-a2 = %d\n", breg[a2]);
        printf("-a3 = %d\n", breg[a3]);
        printf("-a4 = %d\n", breg[a4]);
        printf("-a5 = %d\n", breg[a5]);
        printf("-a6 = %d\n", breg[a6]);
        printf("-a7 = %d\n", breg[a7]);
        printf("-s2 = %d\n", breg[s2]);
        printf("-s3 = %d\n", breg[s3]);
        printf("-s4 = %d\n", breg[s4]);
        printf("-s5 = %d\n", breg[s5]);
        printf("-s6 = %d\n", breg[s6]);
        printf("-s7 = %d\n", breg[s7]);
        printf("-s8 = %d\n", breg[s8]);
        printf("-s9 = %d\n", breg[s9]);
        printf("-s10 = %d\n", breg[s10]);
        printf("-s11 = %d\n", breg[s11]);
        printf("-t3 = %d\n", breg[t3]);
        printf("-t4 = %d\n", breg[t4]);
        printf("-t5 = %d\n", breg[t5]);
        printf("-t6 = %d\n", breg[t6]);
    }
}

void InitiateReg(){
    /* Initialize register bank with zero. */
    for(int i = 0; i < BREG_SIZE; i++){
        breg[i] = 0;
    }

    pc = 0; // Default value for progam counter
    ri = 0; // Default value for ri
    breg[sp] = 0x3ffc; // Default value for stack pointer
    breg[gp] = 0x1800; // Default value for global area
    end = 1; // Inform that end of progam has not been reached
}

void fetch(){
    /* Read next instruction from memory */
    ri = lw(pc, 0);
    /* Increment program counter. */
    pc += 4;
}

void decode(){
    /* Declare temporary variables. */
    uint32_t temp, temp2, temp3, temp4;

    // Get opcode
    temp = ri & 0x7F;
    instCamps.opcode = (uint8_t) temp;

    // Get rs1
    temp = ri & 0xF8000;
    temp = temp >> 15;
    instCamps.rs1 = (uint8_t) temp;

    // Get rs2
    temp = ri & 0x1F00000;
    temp = temp >> 20;
    instCamps.rs2 = (uint8_t) temp;

    // Get rd
    temp = ri & 0xF80;
    temp = temp >> 7;
    instCamps.rd = (uint8_t) temp;

    // Get shamt
    instCamps.shamt = instCamps.rs2;

    // Get funct3
    temp = ri & 0x7000;
    temp = temp >> 12;
    instCamps.funct3 = (uint8_t) temp;

    // Get funct7
    temp = ri & 0xFE000000;
    temp = temp >> 25;
    instCamps.funct7 = (uint8_t) temp;

    // Get imm12_i
    temp = ri & 0xFFF00000;
    temp2 = temp & 0x80000000;
    temp = temp >> 20;
    if(temp2 != 0){
        temp = temp + 0xFFFFF000;
    }
    instCamps.imm12_i = (int16_t) temp;

    // Get imm12_s
    temp = ri & 0xFE000000;
    temp3 = temp & 0x80000000;
    temp = temp >> 13;
    temp2 = ri & 0xF80;
    temp = temp + temp2;
    temp = temp >> 7;
    if(temp3 != 0){     // Extend sign if needed
        temp = temp + 0xFFFFF000;
    }
    instCamps.imm12_s = (int16_t) temp;

    // Get imm13
    temp4 = ri & 0x80000000; // get bit 12
    temp = ri & 0x7E000000;  // get bits 10-5
    temp = temp >> 13;      // put temp on the position before bits 4-1
    temp2 = ri & 0xF00;     // get bits 4-1
    temp = temp + temp2;    // put bits 4-1 and 10-5 together
    temp = temp >> 7;       // shift right, leaving a 0 for bit 0
    temp3 = ri & 0x80;      // get bit 11
    // if bit 11 is '1', put it in temp
    if(temp3 != 0){
        temp = temp + 0x800;
    }
    // if signal bit is '1', extend signal
    if(temp4 != 0){
        temp = temp + 0xFFFFF000;
    }
    instCamps.imm13 = (int16_t) temp; 

    // Get imm20_u
    temp = ri & 0xFFFFF000;
    instCamps.imm20_u = (int32_t) temp;

    // Get imm21
    temp4 = ri & 0x80000000; // get bit 20
    temp = ri & 0x7FE00000;  // get bits 10-1
    temp = temp >> 20;      // put bits 10-1 in its positions
    temp2 = ri & 0xFF000;     // get bits 19-12
    temp = temp + temp2;    // put bits 19-12 and 10-1 together
    temp3 = ri & 0x100000;      // get bit 11
    // if bit 11 is '1', put it in temp
    if(temp3 != 0){
        temp = temp + 0x800;
    }
    // if signal bit is '1', extend signal
    if(temp4 != 0){
        temp = temp + 0xFFF00000;
    }
    instCamps.imm21 = (int16_t) temp; 
}

void execute(){
    uint32_t pca = pc-4; // Get actual program counter value
    uint32_t temp; // temporary variable
    int32_t i = 0; // auxiliar variable
    char c; // temporary char variable

    switch(instCamps.opcode){
        case LUI:
            breg[instCamps.rd] = instCamps.imm20_u;
            break;

        case AUIPC:
            breg[instCamps.rd] = pca + instCamps.imm20_u;
            break;

        case JAL:
            breg[instCamps.rd] = pc;
            pc = pca + instCamps.imm21;
            break;

        case JALR:
            if(instCamps.rd != 0){
                breg[instCamps.rd] = pc;
            }
            pc = (breg[instCamps.rs1] + instCamps.imm12_i) & ~1;
            break;
        
        case BType:
            switch(instCamps.funct3){
                case BEQ3:
                    if(breg[instCamps.rs1] == breg[instCamps.rs2]){
                        pc = pca + instCamps.imm13;
                    }
                    break;
                case BNE3:
                    if(breg[instCamps.rs1] != breg[instCamps.rs2]){
                        pc = pca + instCamps.imm13;
                    }
                    break;
                case BLT3:
                    if(breg[instCamps.rs1] < breg[instCamps.rs2]){
                        pc = pca + instCamps.imm13;
                    }
                    break;
                case BGE3:
                    if(breg[instCamps.rs1] >= breg[instCamps.rs2]){
                        pc = pca + instCamps.imm13;
                    }
                    break;
                case BLTU3:
                    if((uint32_t) breg[instCamps.rs1] < (uint32_t)breg[instCamps.rs2]){
                        pc = pca + instCamps.imm13;
                    }
                    break;
                case BGEU3:
                    if((uint32_t) breg[instCamps.rs1] >= (uint32_t)breg[instCamps.rs2]){
                        pc = pca + instCamps.imm13;
                    }
                    break;
            } // switch funct3
            break; // case BType
        
        case ILType:
            switch(instCamps.funct3){
                case LB3:
                    breg[instCamps.rd] = lb(breg[instCamps.rs1], instCamps.imm12_i);
                    break;
                case LH3:
                    breg[instCamps.rd] = lh(breg[instCamps.rs1], instCamps.imm12_i);
                    break;
                case LW3:
                    breg[instCamps.rd] = lw(breg[instCamps.rs1], instCamps.imm12_i);
                    break;
                case LBU3:
                    breg[instCamps.rd] = lbu(breg[instCamps.rs1], instCamps.imm12_i);
                    break;
                case LHU3:
                    breg[instCamps.rd] = lhu(breg[instCamps.rs1], instCamps.imm12_i);
                    break;
            } // switch funct3
            break; // case ILType
        
        case StoreType:
            switch(instCamps.funct3){
                case SB3:
                    sb(breg[instCamps.rs1], instCamps.imm12_s, breg[instCamps.rs2]);
                    break;
                case SH3:
                    sh(breg[instCamps.rs1], instCamps.imm12_s, breg[instCamps.rs2]);
                    break;
                case SW3:
                    sw(breg[instCamps.rs1], instCamps.imm12_s, breg[instCamps.rs2]);
                    break;
            } // switch funct3
            break; // case StoreType

        case ILAType:
            switch(instCamps.funct3){
                case ADDI3:
                    breg[instCamps.rd] = breg[instCamps.rs1] + instCamps.imm12_i;
                    break;
                case ORI3:
                    breg[instCamps.rd] = breg[instCamps.rs1] | instCamps.imm12_i;
                    break;
                case SLTI3:
                    breg[instCamps.rd] = breg[instCamps.rs1] < instCamps.imm12_i;
                    break;
                case XORI3:
                    breg[instCamps.rd] = breg[instCamps.rs1] ^ instCamps.imm12_i;
                    break;
                case ANDI3:
                    breg[instCamps.rd] = breg[instCamps.rs1] & instCamps.imm12_i;
                    break;
                case SLTIU3:
                    temp = (uint32_t) breg[instCamps.rs1] < (uint32_t) instCamps.imm12_i;
                    breg[instCamps.rd] = (int32_t) temp;
                    break;
                case SLLI3:
                    breg[instCamps.rd] = breg[instCamps.rs1] << instCamps.shamt;
                    break;
                case SRI3:
                    switch(instCamps.funct7){
                        case SRLI7:
                            temp = (uint32_t) breg[instCamps.rs1] >> instCamps.shamt;
                            breg[instCamps.rd] = (int32_t) temp;
                            break;
                        case SRAI7:
                            breg[instCamps.rd] = breg[instCamps.rs1] >> instCamps.shamt;
                            break;
                    } // switch funct7
                    break; // case SRI3   
            }
            break; // case ILAType
        
        case RegType:
            switch(instCamps.funct3){
                case ADDSUB3:
                    switch(instCamps.funct7){
                        case ADD7:
                            breg[instCamps.rd] = breg[instCamps.rs1] + breg[instCamps.rs2];
                            break;
                        case SUB7:
                            breg[instCamps.rd] = breg[instCamps.rs1] - breg[instCamps.rs2];
                            break;
                    } // switch funct7
                    break; // case ADDSUB3
                case SLL3:
                    breg[instCamps.rd] = breg[instCamps.rs1] << breg[instCamps.rs2];
                    break;
                case SLT3:
                    breg[instCamps.rd] = breg[instCamps.rs1] < breg[instCamps.rs2];
                    break;
                case SLTU3:
                    breg[instCamps.rd] = (uint32_t) breg[instCamps.rs1] + (uint32_t) breg[instCamps.rs2];
                    break;
                case XOR3:
                    breg[instCamps.rd] = breg[instCamps.rs1] ^ breg[instCamps.rs2];
                    break;
                case SR3:
                    switch(instCamps.funct7){
                        case SRA7:
                            breg[instCamps.rd] = breg[instCamps.rs1] >> breg[instCamps.rs2];
                            break;
                        case SRL7:
                            temp = (uint32_t) breg[instCamps.rs1] >> (uint32_t) breg[instCamps.rs2];
                            breg[instCamps.rd] = (int32_t) temp; 
                            break;
                    } // switch funct7
                    break; // case SR3
                case OR3:
                    breg[instCamps.rd] = breg[instCamps.rs1] | breg[instCamps.rs2];
                    break;
                case AND3:
                    breg[instCamps.rd] = breg[instCamps.rs1] & breg[instCamps.rs2];
                    break;
            } // switch funct3
            break; // case RegType
        
        case ECALL:
            switch(breg[a7]){
                case PRINT_INT:
                    printf("%d", breg[a0]);
                    break;
                case PRINT_STRING:
                    c = lb((uint32_t)breg[a0], 0);
                    while(c != '\0'){
                        printf("%c", c);
                        i++;
                        c = lb((uint32_t)breg[a0], i);
                    }
                    break; // case PRINT_STRING
                case EXIT:
                    end = 0; // Indicates program has reached its end
                    break;
            } // switch breg[a7]
            break; // case ECALL
    } // switch opcode
    
    /* Make sure register 'zero' cointains 0 as value */
    breg[zero] = 0;
}

void step(){
    fetch();
    decode();
    execute();
}

void run(){
    InitiateReg();
    
    printf("\n-- program started running --\n\n");

    /* Run step() unitl it reaches end of text memory or an end syscall has been called */
    while(end && (pc < 1024*4)){
        step();
    }

    printf("\n\n-- program is finished running --\n\n");
}
