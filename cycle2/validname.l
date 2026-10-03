%{
#include<stdio.h>
%}

%%
.*ACHU.*    { printf("String contains ACHU - Rejected\n"); }
.*          { printf("String does not contain ACHU - Accepted\n"); }
%%

int main(){
    printf("Enter a string: ");
    yylex();
    return 0;
}
int yywrap(){
    return 1;
}

