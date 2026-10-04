// Q4: NFA -> DFA (subset construction). Works with or without epsilon moves.
// Each DFA state = a SET of NFA states. Start with closure({q0}), keep adding new sets.
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

unsigned dstate[64];       // dstate[i] = the NFA-state set that DFA state i stands for
int dnext[64][10];         // dnext[i][a] = DFA state reached from i on symbol a
int cnt = 0;

int find(unsigned set) {                   // index of this set in the list, adding it if new
    for (int i = 0; i < cnt; i++) if (dstate[i] == set) return i;
    dstate[cnt] = set;
    return cnt++;
}

int main() {
    readNFA();
    find(closureSet(1u << 0));             // DFA start state
    for (int i = 0; i < cnt; i++)          // cnt grows while we loop - that's the algorithm
        for (int a = 0; a < m; a++)
            dnext[i][a] = find(closureSet(move(dstate[i], a)));

    printf("\nDFA (A is start, * = final):\n");
    for (int i = 0; i < cnt; i++) {
        printf("%c%s = ", 'A' + i, (dstate[i] & finals) ? "*" : " ");
        printSet(dstate[i]);
        for (int a = 0; a < m; a++) printf("   on %c -> %c", sym[a], 'A' + dnext[i][a]);
        printf("\n");
    }
    return 0;
}
