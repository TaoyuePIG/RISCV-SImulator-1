/* Main for RISC-V Simulator */

#include "./include/RISCVfileReader.h"
#include "./include/RISCVexecuter.h"
#include "./include/RISCVmem.h"
#include <string.h>

int main(int argc, char *argv[]){

    /* Verify if file names were passed: */
    if(argc < 3){
        printf("To execute this program, pass alongside the program call the 'text' and 'data' file names.\n");
        printf("For example: .\\simulador Teste_base-text.bin Teste_base-data.bin\n");
        printf("Also, to dump the memory and the register bank, write 'dump' right after the file names in function call\n");
        printf("and, right next to it, the initial and final memory address to dump, in decmial, and the format to print,\n");
        printf("'h' to hex, 'd' to decimal or 'b' to both.\n");
        printf("For example: .\\simulador Teste_base-text.bin Teste_base-data.bin dump 8192 8220 h\n");
        printf("The example above will execute the 'Teste_base' program, dumping its memory from address 0x2000 to 0x201c and the register bank in hex.\n");
        return 0;
    }

    /* Read Binary Files */
    ReadText(argv[1]);
    ReadData(argv[2]);

    /* Read information necessary for dump. */
    uint8_t dump = 0;
    uint32_t mem_ini = 0, mem_end = 0;
    char format = 'a';
    if(argc == 7){
        if(!strcmp("dump", argv[3])){
            mem_ini = atoi(argv[4]);
            mem_end = atoi(argv[5]);
            format = argv[6][0];
            dump = 1;
        }
    }

    /* Dump memory and registers before program execution, if necessary. */
    if(dump){
        printf("Dump Before Execution:\n\n");
        dump_mem(mem_ini, mem_end, format);
        dump_reg(format);
    }

    /* Run program. */
    run();

    /* Dump memory and registers after program execution, if necessary. */
    if(dump){
        printf("Dump After Execution:\n\n");
        dump_mem(mem_ini, mem_end, format);
        dump_reg(format);
    }

    return 0;
}
