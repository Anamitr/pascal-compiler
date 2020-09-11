%{
#include <stdlib.h>
#include "global.h"
//#include "parser.h"

int tokenval;
int lineno = 0;
int lookupOrInstall(int typeOfToken, int typeCode);
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
                    printf("Flex\t\t\t\t\t\trelop: '%s'\n", yytext);
                    if (strcmp(yytext,"=") == 0) yylval = EQUAL;
                    if (strcmp(yytext,"<>") == 0) yylval = NOT_EQUAL;
                    if (strcmp(yytext,"<") == 0) yylval = LOWER;
                    if (strcmp(yytext,"<=") == 0) yylval = LOWER_OR_EQUAL;
                    if (strcmp(yytext,">=") == 0) yylval = HIGHER;
                    if (strcmp(yytext,">") == 0) yylval = HIGHER_OR_EQUAL;
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
                     return lookupOrInstall(ID, -1);
                }
{digit}+"."{digit}+ {
                    lookupOrInstall(NUM, REAL);
                    return NUM;
}

{digit}+ {
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