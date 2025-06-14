// move_knight.cpp
#include "move_knight.h"
#include "board.h"
#include <cmath>

bool canMoveKnight(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];
    if (piece != KNIGHT_WHITE && piece != KNIGHT_BLACK) return false;

    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);
    // L形走法：一个方向2格，另一个方向1格
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) return false;

    int target = board[toY][toX];
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // 中间可以有棋子，马能跳过
    return true;
}