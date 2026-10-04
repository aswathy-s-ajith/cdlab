// Q5: DFA minimization (table-filling method).
// Idea: two states are DISTINGUISHABLE if one is final and other isn't,
// or if some symbol sends them to an already-distinguishable pair.
// Pairs that never get marked are equivalent -> merge them.
#include <stdio.h>

int n, m, d[20][10], isFinal[20], dist[20][20], rep[20];
char sym[10];

int distinct(int x, int y) {               // are x and y already marked distinguishable?
    if (x == y) return 0;
    return x < y ? dist[x][y] : dist[y][x];
}

int main() {
    int f, x;
    printf("No. of states: ");           scanf("%d", &n);
    printf("No. of symbols: ");          scanf("%d", &m);
    printf("Symbols: ");                 for (int a = 0; a < m; a++) scanf(" %c", &sym[a]);
    printf("Transition table (row = state, column = symbol):\n");
    for (int i = 0; i < n; i++) for (int a = 0; a < m; a++) scanf("%d", &d[i][a]);
    printf("No. of final states: ");     scanf("%d", &f);
    printf("Final states: ");            while (f--) { scanf("%d", &x); isFinal[x] = 1; }

    // step 1: final vs non-final are distinguishable
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++)
        dist[i][j] = (isFinal[i] != isFinal[j]);

    // step 2: repeat until no new pair gets marked
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
            if (dist[i][j]) continue;
            for (int a = 0; a < m; a++)
                if (distinct(d[i][a], d[j][a])) { dist[i][j] = changed = 1; break; }
        }
    }

    // step 3: each state's representative = smallest state equivalent to it
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            if (!distinct(j, i)) { rep[i] = j; break; }

    printf("\nMinimized DFA (start = group of q%d):\n", rep[0]);
    for (int i = 0; i < n; i++) {
        if (rep[i] != i) continue;         // print one line per group
        printf("{");
        for (int j = 0; j < n; j++) if (rep[j] == i) printf(" q%d", j);
        printf(" }%s", isFinal[i] ? " (final)" : "");
        for (int a = 0; a < m; a++) printf("   on %c -> q%d", sym[a], rep[d[i][a]]);
        printf("\n");
    }
    return 0;
}
