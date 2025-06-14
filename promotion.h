#include "board.h"
// 升变模块全局控制
extern bool showPromotion;  // 是否正在显示升变按钮
extern int promotionX;      // 升变目标格坐标 X
extern int promotionY;      // 升变目标格坐标 Y
// 白方升变选项（依次为后、车、象、马）
const int WHITE_PROMOTION_OPTIONS[4] = { QUEEN_WHITE, ROOK_WHITE, BISHOP_WHITE, KNIGHT_WHITE };
// 黑方升变选项
const int BLACK_PROMOTION_OPTIONS[4] = { QUEEN_BLACK, ROOK_BLACK, BISHOP_BLACK, KNIGHT_BLACK };
// 绘制升变按钮
void drawPromotionButtons(bool isWhiteTurn);
// 处理按钮点击
bool handlePromotionClick(int mouseX, int mouseY, bool& isWhiteTurn);
