// move_pawn.cpp
#include "move_pawn.h"
#include "board.h"
#include <cmath>

bool canMovePawn(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];
    if (piece != PAWN_WHITE && piece != PAWN_BLACK) return false;
    int target = board[toY][toX];
    bool isWhite = (piece == PAWN_WHITE);

    int dir = isWhite ? -1 : 1;      // �ױ����� (y ��С)���ڱ����� (y ����)
    int startRow = isWhite ? 6 : 1;  // �ױ���ʼ�м���Ϊ 6���ڱ���ʼ��Ϊ 1

    // ֱ��һ�������
    if (toX == fromX) {
        // һ��ǰ����Ŀ�����Ϊ��
        if (toY == fromY + dir && target == EMPTY) {
            return true;
        }
        // ��ʼ����ǰ������ʼ����·�����յ��Ϊ��
        if (fromY == startRow && toY == fromY + 2 * dir) {
            int midY = fromY + dir;
            if (board[midY][fromX] == EMPTY && board[toY][toX] == EMPTY) {
                return true;
            }
        }
    }
    // б��һ��
    if ((toX == fromX + 1 || toX == fromX - 1) && toY == fromY + dir) {
        if (target != EMPTY) {
            // Ŀ������ǶԷ�����
            if (isWhite && (target >= PAWN_BLACK && target <= KING_BLACK)) return true;
            if (!isWhite && (target >= PAWN_WHITE && target <= KING_WHITE)) return true;
        }
    }
    return false;
}