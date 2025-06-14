#ifndef BOARD_H
#define BOARD_H
#include <graphics.h> // EasyXͼ�ο�ͷ�ļ�
#include <iostream>
using namespace std;
// ��������ö��
enum PieceType {
    EMPTY = 0,
    PAWN_WHITE, ROOK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, QUEEN_WHITE, KING_WHITE,
    PAWN_BLACK, ROOK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, QUEEN_BLACK, KING_BLACK
};

// ���̴�С����
const int BOARD_SIZE = 8;

// �������鶨��
// 0 ��ʾ�ո�����ֵ��Ӧö�ٵ���������
extern int board[BOARD_SIZE][BOARD_SIZE];

// ��ʼ�����̺��������ó�ʼ����λ��
void initBoard();

// �������������ӣ�����Ϊ��ͼ��أ���EasyX����
void drawBoard();
void releasePieceImages();
void loadPieceImages();

#endif
