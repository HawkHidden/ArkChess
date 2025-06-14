#include "move_knight.h"         // ������Knight�����߷��жϺ���
#include "board.h"               // �����������������Ͷ���
#include <cmath>                 // �ṩ abs ���������ھ������
// �ж���Knight���Ƿ��ܴ� (fromX, fromY) �ƶ��� (toX, toY)
bool canMoveKnight(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];                             // ��ǰѡ�е�����
    if (piece != KNIGHT_WHITE && piece != KNIGHT_BLACK) return false; // ֻ�ܴ�������ƶ�
    int dx = std::abs(toX - fromX);                              // �������
    int dy = std::abs(toY - fromY);                              // �������
    // ��ĺϷ��߷��ǡ�L�Ρ��ƶ���һ��������2����һ��������1��
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) return false;
    int target = board[toY][toX];                                // ��ȡĿ��������
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);// �жϵ�ǰ�Ƿ�׷�����
    // ���Ŀ������Ǽ������ӣ���������ȥ
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // ����Ծʱ����Խ���������ӣ���˲��ж�·���Ƿ����赲
    return true; // �Ϸ� L �� + �Ǽ���Ŀ��񣬼����ƶ�
}
