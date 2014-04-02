#Makefile to build benchmarks

CC=gcc
EXE=$(FILE)
SRC=$(FILE).cil.c

all:clean $(EXE)
clean:
	rm -rf $(EXE) *.tpl *.lst *.cautlog *.append *.*~ *.i *~ cover_status.txt Testcase Caut_Log.txt $(EXE)-test
	

$(EXE):$(SRC)
	$(CC) -g -o $@ -I .. -L ../lpsolve $? ../lib/caut-bc.a -llpsolve55 -ldl -lpthread 
