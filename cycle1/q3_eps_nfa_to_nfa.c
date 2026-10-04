// Q3: NFA with epsilon  ->  NFA without epsilon.
// Rule: new_delta(s,a) = closure( move( closure(s), a ) )
// s is final in the new NFA if closure(s) contains an old final state.
#include <stdio.h>

int n, m;                  // number of states, number of input symbols
char sym[10];              // input symbols (a, b, ...)
unsigned eps[32];          // eps[s]  = states reachable from s by ONE epsilon move
unsigned d[32][10];        // d[s][a] = states reachable from s on symbol a
unsigned finals;           // bitmask of final states (start state is always q0)

int idx(char c) { for (int i = 0; i < m; i++) if (sym[i] == c) return i; return -1; }

// closure of a SET of states: keep adding eps-moves until nothing changes
unsigned closureSet(unsigned set) {
    unsigned prev;
    do {
        prev = set;
        for (int i = 0; i < n; i++)
            if (set & (1u << i)) set |= eps[i];
    } while (set != prev);
    return set;
}

// all states reachable from a SET on symbol a (one step)
unsigned move(unsigned set, int a) {
    unsigned r = 0;
    for (int i = 0; i < n; i++)
        if (set & (1u << i)) r |= d[i][a];
    return r;
}

void printSet(unsigned s) {
    printf("{");
    int first = 1;
    for (int i = 0; i < n; i++)
        if (s & (1u << i)) { printf(first ? "q%d" : ",q%d", i); first = 0; }
    printf("}");
}

void readNFA() {
    int t, a, b, f; char c;
    printf("No. of states: ");              scanf("%d", &n);
    printf("No. of input symbols: ");       scanf("%d", &m);
    printf("Symbols (space separated): ");  for (int i = 0; i < m; i++) scanf(" %c", &sym[i]);
    printf("No. of transitions: ");         scanf("%d", &t);
    printf("Enter each as: from symbol to   (use e for epsilon)\n");
    while (t--) {
        scanf("%d %c %d", &a, &c, &b);
        if (c == 'e') eps[a] |= 1u << b;
        else d[a][idx(c)] |= 1u << b;
    }
    printf("No. of final states: ");        scanf("%d", &f);
    printf("Final states: ");               while (f--) { scanf("%d", &a); finals |= 1u << a; }
}

int main() {
    readNFA();
    printf("\nNFA without epsilon:\n");
    for (int s = 0; s < n; s++) {
        unsigned cl = closureSet(1u << s);
        printf("q%d%s", s, (cl & finals) ? " (final)" : "");
        for (int a = 0; a < m; a++) {
            printf("   on %c -> ", sym[a]);
            printSet(closureSet(move(cl, a)));
        }
        printf("\n");
    }
    return 0;
}
