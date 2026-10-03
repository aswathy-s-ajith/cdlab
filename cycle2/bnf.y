%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

%
[a-zA-Z][a-zA-Z0-9]* {
    yylval.str = strdup(yytext);
    return ID;
}
[0-9]+ {
    yylval.str = strdup(yytext);
    return ID;
}
[ \t] ;
\n return '\n';
"+" return '+';
"*" return '*';
"(" return '(';
")" return ')';
. return yytext[0];
%%

int yywrap(){
    return 1;
}

Yacc.y
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char data[20];
    struct node *left;
    struct node *right;
};

struct node *createNode(char *data, struct node *left, struct node *right){
    struct node *p = malloc(sizeof(struct node));
    strcpy(p->data, data);
    p->left = left;
    p->right = right;
    return p;
}

void preorder(struct node *root){
    if(root == NULL)
        return;
    printf("%s ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root){
    if(root == NULL)
        return;
    inorder(root->left);
    printf("%s ", root->data);
    inorder(root->right);
}

void printTree(struct node *root, int space){
    if(root == NULL)
        return;
    space += 5;
    printTree(root->right, space);
    printf("\n");
    for(int i=5; i<space; i++)
        printf(" ");
    printf("%s\n", root->data);
    printTree(root->left, space);
}

int yylex(void);
void yyerror(char *s);
%}

%union{
    char *str;
    struct node *nodeptr;
}

%token <str> ID
%type <nodeptr> E T F
%left '+'
%left '*'

%%

input:
    E '\n'{
        printf("\nAbstract Syntax Tree:\n");
        printTree($1, 0);
        printf("\nPreorder: ");
        preorder($1);
        printf("\nInorder: ");
        inorder($1);
        printf("\n");
    }
    ;

E:
    E '+' T{
        $$ = createNode("+", $1, $3);
    }
    |
    T{
        $$ = $1;
    }
    ;

T:
    T '*' F{
        $$ = createNode("*", $1, $3);
    }
    |
    F{
        $$ = $1;
    }
    ;

F:
    '(' E ')'{
        $$ = $2;
    }
    |
    ID{
        $$ = createNode($1, NULL, NULL);
    }
    ;
%%

void yyerror(char *s){
    printf("Invalid expression\n");
}

int main(){
    printf("Enter an expression: ");
    yyparse();

    return 0;
}

