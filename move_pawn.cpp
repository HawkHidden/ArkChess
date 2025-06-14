#include "move_pawn.h"     // ����pawn���߷�����
#include "board.h"         // �������������ӱ�Ŷ���
#include <cmath>           // abs ���������ã�
// �жϱ��Ƿ��ܴ� (fromX, fromY) �ߵ� (toX, toY)
bool canMovePawn(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];                                 // ��ȡ��ǰ��
    if (piece != PAWN_WHITE && piece != PAWN_BLACK) return false;   // �����Ǳ�������
    int target = board[toY][toX];                                    // Ŀ����ϵ�����
    bool isWhite = (piece == PAWN_WHITE);                           // �ж��Ƿ�ױ�
    int dir = isWhite ? -1 : 1;      // �ױ����ϣ��кż������ڱ����£��к�����
    int startRow = isWhite ? 6 : 1;  // �ױ���ʼ��Ϊ��6�У��ڱ���ʼ��Ϊ��1��
    // �� ֱ�ߵ��߼���ֻ���ߵ��ո�
    if (toX == fromX) {
        // ǰ��һ���������ǿո�
        if (toY == fromY + dir && target == EMPTY) {
            return true;
        }
        // ��ʼλ�������ߣ��м����յ㶼����Ϊ�գ�
        if (fromY == startRow && toY == fromY + 2 * dir) {
            int midY = fromY + dir; // �м���һ��
            if (board[midY][fromX] == EMPTY && board[toY][toX] == EMPTY) {
                return true;
            }
        }
    }
    // �� б�ų����߼��������ǳԶԷ����ӣ�
    if ((toX == fromX + 1 || toX == fromX - 1) && toY == fromY + dir) {
        if (target != EMPTY) {
            // �ױ��Ժ��� �� �ڱ��԰���
            if (isWhite && (target >= PAWN_BLACK && target <= KING_BLACK)) return true;
            if (!isWhite && (target >= PAWN_WHITE && target <= KING_WHITE)) return true;
        }
    }
    // �Ƿ��߷�
    return false;
}
