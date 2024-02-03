#include <stdio.h>
#include "stdlib.h"

int row_count = 3, col_count = 3, player_count = 2, turns = 0, toggle = 0, max_match = 3;
int **rows, **cols, **diag, **anti_diag;
char player[2] = "XO";

void printBoard(char (*board)[]);

void init() {
    rows = calloc(player_count, sizeof(int *));
    cols = calloc(player_count, sizeof(int *));
    diag = calloc(player_count, sizeof(int *));
    anti_diag = calloc(player_count, sizeof(int *));

    for (int i = 0; i < player_count; ++i) {
        rows[i] = calloc(row_count, sizeof(int));
        cols[i] = calloc(col_count, sizeof(int));
        diag[i] = calloc(row_count > col_count ? col_count : row_count, sizeof(int));
        anti_diag[i] = calloc(row_count > col_count ? col_count : row_count, sizeof(int));
    }
}

int main() {
    init();

    char (*board)[col_count] = calloc(row_count * col_count, sizeof(*board));
    if (board == NULL) {
        printf("Not Enough Memory.");
        exit(1);
    }

    int offset = 1;
    for (int i = 0; i < (row_count * col_count); ++i) {
        turns += !toggle;
        int row = offset, col = offset;

        do {
            printf("Player %c's turn. Enter the row (1-%d) and column (1-%d):\n", player[toggle], row_count, col_count);
            scanf("%d", &row);
            scanf("%d", &col);
        } while (row > row_count || row < offset || col > col_count || col < offset ||
                (board[row - offset][col - offset] != ' ' && board[row - offset][col - offset] != 0)) ;

        row = row - offset;
        col = col - offset;
        board[row][col] = player[toggle];
        rows[toggle][row]++;
        cols[toggle][col]++;
        if (row == col) diag[toggle][0]++;
        if (row + (col_count - 1) == col || row == col || col + (col_count - 1) == row) anti_diag[toggle][0]++;

        printBoard(board);

        if (rows[toggle][row] == max_match || cols[toggle][col] == max_match ||
            diag[toggle][0] == max_match || anti_diag[toggle][0] == max_match) {
            break;
        }

        toggle = !toggle;
    }

    return 0;
}

void printBoard(char (*board)[col_count]) {
    for (int i = 0; i < row_count; i++) {

        if (i != 0) {
            for (int j = 0; j < col_count; ++j) {
                if (j != 0) printf("+_");
                else printf("_");
            }
            printf("\n");
        }

        for (int j = 0; j < col_count; j++) {
            if (j != 0) printf("|");

            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}