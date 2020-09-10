COMPILER=g++
OUTPUT_PROGRAM_NAME=pascal-compiler

$(OUTPUT_PROGRAM_NAME) : main.o flex.o parser.o SymbolTable.o Emitter.o Decoder.o \
		util.o Entry.o

	$(COMPILER) -o $(OUTPUT_PROGRAM_NAME) main.o flex.o parser.o SymbolTable.o \
 		Emitter.o Decoder.o util.o Entry.o

main.o : main.cpp global.h parser.h
	$(COMPILER) -c main.cpp

Entry.o : Entry.cpp Entry.h global.h
	$(COMPILER) -c Entry.cpp Entry.h global.h

util.o : util.cpp util.h global.h
	$(COMPILER) -c util.cpp util.h global.h

Decoder.o : Decoder.cpp Decoder.h global.h
	$(COMPILER) -c Decoder.cpp Decoder.h global.h

Emitter.o : Emitter.cpp Emitter.h global.h
	$(COMPILER) -c Emitter.cpp Emitter.h global.h

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
	rm $(OUTPUT_PROGRAM_NAME) main.o flex.o parser.o SymbolTable.o Emitter.o flex.c parser.c parser.h \
	SymbolTable.h.gch global.h.gch Emitter.h.gch Entry.h.gch Decoder.o Decoder.h.gch