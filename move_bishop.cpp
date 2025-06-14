#include "move_bishop.h"       // ������ǰ�ļ���ʹ�õ��߷�����
#include "board.h"             // �����������������͵Ķ���
#include <cmath>               // �ṩ abs ����ѧ�����������ж���б�ߣ�
// �ж���Bishop���Ƿ���Դ� (fromX, fromY) �ߵ� (toX, toY)
bool canMoveBishop(int board[8][8], int fromX, int fromY, int toX, int toY) {
    if (fromX == toX && fromY == toY) return false; // ����ԭ�ز���
    int piece = board[fromY][fromX];                // ��ȡ��������
    if (piece != BISHOP_WHITE && piece != BISHOP_BLACK) return false; // �������󣬷Ƿ�����
    int target = board[toY][toX];                   // ��ȡĿ����ӵ�����
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE); // �жϵ�ǰ�Ƿ�׷�����
    // ���Ŀ������Ǽ������ӣ������ƶ�
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    int dx = toX - fromX;         // ����λ��
    int dy = toY - fromY;         // ����λ��
    if (std::abs(dx) != std::abs(dy)) return false; // ������߶Խ��ߣ�����λ�ƾ���ֵ��ȣ�
    // ȷ���Խ��߷���Ĳ�������+1 �� -1��
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    // ��������ǰ�������·���Ƿ����赲�����ܷ�Ծ��
    int x = fromX + stepX, y = fromY + stepY;
    while (x != toX && y != toY) {
        if (board[y][x] != EMPTY) return false; // ·�������ӣ�������
        x += stepX; y += stepY;
    }
    return true; // ·�߳�ͨ��Ŀ���ɴ�
}
