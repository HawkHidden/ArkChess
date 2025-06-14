// move_bishop.cpp
#include "move_bishop.h"
#include "board.h"
#include <cmath>

bool canMoveBishop(int board[8][8], int fromX, int fromY, int toX, int toY) {
    if (fromX == toX && fromY == toY) return false;
    int piece = board[fromY][fromX];
    if (piece != BISHOP_WHITE && piece != BISHOP_BLACK) return false;

    int target = board[toY][toX];
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }

    int dx = toX - fromX;
    int dy = toY - fromY;
    if (std::abs(dx) != std::abs(dy)) return false; // 必须走对角线
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    int x = fromX + stepX, y = fromY + stepY;
    while (x != toX && y != toY) {
        if (board[y][x] != EMPTY) return false;
        x += stepX; y += stepY;
    }
    return true;
}