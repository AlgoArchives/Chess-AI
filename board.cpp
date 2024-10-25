#include <iostream>
#include <vector>
#include <limits>

enum Piece {
    EMPTY = 0,
    WHITE_PAWN = 1, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
    BLACK_PAWN = -1, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING
};

const int BOARD_SIZE = 8;
int board[BOARD_SIZE][BOARD_SIZE] = {
    {-4, -2, -3, -5, -6, -3, -2, -4},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 1,  1,  1,  1,  1,  1,  1,  1},
    { 4,  2,  3,  5,  6,  3,  2,  4}
};

void printBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}