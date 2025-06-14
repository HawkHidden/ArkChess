#include "move_queen.h"
#include "board.h"

// �жϻʺ��߷��Ƿ�Ϲ棨ֱ�� + б�߾��ɣ�
bool canMoveQueen(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // 1. ������յ㲻����ͬ�����ܲ�����
    if (fromX == toX && fromY == toY) {
        return false;
    }

    int dx = toX - fromX;
    int dy = toY - fromY;

    // 2. ȷ���ߵ���ֱ�� or �Խ���
    bool isStraight = (dx == 0 || dy == 0);
    bool isDiagonal = (abs(dx) == abs(dy));

    if (!isStraight && !isDiagonal) {
        // �Ȳ���ֱ��Ҳ����б��
        return false;
    }

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int x = fromX + stepX;
    int y = fromY + stepY;

    // 3. ���·�����Ƿ����赲������Խ�ӣ�
    while (x != toX || y != toY) {
        if (board[y][x] != EMPTY) {
            return false;  // ·�����赲
        }
        x += stepX;
        y += stepY;
    }

    // 4. �ж�Ŀ���Ƿ�Ϊ�з����
    int piece = board[fromY][fromX];
    int target = board[toY][toX];

    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    bool targetIsWhite = (target >= PAWN_WHITE && target <= KING_WHITE);
    bool targetIsBlack = (target >= PAWN_BLACK && target <= KING_BLACK);

    if ((isWhite && targetIsWhite) || (!isWhite && targetIsBlack)) {
        return false;  // ��������Լ�
    }

    // �Ϸ��ƶ�
    return true;
}
