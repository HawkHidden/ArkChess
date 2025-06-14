#include "move_logic.h"      // ���ļ�ͷ����ͳһ���ȸ��������߷�
#include "move_rook.h"       // ��
#include "move_bishop.h"     // ����
#include "move_knight.h"     // ����ʿ
#include "move_queen.h"      // ��
#include "move_king.h"       // ��
#include "move_pawn.h"       // ��
#include "board.h"           // ����������ö�ٳ�������
// ���ĺ������ж�ĳ�������Ƿ��ܴ� (fromX, fromY) �ƶ��� (toX, toY)
bool canMove(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];         // ��ȡ��ʼ���ϵ����ӱ��
    if (piece == EMPTY) return false;        // �ո��������ӣ������ƶ�
    int target = board[toY][toX];            // ��ȡĿ����ϵ����ӱ��
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE); // �ж��Ƿ�׷�����
    // ���Ŀ������Ǽ������ӣ������ƶ������ܳ��Լ��ˣ�
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // �����������ͣ����ö�Ӧ�ġ��߷��жϺ�����
    switch (piece) {
    case ROOK_WHITE: case ROOK_BLACK:
        return canMoveRook(board, fromX, fromY, toX, toY);       // ��
    case BISHOP_WHITE: case BISHOP_BLACK:
        return canMoveBishop(board, fromX, fromY, toX, toY);     // ��
    case KNIGHT_WHITE: case KNIGHT_BLACK:
        return canMoveKnight(board, fromX, fromY, toX, toY);     // ��
    case QUEEN_WHITE: case QUEEN_BLACK:
        return canMoveQueen(board, fromX, fromY, toX, toY);      // ��
    case KING_WHITE: case KING_BLACK:
        return canMoveKing(board, fromX, fromY, toX, toY);       // ��
    case PAWN_WHITE: case PAWN_BLACK:
        return canMovePawn(board, fromX, fromY, toX, toY);       // ��
    default:
        return false;                                            // �Ƿ����ӱ��
    }
}

