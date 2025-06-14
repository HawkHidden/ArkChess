#include "move_queen.h"   // 皇后走法声明
#include "board.h"        // 棋子编号与棋盘数组定义
// 判断皇后是否能从 (fromX, fromY) 移动到 (toX, toY)
bool canMoveQueen(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // ① 起点终点不能相同（不能原地不动）
    if (fromX == toX && fromY == toY) {
        return false;
    }
    int dx = toX - fromX;  // 横向移动距离
    int dy = toY - fromY;  // 纵向移动距离
    // ② 皇后可以走直线或斜线
    bool isStraight = (dx == 0 || dy == 0);             // 横线/竖线
    bool isDiagonal = (abs(dx) == abs(dy));             // 对角线（45度）
    if (!isStraight && !isDiagonal) {
        return false;  // 非直非斜：非法走法
    }
    // ③ 计算每步的移动方向（单位步长）
    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);
    int x = fromX + stepX;
    int y = fromY + stepY;
    // ④ 检查路径是否被阻挡（不能越过任何棋子）
    while (x != toX || y != toY) {
        if (board[y][x] != EMPTY) {
            return false;  // 有障碍，不能移动
        }
        x += stepX;
        y += stepY;
    }
    // ⑤ 最终目标位置的合法性判断（不能吃自己）
    int piece = board[fromY][fromX];                  // 自己
    int target = board[toY][toX];                     // 目标格子上的棋子
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    bool targetIsWhite = (target >= PAWN_WHITE && target <= KING_WHITE);
    bool targetIsBlack = (target >= PAWN_BLACK && target <= KING_BLACK);
    if ((isWhite && targetIsWhite) || (!isWhite && targetIsBlack)) {
        return false;  // 自己人，不能吃
    }
    // ⑥ 通过所有检查，走法合法
    return true;
}
