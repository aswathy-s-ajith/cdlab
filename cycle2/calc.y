%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"
extern int yylval;
%}

%%
[0-9]+ {
        yylval=atoi(yytext);
        return NUMBER;
        }

[\t] ;
[\n] return 0;
. return yytext[0];
%%

int yywrap(){
    return 1;
}

Yacc.y
%{
#include<stdio.h>
int flag=0;
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression: E {
        printf("\nResult=%d\n",$$);
        return 0;
        };
E:E'+'E {$$=$1+$3;}
  |E'-'E {$$=$1-$3;}
 |E'*'E {$$=$1*$3;}
 |E'/'E {$$=$1/$3;}
 |E'%'E {$$=$1%$3;}
 |'('E')' {$$=$2;}
 |NUMBER {$$=$1;}
;
%%

void main(){
    printf("\nEnter Any Arithmetic Expression:\n");
    yyparse();
    if(flag==0)
        printf("\n\n");
}
void yyerror(){
    printf("\nInvalid\n\n");
    flag=1;
}
