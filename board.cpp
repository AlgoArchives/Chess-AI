#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

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

// Generate moves for pawns
std::vector<std::pair<int, int>> generatePawnMoves(int x, int y, bool isWhite) {
    std::vector<std::pair<int, int>> moves;
    int direction = isWhite ? -1 : 1;
    if (x + direction >= 0 && x + direction < BOARD_SIZE && board[x + direction][y] == EMPTY) {
        moves.push_back({x + direction, y});  // Move forward
    }
    // Capture diagonally
    if (y - 1 >= 0 && board[x + direction][y - 1] * (isWhite ? -1 : 1) > 0) {
        moves.push_back({x + direction, y - 1});
    }
    if (y + 1 < BOARD_SIZE && board[x + direction][y + 1] * (isWhite ? -1 : 1) > 0) {
        moves.push_back({x + direction, y + 1});
    }
    return moves;
}

// Generate moves for knights
std::vector<std::pair<int, int>> generateKnightMoves(int x, int y) {
    std::vector<std::pair<int, int>> moves;
    const int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (auto& move : knightMoves) {
        int newX = x + move[0];
        int newY = y + move[1];
        if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE && (board[newX][newY] * board[x][y]) <= 0) {
            moves.push_back({newX, newY});
        }
    }
    return moves;
}

// Evaluation function
int evaluateBoard() {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            score += board[i][j]; // Simplified: positive score for white, negative for black
        }
    }
    return score;
}

// Minimax with Alpha-Beta Pruning
int minimax(int depth, bool isMaximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard();
    }

    if (isMaximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] > 0) { // White pieces
                    auto moves = generatePawnMoves(i, j, true);
                    for (auto& move : moves) {
                        int temp = board[move.first][move.second];
                        board[move.first][move.second] = board[i][j];
                        board[i][j] = EMPTY;

                        int eval = minimax(depth - 1, false, alpha, beta);
                        maxEval = std::max(maxEval, eval);
                        alpha = std::max(alpha, eval);

                        board[i][j] = board[move.first][move.second];
                        board[move.first][move.second] = temp;

                        if (beta <= alpha) break;
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] < 0) { // Black pieces
                    auto moves = generatePawnMoves(i, j, false);
                    for (auto& move : moves) {
                        int temp = board[move.first][move.second];
                        board[move.first][move.second] = board[i][j];
                        board[i][j] = EMPTY;

                        int eval = minimax(depth - 1, true, alpha, beta);
                        minEval = std::min(minEval, eval);
                        beta = std::min(beta, eval);

                        board[i][j] = board[move.first][move.second];
                        board[move.first][move.second] = temp;

                        if (beta <= alpha) break;
                    }
                }
            }
        }
        return minEval;
    }
}

void playGame() {
    int turn = 1; // White's turn
    while (true) {
        printBoard();
        int score = minimax(3, turn == 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        std::cout << "Score: " << score << std::endl;
        turn *= -1;
    }
}

int main() {
    playGame();
    return 0;
}