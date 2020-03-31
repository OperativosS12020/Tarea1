OPO=pruebaColor3.o
LIB=../lib
INCLUDE=../include
FLAG1=-Wall -c 
FLAG2=-Wall -o 
CC=gcc
XX=g++

output.o: $(OPO)
		$(XX) $(OPO) $(FLAG2) ../bin/output `pkg-config --cflags --libs opencv4`

pruebaColor3.o: pruebaColor3.c
		$(XX) $(FLAG1) pruebaColor3.c `pkg-config --cflags --libs opencv4`