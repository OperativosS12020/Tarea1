PHONY: clean install

OPO=src/*.o
OPB=bin/*

install:
		cd src/ && make
		
clean:
		rm $(OPB) $(OPO)