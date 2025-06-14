#include "promotion.h"
#include "board.h"
#include <graphics.h>

// 按钮区域坐标设置
const int BUTTON_X = 150;
const int BUTTON_Y = 200;
const int BUTTON_WIDTH = 70;
const int BUTTON_HEIGHT = 80;
const int BUTTON_GAP = 10;
bool checkAndHandlePromotion(int toX, int toY, bool isWhite);
// 升变选项：顺序为 皇后、车、象、马
int promoteOptions[4][2] = {
    { QUEEN_WHITE, QUEEN_BLACK },
    { ROOK_WHITE,  ROOK_BLACK  },
    { BISHOP_WHITE,BISHOP_BLACK},
    { KNIGHT_WHITE,KNIGHT_BLACK}
};

// 绘制单个按钮
void drawPromoteButton(int index, int pieceType, const char* label) {
    int x = BUTTON_X + index * (BUTTON_WIDTH + BUTTON_GAP);
    int y = BUTTON_Y;

    // 绘制按钮边框
    setlinecolor(WHITE);
    setfillcolor(RGB(80, 80, 80));
    fillrectangle(x, y, x + BUTTON_WIDTH, y + BUTTON_HEIGHT);

    // 绘制图片（棋子贴图居中）
    int imgX = x + (BUTTON_WIDTH - 64) / 2;
    int imgY = y + 5;
    putimage(imgX, imgY, &pieceImages[pieceType]);

    // 绘制文字标签
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(16, 0, "Consolas");
    outtextxy(x + 15, y + 65, label);
}

// 处理升变菜单逻辑
bool showPromotionMenu(int boardX, int boardY, bool isWhite) {
    const char* labels[4] = { "皇后", "战车", "主教", "骑士" };

    // 显示提示背景
    setfillcolor(BLACK);
    solidrectangle(0, 180, 640, 300); // 清除区域
    settextcolor(WHITE);
    outtextxy(200, 180, "请选择升变的棋子：");

    // 绘制四个按钮
    for (int i = 0; i < 4; ++i) {
        int pieceType = isWhite ? promoteOptions[i][0] : promoteOptions[i][1];
        drawPromoteButton(i, pieceType, labels[i]);
    }

    // 等待用户点击按钮
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
                        // 替换小兵为对应棋子
                        board[boardY][boardX] = isWhite ? promoteOptions[i][0] : promoteOptions[i][1];

                        // 清除提示区域
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

// 升变触发检测与处理入口
bool checkAndHandlePromotion(int toX, int toY, bool isWhite) {
    int piece = board[toY][toX];
    if ((isWhite && piece == PAWN_WHITE && toY == 0) ||
        (!isWhite && piece == PAWN_BLACK && toY == 7)) {
        return showPromotionMenu(toX, toY, isWhite);
    }
    return false;
}
