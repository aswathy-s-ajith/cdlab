#include <stdio.h>
#include <stdlib.h>
int n,t;
int eps[10][10];
int visited[10];

void dfs(int s){
    visited[s]=1;
    for(int i=0;i<n;i++){
        if(!visited[i] && eps[s][i]){
            dfs(i);
        }
    }
}
int main(){


    
    printf("enter number of states:");
    scanf("%d",&n);
    printf("enter number of transitions:");
    scanf("%d",&t);
    printf("enter from to:");
    int a,b;
    for(int i=0;i<t;i++){
        scanf("%d %d",&a,&b);
        eps[a][b]=1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            visited[j]=0;
        }

        dfs(i);
        printf("e-closure of q%d={",i);
        for(int j=0;j<n;j++){
            if(visited[j]){
                printf("q%d",j);
            }
        }
        printf("}");
    }
}