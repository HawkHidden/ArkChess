#include "promotion.h"       // 升变模块头文件，声明变量与函数接口
#include <graphics.h>        // 引入 EasyX 图形库，用于绘制按钮和贴图
// 升变模块全局变量
// showPromotion: 标志当前是否处于升变选择状态
//   true  -> 显示升变按钮，等待玩家点击
//   false -> 正常游戏，不显示升变按钮
bool showPromotion = false;
// promotionX, promotionY: 记录需要升变的兵所在棋盘坐标
//   当兵走到终点行时，设置这两个变量以便点击按钮时替换正确位置
int promotionX = -1;
int promotionY = -1;
// 函数：drawPromotionButtons
// 作用：在右侧垂直绘制 4 个升变选项按钮
// 参数：isWhiteTurn 表示当前升变方是白方还是黑方
void drawPromotionButtons(bool isWhiteTurn) {
    if (!showPromotion) return;  // 若不在升变状态，直接返回不绘制
    // 按钮起始坐标和尺寸
    const int BTN_X = 600;     // 按钮左侧 X 坐标
    const int BTN_Y = 400;     // 第一个按钮顶部 Y 坐标（位于易位按钮下方）
    const int BTN_SIZE = 64;      // 按钮正方形边长（与棋子贴图尺寸一致）
    const int BTN_GAP = 10;      // 按钮之间的垂直间距
    // 根据轮到哪方，选择对应的升变棋子数组指针
    // WHITE_PROMOTION_OPTIONS 和 BLACK_PROMOTION_OPTIONS 在 promotion.h 中定义
    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;
    // 设置绘图属性
    setbkcolor(BLACK);             // 背景色为黑（按钮下方填充区）
    settextcolor(WHITE);           // 文字颜色为白
    setbkmode(TRANSPARENT);        // 文本背景透明
    // 循环绘制 4 个按钮
    for (int i = 0; i < 4; ++i) {
        // 计算第 i 个按钮的顶部和底部 Y 坐标
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;
        // ① 绘制按钮边框
        setlinecolor(WHITE);                                       // 边框线为白色
        rectangle(BTN_X, top, BTN_X + BTN_SIZE, bottom);           // 绘制矩形边框
        // ② 在按钮框内绘制对应棋子贴图（居左上对齐刚好填满64×64）
        // options[i] 是枚举值，对应 pieceImages 数组下标
        putimage(BTN_X, top, &pieceImages[options[i]]);
    }
    // 绘制一个文字提示“升变选择”，位于按钮组上方
    outtextxy(BTN_X, BTN_Y - 30, "升变选择");
}
// 函数：handlePromotionClick
// 作用：检测鼠标点击是否在某一升变按钮上，若是则执行升变
// 参数：mouseX, mouseY 为鼠标点击的像素坐标
//       isWhiteTurn 引用参数，升变完成后要切换走棋方
// 返回：是否处理了升变（true 表示点击在有效按钮并已执行）
bool handlePromotionClick(int mouseX, int mouseY, bool& isWhiteTurn) {
    if (!showPromotion) return false;  // 若不在升变状态，忽略点击
    // 与 drawPromotionButtons 中相同的按钮位置与尺寸常量
    const int BTN_X = 600;
    const int BTN_Y = 400;
    const int BTN_SIZE = 64;
    const int BTN_GAP = 10;
    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;
    // 遍历 4 个按钮，检测鼠标坐标是否落在某个按钮区域
    for (int i = 0; i < 4; ++i) {
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;
        // 若鼠标 X 在按钮左右边界之间，且 Y 在按钮上下边界之间
        if (mouseX >= BTN_X && mouseX <= BTN_X + BTN_SIZE &&
            mouseY >= top && mouseY <= bottom) {
            // 选中第 i 个升变选项：
            // options[i] 是要替换的枚举值（如 QUEEN_WHITE）
            board[promotionY][promotionX] = options[i];
            // 关闭升变状态，重置坐标
            showPromotion = false;
            promotionX = -1;
            promotionY = -1;
            // 播放升变成功的提示音效
            PlaySound(TEXT("promotion.wav"), NULL, SND_FILENAME | SND_ASYNC);
            // 升变完成后，切换走棋方（兵升变仍算本回合行动的一部分，现在交给对方）
            isWhiteTurn = !isWhiteTurn;
            return true; // 表示本次点击已被处理
        }
    }
    return false; // 点击不在任何升变按钮上
}
