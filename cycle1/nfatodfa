#include<stdio.h>
int n,a,t,final[20],start;
int table[20][20][20],dfa[100][21],count;
char alpha[20];

int findalpha(char c){
    for(int i=0;i<a;i++){
        if(alpha[i]==c)
            return i;
    }
    return -1;
}

void insert(int from,char c,int to){
    int x=findalpha(c);
    if(x==-1)
        return;
    table[from][x][to]=1;
}

int same(int x[],int y[]){
    for(int i=1;i<=n;i++){
        if(x[i]!=y[i])
            return 0;
    }
    return 1;
}

int findstate(int state[]){
    for(int i=0;i<count;i++){
        if(same(dfa[i],state))
            return i;
    }
    return -1;
}

void print(int state[]){
    int first=1;
    printf("{");
    for(int i=1;i<=n;i++){
        if(state[i]){
            if(!first)
                printf(",");
            printf("q%d",i);
            first=0;
        }
    }
    printf("}");
}

int main(){
    int i,j,k,from,to,nf,x;
    char c;
    printf("Enter no of alphabets: ");
    scanf("%d",&a);
    printf("Enter alphabets:\n");
    for(i=0;i<a;i++)
        scanf(" %c",&alpha[i]);
    printf("Enter no of states: ");
    scanf("%d",&n);
    printf("Enter start state: ");
    scanf("%d",&start);
    printf("Enter no of final states: ");
    scanf("%d",&nf);
    printf("Enter final states:\n");
    for(i=0;i<nf;i++)
        scanf("%d",&final[i]);
    printf("Enter no of transitions: ");
    scanf("%d",&t);
    printf("Enter transitions:\n");
    for(i=0;i<t;i++){
        scanf("%d %c %d",&from,&c,&to);
        insert(from,c,to);
    }
    dfa[0][start]=1;
    count=1;
    for(i=0;i<count;i++){
        for(x=0;x<a;x++){
            int next[21]={0};
            for(j=1;j<=n;j++){
                if(dfa[i][j]){
                    for(k=1;k<=n;k++){
                        if(table[j][x][k])
                            next[k]=1;
                    }
                }
            }
            print(dfa[i]);
            printf(" --%c--> ",alpha[x]);
            print(next);
            printf("\n");
            if(findstate(next)==-1 && count<100){
                for(j=1;j<=n;j++)
                    dfa[count][j]=next[j];
                count++;
            }
        }
    }
    printf("\nDFA States:\n");
    for(i=0;i<count;i++){
        printf("D%d = ",i);
        print(dfa[i]);
        printf("\n");
    }
    printf("\nStart state: D0 = ");
    print(dfa[0]);
    printf("\nFinal states: ");
    for(i=0;i<count;i++){
        for(j=1;j<=n;j++){
            if(dfa[i][j]){
                for(k=0;k<nf;k++){
                    if(j==final[k]){
                        printf("D%d ",i);
                        j=n;
                        break;
                    }
                }
            }
        }
    }
    printf("\n");
    return 0;
}
