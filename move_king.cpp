// move_king.cpp
#include "move_king.h"
#include "board.h"
#include <cmath>

bool canMoveKing(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];
    if (piece != KING_WHITE && piece != KING_BLACK) return false;

    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);
    // 只允许走一格任何方向
    if (dx > 1 || dy > 1) return false;

    int target = board[toY][toX];
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    return true;
}