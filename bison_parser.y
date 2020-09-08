%{
#include "global.h"
#include <vector>

//std::vector<int> idListHolder;
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

%token OR_OP



%%
program:
PROGRAM_TOKEN ID '(' identifier_list ')'
 ';' {
	printf("program");
}

declarations
subprogram_declarations {

}
compound_statement
'.' {

}

identifier_list:
ID {}
| identifier_list ',' ID {}

declarations:
declarations VAR identifier_list ':' type ';' {

}
| %empty

type:
standard_type {}
| ARRAY '[' NUM RANGEOP NUM ']' OF standard_type {

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