#include <graphics.h>        // EasyX 图形库：提供图形窗口、绘图函数等
#include <conio.h>           // 控制台输入输出（getch 等）；此处可用于暂停或调试
#include "board.h"           // 棋盘模块：定义 board 数组、棋子类型（PieceType）、初始化和绘制函数
#include "move_logic.h"      // 走法逻辑：声明 canMove 等核心判断
#include "promotion.h"       // 升变模块：声明 showPromotion、drawPromotionButtons、handlePromotionClick
#include <mmsystem.h>        // Windows 多媒体 API：用于 PlaySound 播放音效
#pragma comment(lib, "winmm.lib") // 链接 winmm 库，使 PlaySound 生效
// 常量与全局变量
const int CELL_SIZE = 64;                                // 每个棋格的像素边长
const int ORIGIN_X = 50;                                // 棋盘左上角 X 坐标
const int ORIGIN_Y = 50;                                // 棋盘左上角 Y 坐标
const int SCREEN_WIDTH = ORIGIN_X * 2 + CELL_SIZE * 8 + 200; // 窗口宽度：左右边距 + 8 列棋格 + 右侧按钮区
const int SCREEN_HEIGHT = ORIGIN_Y * 2 + CELL_SIZE * 8 + 250; // 窗口高度：上下边距 + 8 行棋格 + 下方提示区
// 当前选中格子坐标。-1 表示未选中任何格子
int selectedX = -1, selectedY = -1;
// 外部声明：王车是否移动过（影响易位合法性）
// extern 表示变量定义在别处（promotion.cpp 或 main.cpp 顶部）
extern bool hasMovedWhiteKing = false, hasMovedWhiteRookLeft = false, hasMovedWhiteRookRight = false;
extern bool hasMovedBlackKing = false, hasMovedBlackRookLeft = false, hasMovedBlackRookRight = false;
// 函数声明：检查胜负状态，返回 0=继续，1=白胜，2=黑胜
int checkVictory();
// 全局标志：当前执棋方，true=白方，false=黑方
bool isWhiteTurn = true;
// 函数：checkVictory
// 作用：扫描整个 board，看哪方的王还在
// 返回：1 表示白方胜（黑王被吃），2 表示黑方胜（白王被吃），0 表示对局继续
int checkVictory() {
    bool whiteKingAlive = false;
    bool blackKingAlive = false;
    // 遍历 8×8 棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == KING_WHITE) whiteKingAlive = true; // 找到白王
            if (board[i][j] == KING_BLACK) blackKingAlive = true; // 找到黑王
        }
    }
    if (!blackKingAlive) return 1; // 黑王消失 → 白胜
    if (!whiteKingAlive) return 2; // 白王消失 → 黑胜
    return 0;                      // 双王都在 → 对局继续
}
// 函数：drawMessage
// 作用：在窗口底部绘制一行提示文字
// 参数：msg 为要显示的 C 字符串（const char*）
void drawMessage(const char* msg) {
    setfillcolor(WHITE);    // 背景填充色白
    solidrectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, SCREEN_HEIGHT); // 清空提示区
    settextcolor(RED);      // 文本颜色红
    setbkmode(TRANSPARENT); // 文本背景透明
    outtextxy(ORIGIN_X, SCREEN_HEIGHT - 35, msg); // 在指定位置绘制文本
}
// 函数：drawHighlights
// 作用：绘制“选中格子”和“所有合法移动位置”的高亮
void drawHighlights() {
    setlinecolor(RED); // 红色用来高亮当前选中格子
    if (selectedX != -1 && selectedY != -1) {
        // 画红色边框，标示已选中的棋子格
        rectangle(
            ORIGIN_X + selectedX * CELL_SIZE,
            ORIGIN_Y + selectedY * CELL_SIZE,
            ORIGIN_X + (selectedX + 1) * CELL_SIZE,
            ORIGIN_Y + (selectedY + 1) * CELL_SIZE
        );
        // 画绿色边框，标示该棋子所有合法落点
        setlinecolor(GREEN);
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                // 调用核心判断函数 canMove，检测 (selectedX,selectedY) → (x,y) 是否合法
                if (canMove(board, selectedX, selectedY, x, y)) {
                    rectangle(
                        ORIGIN_X + x * CELL_SIZE,
                        ORIGIN_Y + y * CELL_SIZE,
                        ORIGIN_X + (x + 1) * CELL_SIZE,
                        ORIGIN_Y + (y + 1) * CELL_SIZE
                    );
                }
            }
        }
    }
}
// ============================
// 函数：drawCastlingButtons
// 作用：在界面右侧绘制“短易位”和“长易位”两个按钮
// 参数：isWhiteTurn 指示当前轮到白方还是黑方走棋
// ============================
void drawCastlingButtons(bool isWhiteTurn) {
    settextstyle(18, 0, _T("Consolas"));  // 设置字体：字号18，无旋转，Consolas字体随便选的
    setbkmode(TRANSPARENT);               // 文本背景模式：透明（不覆盖背景格子）
    setlinecolor(WHITE);                  // 线条颜色：白色
    settextcolor(WHITE);                  // 文本颜色：白色
    // 按钮位置和大小参数
    int leftX = 600, topY = 100, width = 120, height = 40;
    // 绘制“短易位”按钮
    rectangle(leftX, topY, leftX + width, topY + height); // 画按钮边框
    // outtextxy：在按钮内部留 10 像素边距后绘制文字，三目运算决定显示文字
    outtextxy(leftX + 10, topY + 10,
        isWhiteTurn ? _T("白方短易位") : _T("黑方短易位"));
    // 绘制“长易位”按钮，Y 坐标下移60像素
    rectangle(leftX, topY + 60, leftX + width, topY + 60 + height);
    outtextxy(leftX + 10, topY + 70,
        isWhiteTurn ? _T("白方长易位") : _T("黑方长易位"));
}
// 函数：showCastlingInvalid
// 作用：当易位条件不满足时，输出红色错误提示
// 返回：false，以便调用者统一返回 false 表示易位失败
bool showCastlingInvalid() {
    setbkmode(OPAQUE);                   // 文本背景模式：不透明（覆盖之前内容）
    settextstyle(20, 0, _T("Consolas")); // 设置字体：字号20
    settextcolor(RED);                   // 文本颜色：红色，强调错误
    // 在坐标 (50,600) 处输出提示文字
    outtextxy(50, 600, _T("不能进行王车易位，请检查是否已有棋子移动或路径被阻挡"));
    return false;                        // 返回 false，使 performCastling 也返回 false
}
// 函数：performCastling
// 作用：执行王车易位操作（含合法性检查）
// 参数：isWhiteTurn  — 当前是否白方走棋
//       isKingside    — true=短易位（王向王侧移动），false=长易位（王向后侧移动）
// 返回：true=易位成功；false=易位不合法
bool performCastling(bool isWhiteTurn, bool isKingside) {
    // 确定易位所在行：白方第7行，黑方第0行
    int row = isWhiteTurn ? 7 : 0;
    // 确定要移动的国王和车的枚举值
    int king = isWhiteTurn ? KING_WHITE : KING_BLACK;
    int rook = isWhiteTurn ? ROOK_WHITE : ROOK_BLACK;
    // 1. 判断王和对应车是否已经移动过（若已移动，不能易位）
    if (isWhiteTurn) {
        if (hasMovedWhiteKing)       return showCastlingInvalid();
        if (isKingside && hasMovedWhiteRookRight) return showCastlingInvalid();
        if (!isKingside && hasMovedWhiteRookLeft) return showCastlingInvalid();
    }
    else {
        if (hasMovedBlackKing)       return showCastlingInvalid();
        if (isKingside && hasMovedBlackRookRight) return showCastlingInvalid();
        if (!isKingside && hasMovedBlackRookLeft) return showCastlingInvalid();
    }
    // 2. 判断路径是否为空（短易位要检查 king->rook 之间两格，长易位检查三格）
    if (isKingside) {
        // 短易位检查列5和6
        if (board[row][5] != EMPTY || board[row][6] != EMPTY)
            return showCastlingInvalid();
    }
    else {
        // 长易位检查列1、2、3
        if (board[row][1] != EMPTY || board[row][2] != EMPTY || board[row][3] != EMPTY)
            return showCastlingInvalid();
    }
    // 3. 执行实际移动：先将原王和原车位置设为空，再把它们放到新位置
    if (isKingside) {
        board[row][4] = EMPTY;     // 原王位置清空
        board[row][7] = EMPTY;     // 原车位置清空
        board[row][6] = king;      // 王移动至列6
        board[row][5] = rook;      // 车移动至列5
    }
    else {
        board[row][4] = EMPTY;     // 原王位置清空
        board[row][0] = EMPTY;     // 原车位置清空
        board[row][2] = king;      // 王移动至列2
        board[row][3] = rook;      // 车移动至列3
    }
    // 4. 更新标志位，记录王和车都已移动过，防止后续重复易位
    if (isWhiteTurn) {
        hasMovedWhiteKing = true;
        if (isKingside) hasMovedWhiteRookRight = true;
        else            hasMovedWhiteRookLeft = true;
    }
    else {
        hasMovedBlackKing = true;
        if (isKingside) hasMovedBlackRookRight = true;
        else            hasMovedBlackRookLeft = true;
    }
    return true; // 易位成功
}
// 函数：handleCastlingClick
// 作用：检测鼠标点击坐标是否落在易位按钮上，并触发 performCastling
// 参数：x,y 为鼠标像素坐标；isWhiteTurn 当前执棋方
// 返回：true=已点击并执行易位；false=未点击易位按钮或易位失败
bool handleCastlingClick(int x, int y, bool isWhiteTurn) {
    // 与 drawCastlingButtons 使用相同的参数
    int leftX = 600, topY = 100, width = 120, height = 40;
    // 检测“短易位”按钮点击区域
    if (x >= leftX && x <= leftX + width &&
        y >= topY && y <= topY + height) {
        return performCastling(isWhiteTurn, true);  // Kingside = true
    }
    // 检测“长易位”按钮点击区域（Y 坐标下移60）
    if (x >= leftX && x <= leftX + width &&
        y >= topY + 60 && y <= topY + 60 + height) {
        return performCastling(isWhiteTurn, false); // Kingside = false
    }
    return false; // 未点击任何易位按钮
}
int main() {
    // 初始化图形窗口，宽 SCREEN_WIDTH，高 SCREEN_HEIGHT
    // initgraph 是 EasyX 提供的函数，用于创建画布并打开窗口
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    // 初始化棋盘数据（board 数组）到初始布局
    initBoard();
    // 加载所有棋子贴图到 pieceImages 数组
    loadPieceImages();
    ExMessage msg;           // EasyX 的消息结构，保存鼠标/键盘事件
    bool running = true;     // 程序主循环标志，false 时退出
    char message[100] = "白方走棋"; // 底部提示行，初始提示白方先走
    // 程序主循环，直到 running 变为 false
    while (running) {
        BeginBatchDraw();         // 开始批量绘制，减少闪烁
        drawBoard();              // 绘制棋盘格子和棋子
        drawHighlights();         // 绘制选中格子和可走位置高亮
        drawMessage(message);     // 绘制提示文字
        drawCastlingButtons(isWhiteTurn);  // 绘制王车易位按钮
        drawPromotionButtons(isWhiteTurn); // 绘制升变选择按钮（如在升变状态）
        FlushBatchDraw();         // 结束批量绘制并显示到窗口
        // 处理所有挂起的鼠标或键盘消息
        while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
            // 按下 Esc 键退出程序
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                running = false;
                break;
            }
            // 处理鼠标左键点击事件
            if (msg.message == WM_LBUTTONDOWN) {
                // 计算点击位置对应的棋盘格坐标
                int x = (msg.x - ORIGIN_X) / CELL_SIZE;
                int y = (msg.y - ORIGIN_Y) / CELL_SIZE;
                // 1. 优先处理王车易位按钮点击
                //    handleCastlingClick: 如果点击在按钮上并完成易位，返回 true
                if (handleCastlingClick(msg.x, msg.y, isWhiteTurn)) {
                    // 播放易位音效，PlaySound 来自 mmsystem.h
                    PlaySound(_T("crimson.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    isWhiteTurn = !isWhiteTurn;      // 成功易位后换手
                    selectedX = selectedY = -1;      // 清除选中状态
                    continue;                        // 跳过普通走子逻辑
                }
                // 2. 升变按钮点击优先处理
                //    handlePromotionClick: 如果在升变按钮区域点击并完成升变，返回 true
                if (handlePromotionClick(msg.x, msg.y, isWhiteTurn)) {
                    selectedX = selectedY = -1;      // 清除选中，等待新一轮走子
                    continue;                        // 跳过普通走子逻辑
                }
                // 3. 如果点击在棋盘范围内，则进行走子或选子逻辑
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    int piece = board[y][x]; // 获取被点击格子的棋子类型
                    // 判断是否是当前执棋方的棋子
                    bool isWhitePiece = piece >= PAWN_WHITE && piece <= KING_WHITE;
                    bool isBlackPiece = piece >= PAWN_BLACK && piece <= KING_BLACK;
                    // 第一次点击：选中符合条件的己方棋子
                    if (selectedX == -1 && selectedY == -1) {
                        if ((isWhiteTurn && isWhitePiece) || (!isWhiteTurn && isBlackPiece)) {
                            selectedX = x;
                            selectedY = y;
                        }
                    }
                    // 第二次点击：尝试将选中棋子移动到该格
                    else {
                        // 调用核心函数 canMove 判断走法是否合法
                        if (canMove(board, selectedX, selectedY, x, y)) {
                            // 执行移动：将选中格棋子复制到目标格，再清空原格
                            board[y][x] = board[selectedY][selectedX];
                            board[selectedY][selectedX] = EMPTY;
                            int fromX = selectedX, fromY = selectedY; // 保存起点
                            selectedX = selectedY = -1;               // 重置选中
                            // 播放落子音效
                            PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            // 获取刚移动的棋子类型
                            int movedPiece = board[y][x];
                            // 升变检测：如果走到对方底线且为兵，触发升变
                            if ((movedPiece == PAWN_WHITE && y == 0) ||
                                (movedPiece == PAWN_BLACK && y == 7)) {
                                showPromotion = true;  // 进入升变状态
                                promotionX = x;        // 记录升变位置
                                promotionY = y;
                                continue;              // 暂停换手，等待升变
                            }
                            // 切换执棋方
                            isWhiteTurn = !isWhiteTurn;
                            // 检查胜负：1=白胜，2=黑胜，0=继续
                            int result = checkVictory();
                            // 标记王或车是否移动过（影响易位合法性）
                            if (movedPiece == KING_WHITE)  hasMovedWhiteKing = true;
                            if (movedPiece == KING_BLACK)  hasMovedBlackKing = true;
                            if (movedPiece == ROOK_WHITE) {
                                if (fromX == 0 && fromY == 7) hasMovedWhiteRookLeft = true;
                                if (fromX == 7 && fromY == 7) hasMovedWhiteRookRight = true;
                            }
                            if (movedPiece == ROOK_BLACK) {
                                if (fromX == 0 && fromY == 0) hasMovedBlackRookLeft = true;
                                if (fromX == 7 && fromY == 0) hasMovedBlackRookRight = true;
                            }
                            // 胜负确认
                            if (result == 1) {
                                // 播放胜利音效
                                PlaySound(_T("manout.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                // MessageBox 来自 Windows API，弹出对话框
                                MessageBox(GetHWnd(), _T("白方胜利！"), _T("游戏结束"),
                                    MB_OK | MB_ICONINFORMATION);
                                break; // 退出消息处理，结束游戏
                            }
                            else if (result == 2) {
                                PlaySound(_T("manout.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                MessageBox(GetHWnd(), _T("黑方胜利！"), _T("游戏结束"),
                                    MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            // 更新底部提示，显示哪方继续走
                            sprintf_s(message, "%s方走棋", isWhiteTurn ? "白" : "黑");
                        }
                        else {
                            // 非法走子，提示用户重新选择
                            sprintf_s(message, "走子不合规，请重新走子");
                        }
                        // 无论是否合法，都重置选中
                        selectedX = selectedY = -1;
                    }
                }
            }
        }
        // 每帧循环后暂停10毫秒，可以有效减少卡顿
        Sleep(10);
    }
    // 退出主循环后，释放资源并关闭图形窗口
    releasePieceImages(); // 释放贴图（实际无需手动释放）
    closegraph();         // 关闭 EasyX 窗口
    return 0;             // 返回0，表示程序正常结束
}

