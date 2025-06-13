#pragma once
#include "board.h"

// 判断白兵是否能从 (r, c) 移动到 (toR, toC)
bool canWhitePawnMove(int r, int c, int toR, int toC) {
    // 一格直走
    if (toC == c && toR == r - 1 && board[toR][toC] == EMPTY)
        return true;

    // 首次移动两格
    if (r == 6 && toC == c && toR == r - 2 && board[r - 1][c] == EMPTY && board[toR][toC] == EMPTY)
        return true;

    // 吃子（斜对角）
    if (toR == r - 1 && abs(toC - c) == 1 &&
        board[toR][toC] >= BPAWN && board[toR][toC] <= BKING)
        return true;

    return false;
}
