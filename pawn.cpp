// pawn.cpp
#include "pawn.h"

// �����������ж����������Ƿ��ǵж���Ӫ
bool isEnemy(PieceType from, PieceType to) {
    if (from == EMPTY || to == EMPTY) return false;
    return (from <= WKING && to >= BPAWN) || (from >= BPAWN && to <= WKING);
}

// �ж�һ��С�����ƶ��Ƿ�Ϸ�
bool canPawnMove(int fromX, int fromY, int toX, int toY, PieceType piece, PieceType target, PieceType board[8][8]) {
    // �����ƶ����������
    int dx = toX - fromX;
    int dy = toY - fromY;

    // �׷�С���߷�
    if (piece == WPAWN) {
        // �����ߣ�������Y��С��
        // 1. ��ͨǰ��һ����Ŀ����ӱ����ǿ�
        if (dx == 0 && dy == -1 && target == EMPTY) {
            return true;
        }

        // 2. ��ʼ˫���ߣ��������ڵ�6�У���0��ʼ�ĵ�6���� y == 6����·����Ŀ����Ӷ�����Ϊ��
        if (dx == 0 && dy == -2 && fromY == 6 &&
            board[fromY - 1][fromX] == EMPTY && target == EMPTY) {
            return true;
        }

        // 3. �����߷���б��һ�������빥���з�����
        if ((dx == -1 || dx == 1) && dy == -1 && isEnemy(piece, target)) {
            return true;
        }
    }

    // �ڷ�С���߷�
    else if (piece == BPAWN) {
        // �����ߣ�������Y���ӣ�
        // 1. ��ͨǰ��һ����Ŀ����ӱ����ǿ�
        if (dx == 0 && dy == 1 && target == EMPTY) {
            return true;
        }

        // 2. ��ʼ˫���ߣ��������ڵ�1�У�y == 1��
        if (dx == 0 && dy == 2 && fromY == 1 &&
            board[fromY + 1][fromX] == EMPTY && target == EMPTY) {
            return true;
        }

        // 3. �����߷���б��һ�������빥���з�����
        if ((dx == -1 || dx == 1) && dy == 1 && isEnemy(piece, target)) {
            return true;
        }
    }

    // �������������Ϸ��߷�����Ƿ�
    return false;
}
