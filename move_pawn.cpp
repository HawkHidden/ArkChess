// move_pawn.cpp
#include "move_pawn.h"
#include "board.h"
#include <cmath>

bool canMovePawn(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];
    if (piece != PAWN_WHITE && piece != PAWN_BLACK) return false;
    int target = board[toY][toX];
    bool isWhite = (piece == PAWN_WHITE);

    int dir = isWhite ? -1 : 1;      // 白兵向上 (y 减小)，黑兵向下 (y 增大)
    int startRow = isWhite ? 6 : 1;  // 白兵初始行假设为 6，黑兵初始行为 1

    // 直走一格或两格
    if (toX == fromX) {
        // 一格前进，目标必须为空
        if (toY == fromY + dir && target == EMPTY) {
            return true;
        }
        // 初始两格前进，起始行且路径和终点均为空
        if (fromY == startRow && toY == fromY + 2 * dir) {
            int midY = fromY + dir;
            if (board[midY][fromX] == EMPTY && board[toY][toX] == EMPTY) {
                return true;
            }
        }
    }
    // 斜吃一格
    if ((toX == fromX + 1 || toX == fromX - 1) && toY == fromY + dir) {
        if (target != EMPTY) {
            // 目标必须是对方棋子
            if (isWhite && (target >= PAWN_BLACK && target <= KING_BLACK)) return true;
            if (!isWhite && (target >= PAWN_WHITE && target <= KING_WHITE)) return true;
        }
    }
    return false;
}