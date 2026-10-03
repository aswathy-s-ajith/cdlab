
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(){
    FILE *input;
    int line = 1;
    int token = 0;
    int i, flag;
    char ch, str[50];
    char keyword[30][30] = {
        "int", "main", "if", "else", "do", "while"
    };
    input = fopen("input.txt", "r");
    if (input == NULL){
        printf("Cannot open input.txt\n");
        return 1;
    }
    printf("Line no.\tToken no.\t\tToken\t\tLexeme\n\n");
    while ((ch = fgetc(input)) != EOF){
        /* Ignore spaces and tabs */
        if (ch == ' ' || ch == '\t'){
            continue;
        }
        /* New line */
        if (ch == '\n'){
            line++;
            continue;
        }
        /* Operators */
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/'){
            printf("%7d\t\t%7d\t\tOperator\t%7c\n", line, token, ch);
            token++;
        }
        /* =, ==, <, <=, >, >=, != */
        else if (ch == '=' || ch == '<' || ch == '>' || ch == '!'){
            char next = fgetc(input);
            if (next == '='){
                printf("%7d\t\t%7d\t\tOperator\t%7c%c\n", line, token, ch,next);
            }
            else{
                printf("%7d\t\t%7d\t\tOperator\t%7c\n", line, token, ch);
                /* Put the character back because it belongs
                   to the next token */
                if (next != EOF)
                    ungetc(next, input);
            }
            token++;
        }
        /* Special symbols */
        else if (ch == ';' || ch == '{' || ch == '}' || 
                 ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
                 ch == ',' || ch == '?' || ch == '@' || ch == '%'){
            printf("%7d\t\t%7d\t\tSpecial symbol\t%7c\n", line, token, ch);
            token++;
        }
        /* Number */
        else if (isdigit(ch)){
            i = 0;
            while (isdigit(ch)){
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            printf("%7d\t\t%7d\t\tNumber\t\t%7s\n", line, token, str);
            token++;
            if (ch != EOF)
                ungetc(ch, input);
        }
        /* Identifier or keyword */
        else if (isalpha(ch) || ch == '_'){
            i = 0;
            while (isalnum(ch) || ch == '_'){
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            flag = 0;
            /* Check keyword */
            for (int j = 0; j < 6; j++){
                if (strcmp(str, keyword[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1){
                printf("%7d\t\t%7d\t\tKeyword\t\t%7s\n", line, token, str);
            }
            else{
                printf("%7d\t\t%7d\t\tIdentifier\t%7s\n", line, token, str);
            }
            token++;
            /* Put back the character that stopped the identifier */
            if (ch != EOF)
                ungetc(ch, input);
        }
        /* Anything else */
        else{
            printf("%7d\t\t%7d\t\tUnknown\t\t%7c\n", line, token, ch);
            token++;
        }
    }
    fclose(input);
    printf("Lexical analysis completed.\n");
    printf("Check output.txt for the result.\n");
    return 0;
}
