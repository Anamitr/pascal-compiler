%{
#include "global.h"
#include <vector>

std::list<int> idsTempList;
//std::vector<std::tuple<int, std::vector<int>, array_declaration_holder>> paramListHolder;
//std::vector<int> expressionListHolder;
//array_declaration_holder arrayDeclarationHolder;

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
%token PLUS
%token MINUS
%token OR_OP
%token INT_TO_REAL

%token UNKOWN


%%
program:
PROGRAM_TOKEN ID '(' identifier_list ')'
 ';' {
	//printf("program\n");
	emitter.emitString("\tjump.i	#lab0");
	idsTempList.clear();
}

declarations
subprogram_declarations {

	emitter.emitString("#lab0:");
}
compound_statement
'.' {

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
	symbolTable.addGlobalVariablesWithType(idsTempList, $5);
	idsTempList.clear();
}
| %empty

type:
standard_type {}
| ARRAY '[' NUM RANGEOP NUM ']' OF standard_type {
	printf("Arrays not supported!");
}

standard_type:
INTEGER {}
| REAL {}

subprogram_declarations:
subprogram_declarations subprogram_declaration ';' {
}
| %empty

subprogram_declaration:
subprogram_head declarations compound_statement

subprogram_head:
FUNCTION ID arguments ':' standard_type ';' {

}
| PROCEDURE ID arguments ';' {

}

arguments:
'(' parameter_list ')' {

}
| %empty

parameter_list:
identifier_list ':' type {

}
| parameter_list ';' identifier_list ':' type {

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

}
| ID '(' expression_list ')' {
//	if(symbolTable.getEntryByIndex(ID) == "write") {
//		printf("write");
//	}

}

expression_list:
expression {

}
| expression_list ',' expression {

}

expression:
simple_expression {}
| simple_expression RELOP simple_expression {

}

simple_expression:
term {}
| SIGN term
| simple_expression SIGN term {
	printf("simple_expression: %d %d %d\n", $1, $2, $3);
	if ($2 == PLUS) printf("plusss\n");
	int resultIndex = emitter.generateSignOperation($2, $1, $3);
	printf("resultIndex %d\n", resultIndex);
	$$ = resultIndex;
}
| simple_expression OR term {

}

term:
factor {}
| term MULOP factor {

}

factor:
variable {

}
| ID '(' expression_list ')' {

}
| NUM {}
| '(' expression ')' {}
| NOT factor {}
%%
int yyerror(const char *s)
{
 fprintf(stderr,"Error | Line: %d\n%s\n",yylineno,s);
}