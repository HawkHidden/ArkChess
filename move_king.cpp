#include "move_king.h"         // ���������߷�����������
#include "board.h"             // �����������������Ͷ���
#include <cmath>               // �ṩ abs �������ڼ������
// �жϹ�����King���Ƿ��ܴ� (fromX, fromY) �ƶ��� (toX, toY)
bool canMoveKing(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];                // ��ȡ��ǰ����
    if (piece != KING_WHITE && piece != KING_BLACK) return false; // �����ǹ������ܵ��ô˺���
    int dx = std::abs(toX - fromX);                 // �����ƶ�����
    int dy = std::abs(toY - fromY);                 // �����ƶ�����
    if (dx > 1 || dy > 1) return false;             // ����ÿ��ֻ���ƶ�һ�������ⷽ��
    int target = board[toY][toX];                   // ��ȡĿ����ӵ�����
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE); // �ж��Ƿ�Ϊ�׷�����
    // ��Ŀ������Ǽ������ӣ������ƶ���ȥ
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    return true; // һ�����ߡ�Ŀ����޼����ӣ���Ϸ�
}
