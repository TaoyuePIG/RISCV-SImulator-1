all: simulador

simulador: RISCVsimulator.o RISCVexecuter.o RISCVfileReader.o RISCVmem.o
		gcc -g -o simulador RISCVsimulator.o RISCVexecuter.o RISCVfileReader.o RISCVmem.o -I ./include/

RISCVsimulator.o:
		gcc -g -c RISCVsimulator.c -I ./include/

RISCVexecuter.o:
		gcc -g -c RISCVexecuter.c -I ./include/

RISCVfileReader.o: RISCVfileReader.c
		gcc -g -c RISCVfileReader.c -I ./include/

RISCVmem.o: RISCVmem.c
		gcc -g -c RISCVmem.c -I ./include/