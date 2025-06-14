#include <graphics.h>
#include <conio.h>
#include "board.h"
#include "move_logic.h"

const int CELL_SIZE = 64;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 50;
const int SCREEN_WIDTH = ORIGIN_X * 2 + CELL_SIZE * 8+100;
const int SCREEN_HEIGHT = ORIGIN_Y * 2 + CELL_SIZE * 8 + 150; // 留出底下一行提示文字位置

// 当前选中格子坐标（未选中为 -1）
int selectedX = -1, selectedY = -1;
// 白方与黑方的王、两边车是否移动过
extern bool hasMovedWhiteKing=false, hasMovedWhiteRookLeft = false, hasMovedWhiteRookRight = false;
extern bool hasMovedBlackKing = false, hasMovedBlackRookLeft = false, hasMovedBlackRookRight = false;

int checkVictory(); // 返回 0 正常，1 白胜，2 黑胜
// 当前执棋方 true = 白，false = 黑
bool isWhiteTurn = true;
int checkVictory() {
    bool whiteKingAlive = false;
    bool blackKingAlive = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == KING_WHITE) whiteKingAlive = true;
            if (board[i][j] == KING_BLACK) blackKingAlive = true;
        }
    }
    if (!blackKingAlive) return 1; // 白胜
    if (!whiteKingAlive) return 2; // 黑胜
    return 0; // 未分胜负
}
// 显示文本提示
void drawMessage(const char* msg) {
    setfillcolor(WHITE);
    solidrectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, SCREEN_HEIGHT);
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    outtextxy(ORIGIN_X, SCREEN_HEIGHT - 35, msg);
}
// 绘制选中高亮、合法移动位置提示
void drawHighlights() {
    setlinecolor(RED);
    if (selectedX != -1 && selectedY != -1) {
        rectangle(ORIGIN_X + selectedX * CELL_SIZE, ORIGIN_Y + selectedY * CELL_SIZE,
            ORIGIN_X + (selectedX + 1) * CELL_SIZE, ORIGIN_Y + (selectedY + 1) * CELL_SIZE);

        // 显示所有合法走法位置边框（绿色）
        setlinecolor(GREEN);
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (canMove(board, selectedX, selectedY, x, y)) {
                    rectangle(ORIGIN_X + x * CELL_SIZE, ORIGIN_Y + y * CELL_SIZE,
                        ORIGIN_X + (x + 1) * CELL_SIZE, ORIGIN_Y + (y + 1) * CELL_SIZE);
                }
            }
        }
    }
}
void drawCastlingButtons(bool isWhiteTurn) {
    settextstyle(18, 0, _T("Consolas"));
    setbkmode(TRANSPARENT);
    setlinecolor(WHITE);
    settextcolor(WHITE);

    // 按钮位置
    int leftX = 600, topY = 100, width = 120, height = 40;

    // 短易位按钮
    rectangle(leftX, topY, leftX + width, topY + height);
    outtextxy(leftX + 10, topY + 10, isWhiteTurn ? _T("白方短易位") : _T("黑方短易位"));

    // 长易位按钮
    rectangle(leftX, topY + 60, leftX + width, topY + 60 + height);
    outtextxy(leftX + 10, topY + 70, isWhiteTurn ? _T("白方长易位") : _T("黑方长易位"));
}
// 输出“不能进行王车易位”提示的辅助函数
bool showCastlingInvalid() {
    setbkmode(OPAQUE);
    settextstyle(20, 0, _T("Consolas"));
    settextcolor(RED);
    outtextxy(50, 600, _T("不能进行王车易位，请检查是否已有棋子移动或路径被阻挡"));
    return false;
}
bool performCastling(bool isWhiteTurn, bool isKingside) {
    int row = isWhiteTurn ? 7 : 0;
    int king = isWhiteTurn ? KING_WHITE : KING_BLACK;
    int rook = isWhiteTurn ? ROOK_WHITE : ROOK_BLACK;

    // 判断是否移动过
    if (isWhiteTurn) {
        if (hasMovedWhiteKing) return showCastlingInvalid();
        if (isKingside && hasMovedWhiteRookRight) return showCastlingInvalid();
        if (!isKingside && hasMovedWhiteRookLeft) return showCastlingInvalid();
    }
    else {
        if (hasMovedBlackKing) return showCastlingInvalid();
        if (isKingside && hasMovedBlackRookRight) return showCastlingInvalid();
        if (!isKingside && hasMovedBlackRookLeft) return showCastlingInvalid();
    }

    // 判断路径是否为空
    if (isKingside) {
        if (board[row][5] != EMPTY || board[row][6] != EMPTY) return showCastlingInvalid();
    }
    else {
        if (board[row][1] != EMPTY || board[row][2] != EMPTY || board[row][3] != EMPTY)
            return showCastlingInvalid();
    }

    // 移动王与车
    if (isKingside) {
        board[row][4] = EMPTY;
        board[row][7] = EMPTY;
        board[row][6] = king;
        board[row][5] = rook;
    }
    else {
        board[row][4] = EMPTY;
        board[row][0] = EMPTY;
        board[row][2] = king;
        board[row][3] = rook;
    }

    // 设置标记
    if (isWhiteTurn) {
        hasMovedWhiteKing = true;
        if (isKingside) hasMovedWhiteRookRight = true;
        else hasMovedWhiteRookLeft = true;
    }
    else {
        hasMovedBlackKing = true;
        if (isKingside) hasMovedBlackRookRight = true;
        else hasMovedBlackRookLeft = true;
    }

    return true;
}
bool handleCastlingClick(int x, int y, bool isWhiteTurn) {
    int leftX = 600, topY = 100, width = 120, height = 40;

    // 是否点击了“短易位”按钮
    if (x >= leftX && x <= leftX + width && y >= topY && y <= topY + height) {
        return performCastling(isWhiteTurn, true);  // Kingside = true
    }

    // 是否点击了“长易位”按钮
    if (x >= leftX && x <= leftX + width && y >= topY + 60 && y <= topY + 60 + height) {
        return performCastling(isWhiteTurn, false); // Kingside = false
    }

    return false; // 未点击易位按钮
}
int main() {
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    initBoard();
    loadPieceImages();

    ExMessage msg;
    bool running = true;
    char message[100] = "白方走棋";

    while (running) {
        BeginBatchDraw();
        drawBoard();
        drawHighlights();
        drawMessage(message);
        FlushBatchDraw();
        // 每帧重绘棋盘与按钮
        drawBoard();
        drawCastlingButtons(isWhiteTurn);


        // 事件处理
        while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                running = false;
                break;
            }

            if (msg.message == WM_LBUTTONDOWN) {
                int x = (msg.x - ORIGIN_X) / CELL_SIZE;
                int y = (msg.y - ORIGIN_Y) / CELL_SIZE;
                // 优先判断是否点击了易位按钮
                if (handleCastlingClick(msg.x, msg.y, isWhiteTurn)) {
                    isWhiteTurn = !isWhiteTurn; // 成功易位后换手
                    selectedX = selectedY = -1; // 清除选中
                    continue; // 不进行普通走子处理
                }
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    int piece = board[y][x];
                    bool isWhitePiece = piece >= PAWN_WHITE && piece <= KING_WHITE;
                    bool isBlackPiece = piece >= PAWN_BLACK && piece <= KING_BLACK;

                    // 第一次点击，选中己方棋子
                    if (selectedX == -1 && selectedY == -1) {
                        if ((isWhiteTurn && isWhitePiece) || (!isWhiteTurn && isBlackPiece)) {
                            selectedX = x;
                            selectedY = y;
                        }
                    }
                    // 第二次点击，尝试走子
                    else {
                        if (canMove(board, selectedX, selectedY, x, y)) {
                            board[y][x] = board[selectedY][selectedX];
                            board[selectedY][selectedX] = EMPTY;
                            selectedX = selectedY = -1;
                            isWhiteTurn = !isWhiteTurn;
                            int result = checkVictory();
                            // 如果是王
                            if (piece == KING_WHITE)  hasMovedWhiteKing = true;
                            if (piece == KING_BLACK)  hasMovedBlackKing = true;

                            // 如果是车
                            if (piece == ROOK_WHITE) {
                                if (selectedX == 0 && selectedY == 7) hasMovedWhiteRookLeft = true;    // a1
                                if (selectedX == 7 && selectedY == 7) hasMovedWhiteRookRight = true;   // h1
                            }
                            if (piece == ROOK_BLACK) {
                                if (selectedX == 0 && selectedY == 0) hasMovedBlackRookLeft = true;    // a8
                                if (selectedX == 7 && selectedY == 0) hasMovedBlackRookRight = true;   // h8
                            }

                            if (result == 1) {
                                MessageBox(GetHWnd(), _T("白方胜利！"), _T("游戏结束"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            else if (result == 2) {
                                MessageBox(GetHWnd(), _T("黑方胜利！"), _T("游戏结束"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            sprintf_s(message, "%s方走棋", isWhiteTurn ? "白" : "黑");
                        }
                        else {
                            sprintf_s(message, "走子不合规，请重新走子");
                        }
                        selectedX = selectedY = -1; // 无论合法与否都取消选中
                    }
                }
            }
        }
        Sleep(10); // 稍作等待避免占满CPU
    }

    releasePieceImages();
    closegraph();
    return 0;
}
