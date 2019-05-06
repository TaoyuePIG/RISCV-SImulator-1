/* RISC-V binary file reader code file: */

#include "./include/RISCVfileReader.h"

void ReadText(char FileName[]){
    /* Open text file: */
    FILE *fp = fopen(FileName, "rb");
    /* Verify if file was correctly open: */
    if(fp == NULL){
        printf("ERROR: Provided 'text' file does not exist.\n");
        exit(0);
    }

    int32_t instr, i = 0;

    /* Store content of binary file on memory until end of file or maximum memory for text is reached. */
    while((!feof(fp)) && (i < 1024)){
        fread(&instr, sizeof(int32_t), 1, fp);
        mem[i] = instr;
        i++;
    }

    fclose(fp);
}

void ReadData(char FileName[]){
    /* Open data file: */
    FILE *fp = fopen(FileName, "rb");
    /* Verify if file was correctly open: */
    if(fp == NULL){
        printf("ERROR: Provided 'data' file does not exist.\n");
        exit(0);
    }

    int32_t data, i = 2048;

    /* Store content of binary file on memory until end of file or maximum memory is reached. */
    while((!feof(fp)) && (i < 4096)){
        fread(&data, sizeof(int32_t), 1, fp);
        mem[i] = data;
        i++;
    }

    fclose(fp);
}
