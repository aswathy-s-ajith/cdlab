Lex.l
%{
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*    { return VARIABLE; }
\n                      { return '\n'; }
.                       { return INVALID; }
%%

Yacc.y
%{
#include<stdio.h>
%}

%token VARIABLE INVALID
%%
input : VARIABLE '\n'   { printf("Valid variable\n"); }
        | INVALID '\n'    { printf("Invalid variable\n"); }
      ;
%%

int main() {
    printf("Enter a variable: ");
    yyparse();
    return 0;
}

int yyerror() {
    printf("Invalid variable\n");
    return 0;
}
