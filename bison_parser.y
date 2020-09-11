%{
#include "global.h"
#include <vector>
#include "Entry.h"
#include <string.h>

std::list<int> idsTempList;
std::list<int> callArguments;
std::list<int> paramterList;

bool isGlobal = true;
int localMemAllocSize = 0;

%}

%debug
%define parse.error verbose
%locations

%token ID
%token NUM
%token SIGN
%token RELOP
%token MULOP
%token ASSIGNOP
%token OR

%token NOT

%token DO
%token IF
%token ELSE
%token THEN
%token WHILE
%token VAR
%token RANGEOP
%token ARRAY
%token OF

%token INTEGER
%token REAL

%token PROCEDURE
%token FUNCTION

%token BEGIN_TOKEN
%token END_TOKEN
%token PROGRAM_TOKEN

/* Not needed by bison, but elsewhere*/
/* signs */
%token PLUS
%token MINUS
/* mulop's */
%token MULTIPLICATION
%token DIVISION
%token MOD
%token AND

%token OR_OP
%token INT_TO_REAL
%token REAL_TO_INT

%token UNKOWN


%%
program:
PROGRAM_TOKEN ID '(' identifier_list ')'
 ';' {
	//printf("Bison:\t\t\t\tprogram\n");
	emitter.emitString("\tjump.i	#lab0");
	idsTempList.clear();
}

declarations {isGlobal = false;}
subprogram_declarations {
	emitter.writePointerAddresses();
	emitter.emitString("lab0:");
	isGlobal = true;
}
compound_statement
'.' {
	emitter.emitString("\texit");
}

identifier_list:
ID {
	idsTempList.push_back($1);
}
| identifier_list ',' ID {
	idsTempList.push_back($3);
}

declarations:
declarations VAR identifier_list ':' type ';' {
	if (isGlobal) {
		symbolTable.addGlobalVariablesWithType(idsTempList, $5);
	} else {
		symbolTable.addLocalDeclaredVariablesWithType(idsTempList, $5);
	}
	idsTempList.clear();
}
| %empty

type:
standard_type {}
| ARRAY '[' NUM RANGEOP NUM ']' OF standard_type {
	printf("Bison:\t\t\t\tArrays not supported!");
}

standard_type:
INTEGER {}
| REAL {}

subprogram_declarations:
subprogram_declarations subprogram_declaration ';' {
	emitter.emitSubprogramLeave();
	symbolTable.currentlyProcessedSubprogramIndex = -1;
}
| %empty

subprogram_declaration:
subprogram_head declarations compound_statement

subprogram_head:
FUNCTION ID arguments ':' standard_type ';' {
	Entry& functionEntry = symbolTable.getEntryByIndex($2);
	functionEntry.isFunction = true;
//	functionEntry.isPointer = true;
	symbolTable.assignVariableItsType(functionEntry, $5);
//	symbolTable.allocateFunReturnVarPointer(functionEntry);
	symbolTable.assignSubprogramItsArguments(functionEntry, paramterList);
	paramterList.clear();
	emitter.emitSubprogramStart(functionEntry);
	symbolTable.currentlyProcessedSubprogramIndex =
		functionEntry.indexInSymbolTable;
}
| PROCEDURE ID arguments ';' {
	Entry& procedureEntry = symbolTable.getEntryByIndex($2);
	procedureEntry.isProcedure = true;
	symbolTable.assignSubprogramItsArguments(procedureEntry, paramterList);
	paramterList.clear();
	emitter.emitSubprogramStart(procedureEntry);
	symbolTable.currentlyProcessedSubprogramIndex =
		procedureEntry.indexInSymbolTable;
}

arguments:
'(' parameter_list ')' {
	printf("Bison:\t\t\t\t\t\tGot parameter list, currently processed subprogram index = %d\n",
		symbolTable.currentlyProcessedSubprogramIndex);
//	printf("Bison:\t\t\t\t\t\t");
}
| %empty

parameter_list:
identifier_list ':' type {
	symbolTable.pushParametersToStack(idsTempList, $3);
	paramterList.splice(paramterList.end(), idsTempList);
	idsTempList.clear();
}
| parameter_list ';' identifier_list ':' type {
	printf("Bison:\t\t\t\t\t\tPushing parameters\n");
	symbolTable.pushParametersToStack(idsTempList, $5);
	paramterList.splice(paramterList.end(), idsTempList);
	idsTempList.clear();
}

compound_statement:
BEGIN_TOKEN
optional_statements
END_TOKEN

optional_statements:
statement_list
| %empty

statement_list:
statement
| statement_list ';' statement

statement:
variable ASSIGNOP expression {
	printf("Bison:\t\t\t\t\t\tFound assign operation\n");
	emitter.generateAssignOperation(symbolTable.getEntryByIndex($1),
		symbolTable.getEntryByIndex($3));
}
| procedure_statement {

}
| compound_statement
| IF expression {

} THEN statement {

} ELSE {

} statement {

}
| WHILE {

} expression DO  {

}statement {

}

variable:
ID {}
| ID '[' expression ']' {

}

procedure_statement:
ID {
	printf("Bison:\t\t\t\t\t\tFound subprogram call: %s\n", symbolTable.getEntryByIndex($1).name.c_str());
	Entry subprogramEntry = symbolTable.getEntryByIndex($1);
	printf("subprogramEntry.isProcedure %d\n", subprogramEntry.isProcedure);
	if (subprogramEntry.isProcedure) {
		$$ = emitter.callSubprogram(subprogramEntry);
	}
}
| ID '(' expression_list ')' {
	printf("Bison:\t\t\t\t\t\tFound subprogram call: %s\n", symbolTable.getEntryByIndex($1).name.c_str());
	Entry& subprogramEntry = symbolTable.getEntryByIndex($1);
	if(strcmp(subprogramEntry.name.c_str(), "write") == 0) {
		emitter.emitWrite(symbolTable.getEntryByIndex($3));
	} else if (subprogramEntry.isProcedure == true || subprogramEntry.isFunction == true) {
		$$ = emitter.callSubprogram(subprogramEntry, callArguments);
	}
	callArguments.clear();
}

expression_list:
expression {
	callArguments.push_back($1);
}
| expression_list ',' expression {
	callArguments.push_back($3);
}

expression:
simple_expression {$$ = $1;}
| simple_expression RELOP simple_expression {

}

simple_expression:
term {$$ = $1;}
| SIGN term
| simple_expression SIGN term {
	printf("Bison:\t\t\t\t\t\tsimple_expression: %d %d %d\n", $1, $2, $3);
	Entry leftEntry = symbolTable.getEntryByIndex($1);
	Entry rightEntry = symbolTable.getEntryByIndex($3);
	int resultIndex = emitter.generateSignOperation($2, leftEntry, rightEntry);
	printf("Bison:\t\t\t\t\t\tresultIndex %d\n", resultIndex);
	$$ = resultIndex;
}
| simple_expression OR term {

}

term:
factor {$$ = $1;}
| term MULOP factor {
	Entry leftEntry = symbolTable.getEntryByIndex($1);
        Entry rightEntry = symbolTable.getEntryByIndex($3);
        int resultIndex = emitter.generateSignOperation($2, leftEntry, rightEntry);
        //printf("Bison:\t\t\t\tresultIndex %d\n", resultIndex);
        $$ = resultIndex;
}

factor:
variable {
	Entry& subprogramEntry = symbolTable.getEntryByIndex($1);
	if (subprogramEntry.isProcedure || subprogramEntry.isFunction) {
		printf("Bison:\t\t\t\t\t\tFound subprogram as variable: %s\n", symbolTable.getEntryByIndex($1).name.c_str());
		$$ = emitter.callSubprogram(subprogramEntry);
	}
}
| ID '(' expression_list ')' {
	printf("Bison:\t\t\t\t\t\tFound subprogram call: %s\n", symbolTable.getEntryByIndex($1).name.c_str());
	Entry& subprogramEntry = symbolTable.getEntryByIndex($1);
	if(strcmp(subprogramEntry.name.c_str(), "write") == 0) {
		emitter.emitWrite(symbolTable.getEntryByIndex($3));
	} else if (subprogramEntry.isProcedure == true || subprogramEntry.isFunction == true) {
		$$ = emitter.callSubprogram(subprogramEntry, callArguments);
	}
	callArguments.clear();
}
| NUM {
//	printf("Bison:\t\t\t\tFound NUM: %d\n", $1);
}
| '(' expression ')' {}
| NOT factor {}
%%
int yyerror(const char *s)
{
 fprintf(stderr,"Error | Line: %d\n%s\n",yylineno,s);
}