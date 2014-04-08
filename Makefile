objects = src/arguments.o src/compile.o src/errorprocess.o src/fileio.o src/gloadfunction.o src/ins.o src/insformat.o src/instruction.o src/label.o src/macro.o src/main.o src/preprocess.o src/segmentmanager.o src/stddef.o src/strprocess.o src/task.o src/valueswitch.o
defines = src/function.h src/stddef.h
outfile = bin/nesa
cc = g++

nesa :	$(objects)
	$(cc) -o $(outfile) $(objects)

$(objects) : $(defines)

.PHONY : clean
clean:
	rm $(outfile) $(objects)

