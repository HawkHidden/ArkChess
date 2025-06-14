#include "move_bishop.h"       // 声明当前文件中使用的走法函数
#include "board.h"             // 包含棋盘与棋子类型的定义
#include <cmath>               // 提供 abs 等数学函数（用于判断走斜线）
// 判断象（Bishop）是否可以从 (fromX, fromY) 走到 (toX, toY)
bool canMoveBishop(int board[8][8], int fromX, int fromY, int toX, int toY) {
    if (fromX == toX && fromY == toY) return false; // 不能原地不动
    int piece = board[fromY][fromX];                // 获取起点的棋子
    if (piece != BISHOP_WHITE && piece != BISHOP_BLACK) return false; // 若不是象，非法调用
    int target = board[toY][toX];                   // 获取目标格子的棋子
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE); // 判断当前是否白方棋子
    // 如果目标格子是己方棋子，则不能移动
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    int dx = toX - fromX;         // 横向位移
    int dy = toY - fromY;         // 纵向位移
    if (std::abs(dx) != std::abs(dy)) return false; // 象必须走对角线（横纵位移绝对值相等）
    // 确定对角线方向的步进方向（+1 或 -1）
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    // 从起点逐格前进，检查路径是否有阻挡（不能飞跃）
    int x = fromX + stepX, y = fromY + stepY;
    while (x != toX && y != toY) {
        if (board[y][x] != EMPTY) return false; // 路上有棋子，不能走
        x += stepX; y += stepY;
    }
    return true; // 路线畅通，目标格可达
}
