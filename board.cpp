#include "board.h"
#include <graphics.h> // EasyX

// �������鶨��
int board[BOARD_SIZE][BOARD_SIZE];// A���޸�

// ��ʼ�����̺���ʵ��
void initBoard() {
    // ������̣�ȫ����Ϊ EMPTY
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    // �ױ���ʼ��
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[6][j] = PAWN_WHITE;
    }
    // �ڱ���ʼ��
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[1][j] = PAWN_BLACK;
    }
    // ����׷���������
    board[7][0] = ROOK_WHITE;
    board[7][1] = KNIGHT_WHITE;
    board[7][2] = BISHOP_WHITE;
    board[7][3] = QUEEN_WHITE;
    board[7][4] = KING_WHITE;
    board[7][5] = BISHOP_WHITE;
    board[7][6] = KNIGHT_WHITE;
    board[7][7] = ROOK_WHITE;

    // ����ڷ���������
    board[0][0] = ROOK_BLACK;
    board[0][1] = KNIGHT_BLACK;
    board[0][2] = BISHOP_BLACK;
    board[0][3] = QUEEN_BLACK;
    board[0][4] = KING_BLACK;
    board[0][5] = BISHOP_BLACK;
    board[0][6] = KNIGHT_BLACK;
    board[0][7] = ROOK_BLACK;
}

// ������ͼ�б�
IMAGE pieceImages[13]; // �±��� PieceType ��Ӧ

// ����������ͼ���ļ���ͳһ��ʽ�� "queen_white.bmp"
void loadPieceImages() {
    const char* filenames[13] = {
        "empty.bmp", // ��ͼ�������
        "pawn_white.bmp",
        "rook_white.bmp",
        "knight_white.bmp",
        "bishop_white.bmp",
        "queen_white.bmp",
        "king_white.bmp",
        "pawn_black.bmp",
        "rook_black.bmp",
        "knight_black.bmp",
        "bishop_black.bmp",
        "queen_black.bmp",
        "king_black.bmp"
    };
    for (int i = 0; i < 13; i++) {
        loadimage(&pieceImages[i], filenames[i]);
    }
}

// �ͷ���ͼ��Դ
void releasePieceImages() {
    for (int i = 0; i < 13; i++) {
        // EasyX ������ʽ�ͷ� IMAGE����ʵ�������ӿ���չ
    }
}

// �������̺�����
void drawBoard() {
    // ���̸�ߴ�
    const int CELL_SIZE = 64;
    // �������Ͻ��������
    const int ORIGIN_X = 50;
    const int ORIGIN_Y = 50;

    // �����ӣ��ڰ����
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int left = ORIGIN_X + j * CELL_SIZE;
            int top = ORIGIN_Y + i * CELL_SIZE;
            int right = left + CELL_SIZE;
            int bottom = top + CELL_SIZE;

            // �ڰ׸�����ɫ����
            if ((i + j) % 2 == 0) {
                setfillcolor(RGB(240, 217, 181)); // ǳɫ
            }
            else {
                setfillcolor(RGB(181, 136, 99)); // ��ɫ
            }
            fillrectangle(left, top, right, bottom);

            // ������ͼƬ
            int piece = board[i][j];
            if (piece != EMPTY) {
                // ��ͼ���ƾ���
                putimage(left, top, &pieceImages[piece]);
            }
        }
    }
}
