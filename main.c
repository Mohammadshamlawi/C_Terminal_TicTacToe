#include <stdio.h>

#define AXIS_COUNT (const unsigned char) 3
#define PLAYERS "XO"
#define H_BOUNDARY "-+-+-\n"
#define WIN_COUNT (const unsigned char) 8
const unsigned short winning[] = {
        7,      // 0 0000 0111
        56,     // 0 0011 1000
        73,     // 0 0100 1001
        84,     // 0 0101 0100
        146,    // 0 1001 0010
        273,    // 1 0001 0001
        292,    // 1 0010 0100
        448     // 1 1100 0000
};

unsigned short board[2] = {0, 0};
unsigned char toggle = 0, is_win = 0;

void printBoard();
char checkWinning();

int main() {
    for (int i = 0, row, col, index, offset = 1; i < (AXIS_COUNT * AXIS_COUNT); ++i, toggle = !toggle) {
        do {
            printf("Player %c's turn. Enter the row (1-%d) and column (1-%d):\n", PLAYERS[toggle], AXIS_COUNT, AXIS_COUNT);
            scanf("%d", &row);
            scanf("%d", &col);
            row -= offset, col -= offset;
            index = (row * AXIS_COUNT) + col;
        } while (row >= AXIS_COUNT || row < 0 || col >= AXIS_COUNT || col < 0 ||
                ((board[0] >> index) & 1) == 1 || ((board[1] >> index) & 1) == 1) ;

        board[toggle] = board[toggle] | (1 << ((row * AXIS_COUNT) + col));
        printBoard();
        if (checkWinning()) {
            is_win = 1;
            break;
        }
    }

    if (is_win) printf("\nCongratulations!!! Player %c Wins!!!", PLAYERS[toggle]);
    else printf("\nTie.");

    return 0;
}

void printBoard() {
    for (int i = 0, row_index = 0; i < AXIS_COUNT; i++, row_index += AXIS_COUNT) {
        if (i != 0) printf("%s", H_BOUNDARY);

        for (int j = 0, index = row_index; j < AXIS_COUNT; j++, index++) {
            if (j != 0) printf("|");

            if (((board[0] >> index) & 1) == 0 && ((board[1] >> index) & 1) == 0) printf("%c", ' ');
            else printf("%c", PLAYERS[((board[1] >> index) & 1)]);
        }
        printf("\n");
    }
}

char checkWinning() {
    int low = 0, high = WIN_COUNT - 1, mid;
    do {
        mid = low + (high - low) / 2;
        if ((board[toggle] & winning[mid]) == winning[mid]) return 1;

        if (board[toggle] > winning[mid]) low = mid + 1;
        else high = mid - 1;
    } while (low <= high);

    return 0;
}