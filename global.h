#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

#include "parser.h"
#include "SymbolTable.h"
#include "Emitter.h"
#include "Entry.h"
#include "util.h"

using namespace std;

class SymbolTable;
class Emitter;
class Entry;

extern FILE *yyin, *yyout;
extern int yyparse (void);
extern int yylex (void);
extern int yyerror(const char*);
extern int yylineno;

extern SymbolTable symbolTable;
extern Emitter emitter;

extern bool isGlobal;