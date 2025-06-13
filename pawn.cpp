// pawn.cpp
#include "pawn.h"

// 辅助函数：判断两个棋子是否是敌对阵营
bool isEnemy(PieceType from, PieceType to) {
    if (from == EMPTY || to == EMPTY) return false;
    return (from <= WKING && to >= BPAWN) || (from >= BPAWN && to <= WKING);
}

// 判断一个小兵的移动是否合法
bool canPawnMove(int fromX, int fromY, int toX, int toY, PieceType piece, PieceType target, PieceType board[8][8]) {
    // 计算移动方向与距离
    int dx = toX - fromX;
    int dy = toY - fromY;

    // 白方小兵走法
    if (piece == WPAWN) {
        // 向上走（棋盘上Y减小）
        // 1. 普通前进一步，目标格子必须是空
        if (dx == 0 && dy == -1 && target == EMPTY) {
            return true;
        }

        // 2. 初始双步走：起点必须在第6行（从0开始的第6行是 y == 6），路径与目标格子都必须为空
        if (dx == 0 && dy == -2 && fromY == 6 &&
            board[fromY - 1][fromX] == EMPTY && target == EMPTY) {
            return true;
        }

        // 3. 吃子走法：斜向一步，必须攻击敌方棋子
        if ((dx == -1 || dx == 1) && dy == -1 && isEnemy(piece, target)) {
            return true;
        }
    }

    // 黑方小兵走法
    else if (piece == BPAWN) {
        // 向下走（棋盘上Y增加）
        // 1. 普通前进一步，目标格子必须是空
        if (dx == 0 && dy == 1 && target == EMPTY) {
            return true;
        }

        // 2. 初始双步走：起点必须在第1行（y == 1）
        if (dx == 0 && dy == 2 && fromY == 1 &&
            board[fromY + 1][fromX] == EMPTY && target == EMPTY) {
            return true;
        }

        // 3. 吃子走法：斜向一步，必须攻击敌方棋子
        if ((dx == -1 || dx == 1) && dy == 1 && isEnemy(piece, target)) {
            return true;
        }
    }

    // 如果不符合任意合法走法，则非法
    return false;
}
