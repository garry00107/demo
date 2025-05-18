#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 3
#define MAX_STATES 100

int goal[N][N] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Function to print board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            board[i][j] ? printf("%d ", board[i][j]) : printf("  ");
        printf("\n");
    }
    printf("\n");
}

// Compute Manhattan distance
int manhattan(int board[N][N]) {
    int d = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int val = board[i][j];
            if (val != 0) {
                int goal_r = (val - 1) / N;
                int goal_c = (val - 1) % N;
                d += abs(i - goal_r) + abs(j - goal_c);
            }
        }
    return d;
}

// Copy board
void copy(int src[N][N], int dest[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dest[i][j] = src[i][j];
}

// Compare two boards
int isSame(int a[N][N], int b[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j] != b[i][j]) return 0;
    return 1;
}

// Find blank position
void findBlank(int board[N][N], int *x, int *y) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == 0) {
                *x = i; *y = j;
                return;
            }
}

// Greedy Best-First Search (without priority queue)
void bestFirstSearch(int start[N][N]) {
    int dx[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
    int dy[] = {0, 0, -1, 1};

    int curr[N][N];
    copy(start, curr);

    for (int steps = 0; steps < MAX_STATES; steps++) {
        printf("Step %d:\n", steps);
        printBoard(curr);
        if (isSame(curr, goal)) {
            printf("Goal reached!\n");
            return;
        }

        int bx, by;
        findBlank(curr, &bx, &by);

        int best_h = 9999;
        int best_board[N][N];

        // Try all 4 moves and pick the best one (lowest heuristic)
        for (int d = 0; d < 4; d++) {
            int nx = bx + dx[d];
            int ny = by + dy[d];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                int temp[N][N];
                copy(curr, temp);
                // Swap blank with neighbor
                temp[bx][by] = temp[nx][ny];
                temp[nx][ny] = 0;

                int h = manhattan(temp);
                if (h < best_h) {
                    best_h = h;
                    copy(temp, best_board);
                }
            }
        }

        // Update current board to best found move
        copy(best_board, curr);
    }

    printf("Reached max steps without finding goal.\n");
}

int main() {
    int start[N][N] = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    printf("Initial state:\n");
    printBoard(start);

    bestFirstSearch(start);

    return 0;
}
