#include "move_pawn.h"     // 兵（pawn）走法声明
#include "board.h"         // 引入棋盘与棋子编号定义
#include <cmath>           // abs 函数（备用）
// 判断兵是否能从 (fromX, fromY) 走到 (toX, toY)
bool canMovePawn(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];                                 // 获取当前兵
    if (piece != PAWN_WHITE && piece != PAWN_BLACK) return false;   // 若不是兵，报错
    int target = board[toY][toX];                                    // 目标格上的棋子
    bool isWhite = (piece == PAWN_WHITE);                           // 判断是否白兵
    int dir = isWhite ? -1 : 1;      // 白兵向上（行号减），黑兵向下（行号增）
    int startRow = isWhite ? 6 : 1;  // 白兵起始行为第6行，黑兵起始行为第1行
    // ① 直走滴逻辑（只能走到空格）
    if (toX == fromX) {
        // 前进一步（必须是空格）
        if (toY == fromY + dir && target == EMPTY) {
            return true;
        }
        // 起始位置两步走（中间与终点都必须为空）
        if (fromY == startRow && toY == fromY + 2 * dir) {
            int midY = fromY + dir; // 中间那一格
            if (board[midY][fromX] == EMPTY && board[toY][toX] == EMPTY) {
                return true;
            }
        }
    }
    // ② 斜着吃子逻辑（必须是吃对方棋子）
    if ((toX == fromX + 1 || toX == fromX - 1) && toY == fromY + dir) {
        if (target != EMPTY) {
            // 白兵吃黑子 或 黑兵吃白子
            if (isWhite && (target >= PAWN_BLACK && target <= KING_BLACK)) return true;
            if (!isWhite && (target >= PAWN_WHITE && target <= KING_WHITE)) return true;
        }
    }
    // 非法走法
    return false;
}
