//ast.l

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the structure before y.tab.h */
struct node
{
    char data[20];
    struct node *left;
    struct node *right;
};

#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*    {
                            yylval.str = strdup(yytext);
                            return ID;
                         }

[0-9]+                  {
                            yylval.str = strdup(yytext);
                            return ID;
                         }

[ \t]                   ;

\n                      return '\n';

"+"                     return '+';
"*"                     return '*';
"("                     return '(';
")"                     return ')';

.                       return yytext[0];
%%

int yywrap()
{
    return 1;
}

//ast.y

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char data[20];
    struct node *left;
    struct node *right;
};

struct node *createNode(char *data, struct node *left, struct node *right)
{
    struct node *newNode;

    newNode = (struct node *)malloc(sizeof(struct node));

    strcpy(newNode->data, data);
    newNode->left = left;
    newNode->right = right;

    return newNode;
}

void preorder(struct node *root)
{
    if (root == NULL)
        return;

    printf("%s ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%s ", root->data);
    inorder(root->right);
}

void printTree(struct node *root, int space)
{
    int i;

    if (root == NULL)
        return;

    space = space + 5;

    printTree(root->right, space);

    printf("\n");

    for (i = 5; i < space; i++)
        printf(" ");

    printf("%s\n", root->data);

    printTree(root->left, space);
}

int yylex(void);
void yyerror(char *s);
%}

%union
{
    char *str;
    struct node *nodeptr;
}

%token <str> ID

%type <nodeptr> E T F

%left '+'
%left '*'

%%

input:
        E '\n'
        {
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
        E '+' T
        {
            $$ = createNode("+", $1, $3);
        }
        |
        T
        {
            $$ = $1;
        }
        ;

T:
        T '*' F
        {
            $$ = createNode("*", $1, $3);
        }
        |
        F
        {
            $$ = $1;
        }
        ;

F:
        '(' E ')'
        {
            $$ = $2;
        }
        |
        ID
        {
            $$ = createNode($1, NULL, NULL);
        }
        ;

%%

void yyerror(char *s)
{
    printf("Invalid expression\n");
}

int main()
{
    printf("Enter an expression: ");
    yyparse();

    return 0;
}


//bnf.l

%{
#include <stdio.h>
#include <string.h>

int first = 1;
%}

%%

"<"[a-zA-Z_][a-zA-Z0-9_]*">" {
    char temp[100];

    strcpy(temp, yytext);

    /* Remove < and > */
    temp[strlen(temp) - 1] = '\0';

    if (first)
    {
        printf("\n%s :", temp + 1);
        first = 0;
    }
    else
    {
        printf("%s ", temp + 1);
    }
}

"::=" {
    printf(" ");
}

"|" {
    printf("\n     | ");
}

[ \t]+ {
    printf(" ");
}

"\n" {
    if (!first)
    {
        printf("\n     ;\n");
        first = 1;
    }
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%s ", yytext);
}

[()+*-/] {
    printf("%s ", yytext);
}

. {
    printf("%s ", yytext);
}

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter BNF rules (Ctrl+D to finish):\n\n");

    yylex();

    return 0;
}


