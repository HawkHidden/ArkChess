// move_queen.cpp
#include "move_queen.h"
#include "move_rook.h"
#include "move_bishop.h"
#include "board.h"

bool canMoveQueen(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];
    if (piece != QUEEN_WHITE && piece != QUEEN_BLACK) return false;
    // 尝试车走法或象走法
    if (fromX == toX || fromY == toY) {
        return canMoveRook(board, fromX, fromY, toX, toY);
    }
    else if (std::abs(toX - fromX) == std::abs(toY - fromY)) {
        return canMoveBishop(board, fromX, fromY, toX, toY);
    }
    return false;
}