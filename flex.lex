%{
#include <stdlib.h>
#include "global.h"
//#include "parser.h"

int tokenval;
int lineno = 0;
int lookupOrInstall(int typeOfToken);
%}

%option noyywrap
%option yylineno

digit [0-9]
letter [a-zA-Z_]
NEWLINE "\n"
WHITE [ \t]+
RELOPS "="|"<>"|"<"|"<="|">="|">"
MULOPS "*"|"/"|"div"|"mod"|"and"
SIGNS "+"|"-"
ASSIGN ":="
OR "or"

%%

{RELOPS}        {
                    //yylval = decodeRelOp(yytext);
                    return RELOP;
                }
{MULOPS}        {
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
{ASSIGN}        {
                    return ASSIGNOP;
                }
{NEWLINE}       {
                    lineno++;
                }
{WHITE}         {}
"or"            {yylval == OR_OP; return OR;}
"not"           {return NOT;}
"do"            {return DO;}
"if"            {
                    //yylval = symbolTable.insertHolder(IF_HOLDER);
                    return IF;
}
"else"          {return ELSE;}
"then"          {return THEN;}
"while"         {
                    //yylval = symbolTable.insertHolder(WHILE_HOLDER);
                    return WHILE;
}
"var"           {return VAR;}
".."            {return RANGEOP;}
"array"         {return ARRAY;}
"of"            {return OF;}

"integer"       {yylval = INTEGER; return INTEGER;}
"real"          {yylval = REAL; return REAL;}

"procedure"     {return PROCEDURE;}
"function"      {return FUNCTION;}

"begin"         {return BEGIN_TOKEN;}
"end"           {return END_TOKEN;}
"program"       {return PROGRAM_TOKEN;}

{letter}({letter}|{digit})* {
                     return lookupOrInstall(ID);
                }
{digit}+"."{digit}+ {
                    return lookupOrInstall(REAL);
                    return NUM;
}

{digit}+ {
                    return lookupOrInstall(INTEGER);
                    return NUM;
}
.               {return (int) yytext[0];}
%%

int lookupOrInstall(int typeOfToken) {
     //printf("Found id %s\n", yytext);
     int p;
     p = symbolTable.lookup(yytext);
     if (p == -1) {
        p = symbolTable.insert(yytext, ID);
     }
     yylval = p;
     return typeOfToken;
}