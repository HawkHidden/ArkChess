// move_rook.cpp
#include "move_rook.h"
#include "board.h" // 假设包含 PieceType 枚举定义
#include <cmath>

bool canMoveRook(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // 检查起点、终点是否不同且起点有车
    if (fromX == toX && fromY == toY) return false;
    int piece = board[fromY][fromX];
    if (piece != ROOK_WHITE && piece != ROOK_BLACK) return false;

    int target = board[toY][toX];
    // 判断目标格是否有己方棋子
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }

    // 水平移动：同一行
    if (fromY == toY) {
        int step = (toX > fromX) ? 1 : -1;
        for (int x = fromX + step; x != toX; x += step) {
            if (board[fromY][x] != EMPTY) return false; // 中间必须空
        }
        return true;
    }
    // 垂直移动：同一列
    if (fromX == toX) {
        int step = (toY > fromY) ? 1 : -1;
        for (int y = fromY + step; y != toY; y += step) {
            if (board[y][fromX] != EMPTY) return false;
        }
        return true;
    }
    // 既不同行也不同列，走法无效
    return false;
}