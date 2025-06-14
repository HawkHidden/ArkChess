#include "board.h"           // ��������ͷ�ļ����������������������غ�������
#include <graphics.h>        // ���� EasyX ͼ�ο⣬����ͼ�λ���
// ģ��һ���������ݽṹ
// �����������飬���浱ǰ����ÿ�����ӵ���������
// board[i][j] ��ʾ�� i �� j ���ϵ�����
// ÿ�����ӵ�ֵ��һ��ö�����ͣ�PieceType�������� PAWN_WHITE��KING_BLACK ��
int board[BOARD_SIZE][BOARD_SIZE]; // A���޸�
// ģ��������̳�ʼ������
// ��ʼ�����̺��������ó�ʼ���֣������ڰױ�����������
void initBoard() {
    // ��һ�����Ƚ�����������գ���ÿ�����Ӷ���Ϊ EMPTY
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    // �ڶ��������ðױ��ڵ�6�У������±�Ϊ6��
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[6][j] = PAWN_WHITE;
    }
    // �����������úڱ��ڵ�1�У������±�Ϊ1��
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[1][j] = PAWN_BLACK;
    }
    // ���Ĳ������ð׷��������ӣ���7�У�
    board[7][0] = ROOK_WHITE;
    board[7][1] = KNIGHT_WHITE;
    board[7][2] = BISHOP_WHITE;
    board[7][3] = QUEEN_WHITE;
    board[7][4] = KING_WHITE;
    board[7][5] = BISHOP_WHITE;
    board[7][6] = KNIGHT_WHITE;
    board[7][7] = ROOK_WHITE;
    // ���岽�����úڷ��������ӣ���0�У�
    board[0][0] = ROOK_BLACK;
    board[0][1] = KNIGHT_BLACK;
    board[0][2] = BISHOP_BLACK;
    board[0][3] = QUEEN_BLACK;
    board[0][4] = KING_BLACK;
    board[0][5] = BISHOP_BLACK;
    board[0][6] = KNIGHT_BLACK;
    board[0][7] = ROOK_BLACK;
}
// ģ����������ͼƬ���ع���
// ����������ͼ��Դ����
// ÿ���±��Ӧһ���������ͣ��� 1=PAWN_WHITE��12=KING_BLACK
IMAGE pieceImages[13]; // ��13�֣������ո��� + 6������ �� 2����ɫ
// ����������ͼ�����ص��� BMP ͼƬ�ļ������±�һһ��Ӧ
void loadPieceImages() {
    const char* filenames[13] = {
        "empty.bmp",        // �±�0����Ӧ EMPTY
        "pawn_white.bmp",   // �±�1
        "rook_white.bmp",
        "knight_white.bmp",
        "bishop_white.bmp",
        "queen_white.bmp",
        "king_white.bmp",   // �±�6
        "pawn_black.bmp",   // �±�7
        "rook_black.bmp",
        "knight_black.bmp",
        "bishop_black.bmp",
        "queen_black.bmp",
        "king_black.bmp"    // �±�12
    };
    for (int i = 0; i < 13; i++) {
        loadimage(&pieceImages[i], filenames[i]);  // EasyX ����������ָ�� BMP ͼƬ��ͼ�������
    }
}
// ģ���ģ���Դ�ͷţ���ѡ��
// �ͷ���ͼ��Դ������Ŀǰδ����ʵ��
void releasePieceImages() {   
		//û�����幦�ܣ����Բ���Ҫ�ͷ���ͼ��Դ    
}
// ģ���壺��������������
// �������̱����뵱ǰ���ӷֲ�
void drawBoard() {
    const int CELL_SIZE = 64;         // ÿ�����̸��ӵı߳�����λ�����أ�
    const int ORIGIN_X = 50;          // �������Ͻǵ� X ����
    const int ORIGIN_Y = 50;          // �������Ͻǵ� Y ����
    // ������������ 8x8��ÿ�����Ӷ����Ʊ���������
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // ���㵱ǰ���ӵ����Ͻ������½�����
            int left = ORIGIN_X + j * CELL_SIZE;
            int top = ORIGIN_Y + i * CELL_SIZE;
            int right = left + CELL_SIZE;
            int bottom = top + CELL_SIZE;
            // �����趨������ɫ��ʵ�ֹ�������ڰ׸�
            if ((i + j) % 2 == 0) {
                setfillcolor(RGB(240, 217, 181)); // ǳɫ����
            }
            else {
                setfillcolor(RGB(181, 136, 99));  // ��ɫ����
            }
            fillrectangle(left, top, right, bottom); // ���ƾ��α���
            // ��ȡ�ø��ӵ����ӱ��
            int piece = board[i][j];
            if (piece != EMPTY) {
                // ������ǿո��ӣ����ƶ�Ӧ��������ͼ
                // putimage ��ͼƬ����ָ������
                putimage(left, top, &pieceImages[piece]);
            }
        }
    }
}




