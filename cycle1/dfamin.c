#include<stdio.h>
int n,a,final[20],reach[20];
int table[20][20],group[20],newgroup[20];
int nf;

void dfs(int state){
    reach[state]=1;
    for(int i=0;i<a;i++){
        if(table[state][i]!=-1 && !reach[table[state][i]])
            dfs(table[state][i]);
    }
}

void insert(int from,int symbol,int to){
    table[from][symbol]=to;
}

int main(){
    int i,j,k,start,to,changed,count;
    char c;
    printf("Enter no of states: ");
    scanf("%d",&n);
    printf("Enter no of alphabets: ");
    scanf("%d",&a);
    for(i=0;i<n;i++)
        for(j=0;j<a;j++)
            table[i][j]=-1;
    printf("Enter transitions:\n");
    for(i=0;i<n;i++){
        printf("State %d:\n",i);
        for(j=0;j<a;j++){
            scanf(" %c %d",&c,&to);
            insert(i,j,to);
        }
    }
    printf("Enter start state: ");
    scanf("%d",&start);
    printf("Enter no of final states: ");
    scanf("%d",&nf);
    printf("Enter final states:\n");
    for(i=0;i<nf;i++)
        scanf("%d",&final[i]);
    dfs(start);
    for(i=0;i<n;i++)
        group[i]=reach[i] ? 0 : -1;
    for(i=0;i<nf;i++)
        group[final[i]]=1;
    do{
        changed=0;
        count=0;
        for(i=0;i<n;i++)
            newgroup[i]=-1;
        for(i=0;i<n;i++){
            if(group[i]==-1 || newgroup[i]!=-1)
                continue;
            newgroup[i]=count;
            for(j=i+1;j<n;j++){
                if(group[j]==-1 || newgroup[j]!=-1 ||
                   group[i]!=group[j])
                    continue;
                int same=1;
                for(k=0;k<a;k++){
                    int x=table[i][k];
                    int y=table[j][k];
                    if(x!=-1 && y!=-1 && group[x]==group[y])
                        continue;
                    if(x==-1 && y==-1)
                        continue;
                    same=0;
                    break;
                }
                if(same)
                    newgroup[j]=count;
            }
            count++;
        }
        for(i=0;i<n;i++){
            if(group[i]!=newgroup[i])
                changed=1;
            group[i]=newgroup[i];
        }
    }while(changed);
    printf("\nMinimized DFA\n");
    printf("----------------\n");
    printf("Number of states: %d\n",count);
    printf("\nStates:\n");
    for(i=0;i<count;i++){
        printf("D%d = {",i);
        for(j=0;j<n;j++)
            if(group[j]==i)
                printf("q%d ",j);
        printf("}\n");
    }
    printf("\nTransitions:\n");
    for(i=0;i<count;i++){
        int state=-1;
        for(j=0;j<n;j++){
            if(group[j]==i){
                state=j;
                break;
            }
        }
        for(k=0;k<a;k++){
            if(table[state][k]!=-1)
                printf("D%d --%d--> D%d\n",
                       i,k,group[table[state][k]]);
        }
    }
    printf("\nStart state: D%d\n",group[start]);
    printf("Final states: ");
    for(i=0;i<count;i++){
        for(j=0;j<nf;j++){
            if(group[final[j]]==i){
                printf("D%d ",i);
                break;
            }
        }
    }
    printf("\n");
    return 0;
}
