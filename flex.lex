%{
#include <stdlib.h>
#include "global.h"

int tokenval;
int lineno = 0;
int lookupOrInstall(int typeOfToken, int typeCode);
%}

%option noyywrap
%option yylineno

digit           [0-9]
letter          [a-zA-Z_]
DELIMITER       [ \t]
WHITE_SPACE     {DELIMITER}+
NEWLINE         "\n"
RELOPS          "="|"<>"|"<"|"<="|">="|">"
MULOPS          "*"|"/"|"div"|"mod"|"and"
SIGNS           "+"|"-"
ASSIGN          ":="
IDENTIFIER      {letter}({letter}|{digit})*
INT             {digit}+
DECIMAL         {digit}+"."{digit}+

%%


{WHITE_SPACE}   {}
{NEWLINE}       { lineno++; }
{RELOPS}        {
                    printf("Flex\t\t\t\t\t\trelop: '%s'\n", yytext);
                    if (strcmp(yytext,"=") == 0) yylval = EQUAL;
                    if (strcmp(yytext,"<>") == 0) yylval = NOT_EQUAL;
                    if (strcmp(yytext,"<") == 0) yylval = LOWER;
                    if (strcmp(yytext,"<=") == 0) yylval = LOWER_OR_EQUAL;
                    if (strcmp(yytext,">=") == 0) yylval = HIGHER_OR_EQUAL;
                    if (strcmp(yytext,">") == 0) yylval = HIGHER;
                    return RELOP;
                }
{MULOPS}        {
                    printf("Flex\t\t\t\t\t\tmulop: '%s'\n", yytext);
                    if (strcmp(yytext,"*") == 0) yylval = MULTIPLICATION;
                    if (strcmp(yytext,"/") == 0) yylval = DIVISION;
                    if (strcmp(yytext,"div") == 0) yylval = DIVISION;
                    if (strcmp(yytext,"mod") == 0) yylval = MOD;
                    if (strcmp(yytext,"and") == 0) yylval = AND;

                    //yylval = decodeMulOp(yytext);
                    return MULOP;
                }
{SIGNS}         {
                    printf("sign: '%s'\n", yytext);
                    if (strcmp(yytext,"+") == 0) yylval = PLUS;
                    if (strcmp(yytext,"-") == 0) yylval = MINUS;
                    printf("Sign yyval: %d\n", yylval);
                    printf("PLUS: %d, MINUS: %d\n", PLUS, MINUS);
                    //yylval = decodeSignOp(yytext);
                    return SIGN;
                }
{ASSIGN}        { return ASSIGNOP; }
"program"       { return PROGRAM_TOKEN; }
"begin"         { return BEGIN_TOKEN; }
"end"           { return END_TOKEN; }
"or"            { return OR; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"not"           { return NOT; }
"while"         { return WHILE; }
"do"            { return DO; }
"var"           { return VAR; }
"integer"       { yylval = INTEGER; return INTEGER; }
"real"          { yylval = REAL; return REAL; }
"procedure"     { return PROCEDURE; }
"function"      { return FUNCTION; }
{IDENTIFIER}    {
                     return lookupOrInstall(ID, -1);
                }
{DECIMAL}       {
                    return lookupOrInstall(NUM, REAL);
                }
{INT}           {
                    lookupOrInstall(NUM, INTEGER);
                    printf("flex: found integer: %s\n", yytext);
                    return NUM;
                }
.               {return (int) yytext[0];}
%%

int lookupOrInstall(int typeOfToken, int typeCode) {
     //printf("Found id %s\n", yytext);
     int p;
     p = symbolTable.lookup(yytext);
     if (p == -1) {
        p = symbolTable.insert(yytext, typeOfToken, typeCode);
     }
     yylval = p;
     return typeOfToken;
}