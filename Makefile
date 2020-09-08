COMPILER=g++
OUTPUT_PROGRAM_NAME=pascal-compiler

$(OUTPUT_PROGRAM_NAME) : main.o flex.o parser.o SymbolTable.o \
	# emitter.o error.o init.o \
#	 symbol.o
	$(COMPILER) -o $(OUTPUT_PROGRAM_NAME) main.o flex.o parser.o SymbolTable.o \
#     emitter.o error.o init.o \
#	 symbol.o

main.o : main.cpp global.h parser.h
	$(COMPILER) -c main.cpp

#emitter.o : emitter.c global.h parser.h
#	$(COMPILER) -c emitter.c
#
#error.o : error.c global.h parser.h
#	$(COMPILER) -c error.c
#
#init.o : init.c global.h parser.h
#	$(COMPILER) -c init.c

# parser.h generated by bison includes enums like DONE, DIV etc.
# previously defined in global.h
parser.c parser.h : bison_parser.y
	bison --defines=parser.h -o parser.c bison_parser.y

parser.o : parser.c global.h
	$(COMPILER) -c -w parser.c

flex.c : flex.lex
	lex -o flex.c flex.lex

flex.o : flex.c global.h parser.h
	$(COMPILER) -c flex.c

SymbolTable.o : SymbolTable.cpp SymbolTable.h global.h
	$(COMPILER) -c SymbolTable.cpp SymbolTable.h global.h

clean :
#	rm $(OUTPUT_PROGRAM_NAME) main.o emitter.o error.o init.o \
#	flex.o parser.o symbol.o flex.c parser.c parser.h
	rm $(OUTPUT_PROGRAM_NAME) main.o flex.o parser.o SymbolTable.o flex.c parser.c parser.h