#include "promotion.h"
#include "board.h"
#include <graphics.h>

// ��ť������������
const int BUTTON_X = 150;
const int BUTTON_Y = 200;
const int BUTTON_WIDTH = 70;
const int BUTTON_HEIGHT = 80;
const int BUTTON_GAP = 10;
bool checkAndHandlePromotion(int toX, int toY, bool isWhite);
// ����ѡ�˳��Ϊ �ʺ󡢳�������
int promoteOptions[4][2] = {
    { QUEEN_WHITE, QUEEN_BLACK },
    { ROOK_WHITE,  ROOK_BLACK  },
    { BISHOP_WHITE,BISHOP_BLACK},
    { KNIGHT_WHITE,KNIGHT_BLACK}
};

// ���Ƶ�����ť
void drawPromoteButton(int index, int pieceType, const char* label) {
    int x = BUTTON_X + index * (BUTTON_WIDTH + BUTTON_GAP);
    int y = BUTTON_Y;

    // ���ư�ť�߿�
    setlinecolor(WHITE);
    setfillcolor(RGB(80, 80, 80));
    fillrectangle(x, y, x + BUTTON_WIDTH, y + BUTTON_HEIGHT);

    // ����ͼƬ��������ͼ���У�
    int imgX = x + (BUTTON_WIDTH - 64) / 2;
    int imgY = y + 5;
    putimage(imgX, imgY, &pieceImages[pieceType]);

    // �������ֱ�ǩ
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(16, 0, "Consolas");
    outtextxy(x + 15, y + 65, label);
}

// ��������˵��߼�
bool showPromotionMenu(int boardX, int boardY, bool isWhite) {
    const char* labels[4] = { "�ʺ�", "ս��", "����", "��ʿ" };

    // ��ʾ��ʾ����
    setfillcolor(BLACK);
    solidrectangle(0, 180, 640, 300); // �������
    settextcolor(WHITE);
    outtextxy(200, 180, "��ѡ����������ӣ�");

    // �����ĸ���ť
    for (int i = 0; i < 4; ++i) {
        int pieceType = isWhite ? promoteOptions[i][0] : promoteOptions[i][1];
        drawPromoteButton(i, pieceType, labels[i]);
    }

    // �ȴ��û������ť
    while (true) {
        ExMessage msg;
        if (peekmessage(&msg, EX_MOUSE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                int mx = msg.x;
                int my = msg.y;

                for (int i = 0; i < 4; ++i) {
                    int bx = BUTTON_X + i * (BUTTON_WIDTH + BUTTON_GAP);
                    int by = BUTTON_Y;

                    if (mx >= bx && mx <= bx + BUTTON_WIDTH &&
                        my >= by && my <= by + BUTTON_HEIGHT) {
                        // �滻С��Ϊ��Ӧ����
                        board[boardY][boardX] = isWhite ? promoteOptions[i][0] : promoteOptions[i][1];

                        // �����ʾ����
                        setfillcolor(BLACK);
                        solidrectangle(0, 180, 640, 300);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// ���䴥������봦�����
bool checkAndHandlePromotion(int toX, int toY, bool isWhite) {
    int piece = board[toY][toX];
    if ((isWhite && piece == PAWN_WHITE && toY == 0) ||
        (!isWhite && piece == PAWN_BLACK && toY == 7)) {
        return showPromotionMenu(toX, toY, isWhite);
    }
    return false;
}
