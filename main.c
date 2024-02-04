#include <stdio.h>
#include "stdlib.h"

const unsigned char win_count = 8;
unsigned short winning[] = {
        7 << 6,
        7 << 3,
        7,
        292,
        146,
        73,
        273,
        84
};

int row_count = 3, col_count = 3, toggle = 0;
char player[2] = "XO";

void printBoard(const unsigned short board[]);
char checkWinning(const unsigned short board[]);

int main() {
    unsigned short board[2] = {0, 0};

    unsigned char is_win = 0;
    for (int i = 0, row, col, index, offset = 1; i < (row_count * col_count); ++i, toggle = !toggle) {
        do {
            printf("Player %c's turn. Enter the row (1-%d) and column (1-%d):\n", player[toggle], row_count, col_count);
            scanf("%d", &row);
            scanf("%d", &col);
            row -= offset, col -= offset;
            index = (row * row_count) + col;
        } while (row >= row_count || row < 0 || col >= col_count || col < 0 ||
                ((board[0] >> index) & 1) == 1 || ((board[1] >> index) & 1) == 1) ;

        board[toggle] = board[toggle] | (1 << ((row * row_count) + col));
        printBoard(board);
        if (checkWinning(board)) {
            is_win = 1;
            break;
        }
    }

    if (is_win) printf("Congratulations Player %c for winning!!!", player[toggle]);
    else printf("Tie.");

    return 0;
}

void printBoard(const unsigned short board[]) {
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

            int index = (i * row_count) + j;
            if (((board[0] >> index) & 1) == 0 &&
                ((board[1] >> index) & 1) == 0) {
                printf("%c", ' ');
            } else {
                printf("%c", player[((board[1] >> index) & 1)]);
            }
        }
        printf("\n");
    }
}

char checkWinning(const unsigned short board[]) {
    for (int i = 0; i < win_count; ++i) {
        if (board[toggle] == winning[i]) {
            return 1;
        }
    }

    return 0;
}