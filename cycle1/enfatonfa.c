#include<stdio.h>
#include<stdlib.h>
struct Node{
    int st;
    struct Node *link;
};
int n, a, t, closure[20][20], final[20], visited[20], count;
char alpha[20];
struct Node *table[20][20];

int findalpha(char c){
    for(int i=0;i<a;i++){
        if(alpha[i]==c){
            return i;
        }
    }
    return -1;
}

void insert(int from, char c, int to){
    int x=findalpha(c);
    if(x==-1) return;
    struct Node *p=malloc(sizeof(struct Node));
    p->st=to;
    p->link=table[from][x];
    table[from][x]=p;
}

void findclosure(int state, int start){
    if(visited[state]) return;
    visited[state]=1;
    closure[start][count++]=state;
    if(alpha[a-1]=='e'){
        struct Node *p=table[state][a-1];
        while(p){
            findclosure(p->st, start);
            p=p->link;
        }
    }
}

void print(int state){
    printf("{");
    for (int i = 0; closure[state][i]; i++){
        printf("q%d", closure[state][i]);
        if (closure[state][i + 1])
            printf(",");
    }
    printf("}");
}

int main(){
    int i, j, from, to, start, nf, k, set[20];
    char c;
    printf("Enter no of alphabets: ");
    scanf("%d", &a);
    printf("Enter alphabets:\n ");
    for(i=0;i<a;i++){
        scanf(" %c", &alpha[i]);
    }
    printf("Enter no of states:");
    scanf("%d", &n);
    printf("Enter start state: ");
    scanf("%d", &start);
    printf("Enter no of final states: ");
    scanf("%d", &nf);
    printf("Enter final states:\n");
    for(i=0;i<nf;i++){
        scanf("%d", &final[i]);
    }
    printf("Enter no of transitions: ");
    scanf("%d", &t);
    printf("Enter transitions:\n ");
    for(i=0;i<t;i++){
        scanf("%d %c %d", &from, &c, &to);
        insert(from, c, to);
    }
    for(i=1;i<=n;i++){
        count=0;
        for(j=0;j<n;j++){
            visited[j+1]=0;
            closure[i][j]=0;
        }
        findclosure(i, i);
    }
    printf("NFA Without Epsilon Transitions\n");
    printf("Start state:");
    print(start);
    printf("\nStates: ");
    for (i = 1; i <= n; i++)
        print(i);
    printf("\nTransitions:\n");
    for(i=1;i<=n;i++){
        for(j=0;j<a-1;j++){
            for(k=1;k<=n;k++){
                set[k]=0;
            }
            for(k=0;closure[i][k]!=0;k++){
                struct Node *p=table[closure[i][k]][j];
                while(p){
                    int x;
                    for(x=0;closure[p->st][x]!=0;x++){
                        set[closure[p->st][x]]=1;
                    }
                    p=p->link;
                }
            }
            print(i);
            printf(" --%c--> {", alpha[j]);
            for (k = 1; k <= n; k++)
                if (set[k])
                    printf("q%d,", k);
            printf("}\n");
        }
    }
    printf("Final states:\n");
    for (i = 1; i <= n; i++){
            for (j = 0; j < n; j++){
                for (k = 0; k < nf; k++){
                    if (closure[i][j] == final[k]){
                        printf("q%d ", i);
                        j = n;
                        break;
                    }
                }
            }
        }
    printf("\n");
    return 0;
}


