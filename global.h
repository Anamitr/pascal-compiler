//
// Created by konrad on 9/7/20.
//

#pragma once
#include <iostream>
#include <string>

#include "parser.h"
#include "SymbolTable.h"

class SymbolTable;

extern FILE *yyin, *yyout;
extern int yyparse (void);
extern int yylex (void);
extern int yyerror(const char*);
extern int yylineno;

extern SymbolTable symbolTable;