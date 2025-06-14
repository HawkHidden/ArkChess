#include "move_rook.h"   // 声明车（Rook）的走法判断接口
#include "board.h"       // 包含棋盘数组与棋子类型定义
#include <cmath>         // 提供数学函数
// 判断车（Rook）是否能从 (fromX, fromY) 移动到 (toX, toY)
bool canMoveRook(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // ① 起点和终点不能相同，且起点必须为车
    if (fromX == toX && fromY == toY) return false;
    int piece = board[fromY][fromX];
    if (piece != ROOK_WHITE && piece != ROOK_BLACK) return false;
    // ② 目标格子不能有己方棋子
    int target = board[toY][toX];
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // ③ 水平移动逻辑：同一行（fromY == toY）
    if (fromY == toY) {
        // 确定左右方向的步长（+1 向右，-1 向左）
        int step = (toX > fromX) ? 1 : -1;
        // 检查起点与终点之间的每个格子，必须都是空的
        for (int x = fromX + step; x != toX; x += step) {
            if (board[fromY][x] != EMPTY) return false;
        }
        return true;  // 路径清空，水平移动合规
    }
    // ④ 垂直移动逻辑：同一列（fromX == toX）
    if (fromX == toX) {
        // 确定上下方向的步长（+1 向下，-1 向上）
        int step = (toY > fromY) ? 1 : -1;
        // 检查起点与终点之间的每个格子，必须都是空的
        for (int y = fromY + step; y != toY; y += step) {
            if (board[y][fromX] != EMPTY) return false;
        }
        return true;  // 路径清空，垂直移动合法
    }
    // ⑤ 既不同行也不同列，既非水平也非垂直，非法走法
    return false;
}
