/* RISC-V binary file reader header file: */

#ifndef RISCVFILEREADER_H_
#define RISCVFILEREADER_H_

#include "RISCVmem.h"

/* Functions: */

/* Function 'ReadText':
   Read the content of the 'text' file and store it in the initial positions of the memory
   Inputs: FileName - String with the name of the file with the 'text' data.
*/
void ReadText(char FileName[]);

/* Function 'ReadData':
   Read the content of the 'data' file and store it in the later positions of the memory
   Inputs: FileName - String with the name of the file with the 'data' data.
*/
void ReadData(char FileName[]);

#endif
