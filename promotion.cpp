#include "promotion.h"
#include <graphics.h> // EasyX

// ����״̬��������
bool showPromotion = false;
int promotionX = -1;
int promotionY = -1;

void drawPromotionButtons(bool isWhiteTurn) {
    if (!showPromotion) return;

    const int BTN_X = 600;  // �Ҳఴť��ʼ X ����
    const int BTN_Y = 400;  // λ����λ��ť�·�
    const int BTN_SIZE = 64;
    const int BTN_GAP = 10;

    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;

    setbkcolor(BLACK); // ������ɫ
    settextcolor(WHITE); // �����ɫ
    setbkmode(TRANSPARENT);

    for (int i = 0; i < 4; ++i) {
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;

        // ���ư�ť�߿�
        setlinecolor(WHITE);
        rectangle(BTN_X, top, BTN_X + BTN_SIZE, bottom);

        // ������ͼ
        putimage(BTN_X, top, &pieceImages[options[i]]);
    }

    
    outtextxy(BTN_X, BTN_Y - 30, "����ѡ��");
}

bool handlePromotionClick(int mouseX, int mouseY, bool& isWhiteTurn) {
    if (!showPromotion) return false;

    const int BTN_X = 600;
    const int BTN_Y = 400;
    const int BTN_SIZE = 64;
    const int BTN_GAP = 10;

    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;

    for (int i = 0; i < 4; ++i) {
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;

        if (mouseX >= BTN_X && mouseX <= BTN_X + BTN_SIZE &&
            mouseY >= top && mouseY <= bottom) {
            // ִ�������滻
            board[promotionY][promotionX] = options[i];
            showPromotion = false;
            promotionX = promotionY = -1;

            // ������ɺ���
            isWhiteTurn = !isWhiteTurn;
            return true;
        }
    }

    return false;
}
