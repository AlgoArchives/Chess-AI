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



std::vector<std::pair<int, int>> generatePawnMoves(int x, int y, bool isWhite) {
    std::vector<std::pair<int, int>> moves;
    int direction = isWhite ? -1 : 1;
    if (board[x + direction][y] == EMPTY) { // Forward move
        moves.push_back({x + direction, y});
    }
    // Add other pawn moves (captures, en passant) here
    return moves;
}

std::vector<std::pair<int, int>> generateKnightMoves(int x, int y) {
    std::vector<std::pair<int, int>> moves;
    const int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (auto& move : knightMoves) {
        int newX = x + move[0];
        int newY = y + move[1];
        if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
            moves.push_back({newX, newY});
        }
    }
    return moves;
}



int evaluateBoard() {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            score += board[i][j]; // Simple evaluation: positive for white, negative for black
        }
    }
    return score;
}




int minimax(int depth, bool isMaximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard();
    }
    
    if (isMaximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        // Loop through all possible moves for maximizing player
        // For each move:
        //     int eval = minimax(depth - 1, false, alpha, beta);
        //     maxEval = std::max(maxEval, eval);
        //     alpha = std::max(alpha, eval);
        //     if (beta <= alpha)
        //         break;
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        // Loop through all possible moves for minimizing player
        // For each move:
        //     int eval = minimax(depth - 1, true, alpha, beta);
        //     minEval = std::min(minEval, eval);
        //     beta = std::min(beta, eval);
        //     if (beta <= alpha)
        //         break;
        return minEval;
    }
}
