#include <stdio.h>

int rows = 3, cols = 3;

void printBoard();

int main() {
//    printf("Hello, World!\n");

    printBoard();

    return 0;
}

void printBoard() {
    for (int i = 0; i < rows; i++) {

        if (i != 0) {
            for (int j = 0; j < cols; ++j) {
                if (j != 0) printf("+_");
                else printf("_");
            }
            printf("\n");
        }

        for (int j = 0; j < cols - 1; j++) {
            printf(" |");
        }
        printf(" \n");
    }
}