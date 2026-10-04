/*
#include <stdio.h>

int n;
int eps[10][10];     // eps[a][b] = 1  means  qa --epsilon--> qb
int visited[10];     // visited[i] = 1 means qi is in the closure

void dfs(int s) {
    visited[s] = 1;                          // s can always reach itself
    for (int i = 0; i < n; i++)
        if (eps[s][i] && !visited[i])        // epsilon move to a new state?
            dfs(i);                          // then follow it too
}

int main() {
    int t, a, b;
    printf("No. of states: ");                
    scanf("%d", &n);
    printf("No. of epsilon transitions: ");   
    scanf("%d", &t);
    printf("Enter each as: from to\n");
    while (t--) { 
        scanf("%d %d", &a, &b); 
        eps[a][b] = 1;
    }

    for (int s = 0; s < n; s++) {
        for (int i = 0; i < n; i++) visited[i] = 0;   // fresh start for each state
        dfs(s);
        printf("eps-closure(q%d) ={", s);
        for (int i = 0; i < n; i++)
            if (visited[i]) printf("q%d ", i);
        printf("}\n");
    }
    
    return 0;
}
*/

///////////////////////////////////////////////////////////////
#include <stdio.h>

int n, t;

// trans[from][to][k] stores the kth transition symbol
char trans[10][10][10];

int count[10][10];   // number of transitions from i to j
int visited[10];

void dfs(int s)
{
    visited[s] = 1;

    for (int i = 0; i < n; i++)
    {
        // Check all transitions from s to i
        for (int k = 0; k < count[s][i]; k++)
        {
            // Follow only epsilon transitions
            if (trans[s][i][k] == 'e' && !visited[i])
            {
                dfs(i);
            }
        }
    }
}

int main()
{
    int from, to;
    char symbol;

    printf("No. of states: ");
    scanf("%d", &n);

    printf("No. of transitions: ");
    scanf("%d", &t);

    printf("Enter each transition as: from symbol to\n");

    while (t--)
    {
        scanf("%d %c %d", &from, &symbol, &to);

        trans[from][to][count[from][to]] = symbol;
        count[from][to]++;
    }

    // Find epsilon closure of every state
    for (int s = 0; s < n; s++)
    {
        // Reset visited array
        for (int i = 0; i < n; i++)
            visited[i] = 0;

        // Find closure using DFS
        dfs(s);

        // Print closure
        printf("eps-closure(q%d) = {", s);

        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                printf("q%d ", i);
        }

        printf("}\n");
    }

    return 0;
}