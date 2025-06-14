#include "move_queen.h"   // �ʺ��߷�����
#include "board.h"        // ���ӱ�����������鶨��
// �жϻʺ��Ƿ��ܴ� (fromX, fromY) �ƶ��� (toX, toY)
bool canMoveQueen(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // �� ����յ㲻����ͬ������ԭ�ز�����
    if (fromX == toX && fromY == toY) {
        return false;
    }
    int dx = toX - fromX;  // �����ƶ�����
    int dy = toY - fromY;  // �����ƶ�����
    // �� �ʺ������ֱ�߻�б��
    bool isStraight = (dx == 0 || dy == 0);             // ����/����
    bool isDiagonal = (abs(dx) == abs(dy));             // �Խ��ߣ�45�ȣ�
    if (!isStraight && !isDiagonal) {
        return false;  // ��ֱ��б���Ƿ��߷�
    }
    // �� ����ÿ�����ƶ����򣨵�λ������
    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);
    int x = fromX + stepX;
    int y = fromY + stepY;
    // �� ���·���Ƿ��赲������Խ���κ����ӣ�
    while (x != toX || y != toY) {
        if (board[y][x] != EMPTY) {
            return false;  // ���ϰ��������ƶ�
        }
        x += stepX;
        y += stepY;
    }
    // �� ����Ŀ��λ�õĺϷ����жϣ����ܳ��Լ���
    int piece = board[fromY][fromX];                  // �Լ�
    int target = board[toY][toX];                     // Ŀ������ϵ�����
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    bool targetIsWhite = (target >= PAWN_WHITE && target <= KING_WHITE);
    bool targetIsBlack = (target >= PAWN_BLACK && target <= KING_BLACK);
    if ((isWhite && targetIsWhite) || (!isWhite && targetIsBlack)) {
        return false;  // �Լ��ˣ����ܳ�
    }
    // �� ͨ�����м�飬�߷��Ϸ�
    return true;
}
