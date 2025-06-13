#pragma once
#include "board.h"

// ==================== 小兵移动规则 ====================
// 说明：此模块包含白兵（WPAWN）与黑兵（BPAWN）的基本移动逻辑。
// 包括：
// - 单步前进
// - 首步双格前进
// - 吃子（斜对角）
// =====================================================

// 判断白兵（WPAWN）是否能从 (r, c) 移动到 (toR, toC)
bool canWhitePawnMove(int r, int c, int toR, int toC) {
    // 白兵向上移动（行数减小）

    // 1. 向前移动一格
    if (toC == c && toR == r - 1 && board[toR][toC] == EMPTY)
        return true;

    // 2. 首次移动，两格前进
    if (r == 6 && toC == c && toR == r - 2 &&
        board[r - 1][c] == EMPTY && board[toR][toC] == EMPTY)
        return true;

    // 3. 吃子：对角线移动（敌方棋子）
    if (toR == r - 1 && abs(toC - c) == 1 &&
        board[toR][toC] >= BPAWN && board[toR][toC] <= BKING)
        return true;

    return false;
}

// 判断黑兵（BPAWN）是否能从 (r, c) 移动到 (toR, toC)
bool canBlackPawnMove(int r, int c, int toR, int toC) {
    // 黑兵向下移动（行数增大）

    // 1. 向前移动一格
    if (toC == c && toR == r + 1 && board[toR][toC] == EMPTY)
        return true;

    // 2. 首次移动，两格前进
    if (r == 1 && toC == c && toR == r + 2 &&
        board[r + 1][c] == EMPTY && board[toR][toC] == EMPTY)
        return true;

    // 3. 吃子：对角线移动（敌方棋子）
    if (toR == r + 1 && abs(toC - c) == 1 &&
        board[toR][toC] >= WPAWN && board[toR][toC] <= WKING)
        return true;

    return false;
}
