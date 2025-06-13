#pragma once
#include "board.h"

// ==================== С���ƶ����� ====================
// ˵������ģ������ױ���WPAWN����ڱ���BPAWN���Ļ����ƶ��߼���
// ������
// - ����ǰ��
// - �ײ�˫��ǰ��
// - ���ӣ�б�Խǣ�
// =====================================================

// �жϰױ���WPAWN���Ƿ��ܴ� (r, c) �ƶ��� (toR, toC)
bool canWhitePawnMove(int r, int c, int toR, int toC) {
    // �ױ������ƶ���������С��

    // 1. ��ǰ�ƶ�һ��
    if (toC == c && toR == r - 1 && board[toR][toC] == EMPTY)
        return true;

    // 2. �״��ƶ�������ǰ��
    if (r == 6 && toC == c && toR == r - 2 &&
        board[r - 1][c] == EMPTY && board[toR][toC] == EMPTY)
        return true;

    // 3. ���ӣ��Խ����ƶ����з����ӣ�
    if (toR == r - 1 && abs(toC - c) == 1 &&
        board[toR][toC] >= BPAWN && board[toR][toC] <= BKING)
        return true;

    return false;
}

// �жϺڱ���BPAWN���Ƿ��ܴ� (r, c) �ƶ��� (toR, toC)
bool canBlackPawnMove(int r, int c, int toR, int toC) {
    // �ڱ������ƶ�����������

    // 1. ��ǰ�ƶ�һ��
    if (toC == c && toR == r + 1 && board[toR][toC] == EMPTY)
        return true;

    // 2. �״��ƶ�������ǰ��
    if (r == 1 && toC == c && toR == r + 2 &&
        board[r + 1][c] == EMPTY && board[toR][toC] == EMPTY)
        return true;

    // 3. ���ӣ��Խ����ƶ����з����ӣ�
    if (toR == r + 1 && abs(toC - c) == 1 &&
        board[toR][toC] >= WPAWN && board[toR][toC] <= WKING)
        return true;

    return false;
}
