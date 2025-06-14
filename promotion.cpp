#include "promotion.h"
#include <graphics.h> // EasyX

// 升变状态变量定义
bool showPromotion = false;
int promotionX = -1;
int promotionY = -1;

void drawPromotionButtons(bool isWhiteTurn) {
    if (!showPromotion) return;

    const int BTN_X = 600;  // 右侧按钮起始 X 坐标
    const int BTN_Y = 400;  // 位于易位按钮下方
    const int BTN_SIZE = 64;
    const int BTN_GAP = 10;

    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;

    setbkcolor(BLACK); // 背景黑色
    settextcolor(WHITE); // 字体白色
    setbkmode(TRANSPARENT);

    for (int i = 0; i < 4; ++i) {
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;

        // 绘制按钮边框
        setlinecolor(WHITE);
        rectangle(BTN_X, top, BTN_X + BTN_SIZE, bottom);

        // 绘制贴图
        putimage(BTN_X, top, &pieceImages[options[i]]);
    }

    
    outtextxy(BTN_X, BTN_Y - 30, "升变选择");
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
            // 执行升变替换
            board[promotionY][promotionX] = options[i];
            showPromotion = false;
            promotionX = promotionY = -1;

            // 升变完成后换手
            isWhiteTurn = !isWhiteTurn;
            return true;
        }
    }

    return false;
}
