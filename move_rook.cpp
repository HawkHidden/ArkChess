#include "move_rook.h"   // ��������Rook�����߷��жϽӿ�
#include "board.h"       // ���������������������Ͷ���
#include <cmath>         // �ṩ��ѧ����
// �жϳ���Rook���Ƿ��ܴ� (fromX, fromY) �ƶ��� (toX, toY)
bool canMoveRook(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // �� �����յ㲻����ͬ����������Ϊ��
    if (fromX == toX && fromY == toY) return false;
    int piece = board[fromY][fromX];
    if (piece != ROOK_WHITE && piece != ROOK_BLACK) return false;
    // �� Ŀ����Ӳ����м�������
    int target = board[toY][toX];
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // �� ˮƽ�ƶ��߼���ͬһ�У�fromY == toY��
    if (fromY == toY) {
        // ȷ�����ҷ���Ĳ�����+1 ���ң�-1 ����
        int step = (toX > fromX) ? 1 : -1;
        // ���������յ�֮���ÿ�����ӣ����붼�ǿյ�
        for (int x = fromX + step; x != toX; x += step) {
            if (board[fromY][x] != EMPTY) return false;
        }
        return true;  // ·����գ�ˮƽ�ƶ��Ϲ�
    }
    // �� ��ֱ�ƶ��߼���ͬһ�У�fromX == toX��
    if (fromX == toX) {
        // ȷ�����·���Ĳ�����+1 ���£�-1 ���ϣ�
        int step = (toY > fromY) ? 1 : -1;
        // ���������յ�֮���ÿ�����ӣ����붼�ǿյ�
        for (int y = fromY + step; y != toY; y += step) {
            if (board[y][fromX] != EMPTY) return false;
        }
        return true;  // ·����գ���ֱ�ƶ��Ϸ�
    }
    // �� �Ȳ�ͬ��Ҳ��ͬ�У��ȷ�ˮƽҲ�Ǵ�ֱ���Ƿ��߷�
    return false;
}
