#include <stdio.h>
#include <stdlib.h>
struct node {
    int st;
    struct node *link;
};
int n, a, t, trans[20][20], closure[20][20], visited[20], count;
char alpha[20];
struct node *table[20][20];

int findalpha(char c){
    for (int i = 0; i < a; i++)
        if (alpha[i] == c)
            return i;
    return -1;
}

void insert(int from, char c, int to){
    int x = findalpha(c);
    if (x == -1) return;
    struct node *p = malloc(sizeof(struct node));
    p->st = to;
    p->link = table[from][x];
    table[from][x] = p;
}

void closure_find(int state, int start){
    if (visited[state])
        return;
    visited[state] = 1;
    closure[start][count++] = state;
    if (alpha[a - 1] == 'e'){
        struct node *p = table[state][a - 1];
        while (p){
            closure_find(p->st, start);
            p = p->link;
        }
    }
}

int main(){
    int i, j, from, to;
    char c;
    printf("Enter number of alphabets: ");
    scanf("%d", &a);
    printf("Enter alphabets: ");
    for (i = 0; i < a; i++)
        scanf(" %c", &alpha[i]);
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of transitions: ");
    scanf("%d", &t);
    printf("Enter transitions (state alphabet state):\n");
    for (i = 0; i < t; i++){
        scanf("%d %c %d", &from, &c, &to);
        insert(from, c, to);
    }
    printf("\nEpsilon closures:\n");
    for (i = 1; i <= n; i++){
        count = 0;
        for (j = 0; j < n; j++){
            visited[j + 1] = 0;
            closure[i][j] = 0;
        }
        closure_find(i, i);
        printf("e-closure(q%d) = {", i);
        for (j = 0; j < count; j++){
            printf("q%d", closure[i][j]);
            if (j < count - 1)
                printf(",");
        }
        printf("}\n");
    }
    return 0;
}
