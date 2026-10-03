%{
#include "y.tab.h"
%}

%%

"for"                   return FOR;
[a-zA-Z_][a-zA-Z0-9_]*  return ID;
[0-9]+                  return NUM;

"++"                    return INC;
"--"                    return DEC;

"=="                    return EQ;
"<="                    return LE;
">="                    return GE;
"!="                    return NE;

"="                     return '=';
"<"                     return '<';
">"                     return '>';

";"                     return ';';
"("                     return '(';
")"                     return ')';

"+"                     return '+';
"-"                     return '-';

[ \t\n]                 ;

.                       return yytext[0];

%%

int yywrap()
{
    return 1;
}

Yacc.y
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token FOR ID NUM INC DEC
%token EQ LE GE NE

%left '+' '-'

%%

statement:
    FOR '(' initialization ';' condition ';' increment ')'
    {
        printf("Valid FOR statement\n");
    }
    ;

initialization:
    ID '=' expression
    ;

condition:
    expression relational_operator expression
    ;

increment:
    ID INC
    | ID DEC
    | INC ID
    | DEC ID
    | ID '=' expression
    ;

expression:
    ID
    | NUM
    | expression '+' expression
    | expression '-' expression
    ;

relational_operator:
    '<'
    | '>'
    | EQ
    | LE
    | GE
    | NE
    ;

%%

void yyerror(const char *s){
    printf("Invalid FOR statement\n");
}

int main(){
    printf("Enter a C FOR statement:\n");
    yyparse();

    return 0;
}

