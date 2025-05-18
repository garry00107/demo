//8puzzle Astar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 3
#define MAX 10000

typedef struct {
    int board[SIZE][SIZE];
    int r, c;        // blank position
    int g, h;        // cost and heuristic
    char path[100];  // move path
} State;

State open[MAX];
int open_size = 0;
char closed[MAX][10];
int closed_size = 0;

int initial[SIZE][SIZE] = {{1,2,3},{4,0,6},{7,5,8}};
int goal[SIZE][SIZE]    = {{1,2,3},{4,5,6},{7,8,0}};

// Convert board to string
void board_str(int b[SIZE][SIZE], char *s) {
    int k = 0;
    for (int i=0;i<SIZE;i++)
        for (int j=0;j<SIZE;j++)
            s[k++] = b[i][j] + '0';
    s[k] = '\0';
}

// Check if board is in closed list
bool visited(int b[SIZE][SIZE]) {
    char s[10];
    board_str(b, s);
    for (int i = 0; i < closed_size; i++)
        if (strcmp(closed[i], s) == 0) return true;
    return false;
}

// Add board to closed list
void mark_visited(int b[SIZE][SIZE]) {
    board_str(b, closed[closed_size++]);
}

// Manhattan distance heuristic
int manhattan(int b[SIZE][SIZE]) {
    int d = 0;
    for (int i=0;i<SIZE;i++) {
        for (int j=0;j<SIZE;j++) {
            int val = b[i][j];
            if (val != 0) {
                int goal_r = (val - 1) / SIZE;
                int goal_c = (val - 1) % SIZE;
                d += abs(i - goal_r) + abs(j - goal_c);
            }
        }
    }
    return d;
}

// Get best (lowest cost f=g+h) state from open list
State get_best() {
    int best = 0;
    for (int i = 1; i < open_size; i++)
        if (open[i].g + open[i].h < open[best].g + open[best].h)
            best = i;
    State s = open[best];
    open[best] = open[--open_size];
    return s;
}

// Add state to open list
void push(State s) {
    open[open_size++] = s;
}

// Check goal
bool goal_check(int b[SIZE][SIZE]) {
    for (int i=0;i<SIZE;i++)
        for (int j=0;j<SIZE;j++)
            if (b[i][j] != goal[i][j]) return false;
    return true;
}

// Print board
void show(int b[SIZE][SIZE]) {
    for (int i=0;i<SIZE;i++) {
        for (int j=0;j<SIZE;j++)
            b[i][j] ? printf("%d ", b[i][j]) : printf("  ");
        printf("\n");
    }
    printf("\n");
}

// A* solver
char* solve() {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char mv[] = {'U', 'D', 'L', 'R'};

    State start;
    memcpy(start.board, initial, sizeof(initial));
    start.g = 0;
    start.h = manhattan(start.board);
    start.path[0] = '\0';

    // Find blank
    for (int i=0;i<SIZE;i++)
        for (int j=0;j<SIZE;j++)
            if (start.board[i][j] == 0)
                start.r = i, start.c = j;

    push(start);

    while (open_size > 0) {
        State cur = get_best();

        if (goal_check(cur.board))
            return strdup(cur.path);

        if (visited(cur.board)) continue;
        mark_visited(cur.board);

        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d], nc = cur.c + dc[d];
            if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) continue;

            State next = cur;
            next.board[cur.r][cur.c] = next.board[nr][nc];
            next.board[nr][nc] = 0;
            next.r = nr; next.c = nc;
            next.g = cur.g + 1;
            next.h = manhattan(next.board);
            next.path[cur.g] = mv[d];
            next.path[cur.g+1] = '\0';

            if (!visited(next.board)) push(next);
        }
    }
    return NULL;
}

int main() {
    printf("Initial state:\n");
    show(initial);

    char* ans = solve();

    if (ans) {
        printf("Solved in %lu moves: %s\n\n", strlen(ans), ans);

        // Replay solution
        int b[SIZE][SIZE], r, c;
        memcpy(b, initial, sizeof(initial));
        for (int i=0;i<SIZE;i++)
            for (int j=0;j<SIZE;j++)
                if (b[i][j] == 0)
                    r = i, c = j;

        show(b);
        for (int i=0; ans[i]; i++) {
            int nr = r, nc = c;
            switch (ans[i]) {
                case 'U': nr--; break;
                case 'D': nr++; break;
                case 'L': nc--; break;
                case 'R': nc++; break;
            }
            b[r][c] = b[nr][nc];
            b[nr][nc] = 0;
            r = nr; c = nc;
            printf("Move %d: %c\n", i+1, ans[i]);
            show(b);
        }
        free(ans);
    } else {
        printf("No solution found.\n");
    }
    return 0;
}
