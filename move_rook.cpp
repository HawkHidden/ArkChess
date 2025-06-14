// move_rook.cpp
#include "move_rook.h"
#include "board.h" // ������� PieceType ö�ٶ���
#include <cmath>

bool canMoveRook(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // �����㡢�յ��Ƿ�ͬ������г�
    if (fromX == toX && fromY == toY) return false;
    int piece = board[fromY][fromX];
    if (piece != ROOK_WHITE && piece != ROOK_BLACK) return false;

    int target = board[toY][toX];
    // �ж�Ŀ����Ƿ��м�������
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }

    // ˮƽ�ƶ���ͬһ��
    if (fromY == toY) {
        int step = (toX > fromX) ? 1 : -1;
        for (int x = fromX + step; x != toX; x += step) {
            if (board[fromY][x] != EMPTY) return false; // �м�����
        }
        return true;
    }
    // ��ֱ�ƶ���ͬһ��
    if (fromX == toX) {
        int step = (toY > fromY) ? 1 : -1;
        for (int y = fromY + step; y != toY; y += step) {
            if (board[y][fromX] != EMPTY) return false;
        }
        return true;
    }
    // �Ȳ�ͬ��Ҳ��ͬ�У��߷���Ч
    return false;
}