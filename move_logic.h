#pragma once
#include "board.h"

// �жϰױ��Ƿ��ܴ� (r, c) �ƶ��� (toR, toC)
bool canWhitePawnMove(int r, int c, int toR, int toC) {
    // һ��ֱ��
    if (toC == c && toR == r - 1 && board[toR][toC] == EMPTY)
        return true;

    // �״��ƶ�����
    if (r == 6 && toC == c && toR == r - 2 && board[r - 1][c] == EMPTY && board[toR][toC] == EMPTY)
        return true;

    // ���ӣ�б�Խǣ�
    if (toR == r - 1 && abs(toC - c) == 1 &&
        board[toR][toC] >= BPAWN && board[toR][toC] <= BKING)
        return true;

    return false;
}
