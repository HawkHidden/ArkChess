#include <graphics.h>
#include <conio.h>
#include "board.h"
#include "move_logic.h"

const int CELL_SIZE = 64;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 50;
const int SCREEN_WIDTH = ORIGIN_X * 2 + CELL_SIZE * 8;
const int SCREEN_HEIGHT = ORIGIN_Y * 2 + CELL_SIZE * 8 + 40; // 留出提示文字位置

// 当前选中格子坐标（未选中为 -1）
int selectedX = -1, selectedY = -1;
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

        // 事件处理
        while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                running = false;
                break;
            }

            if (msg.message == WM_LBUTTONDOWN) {
                int x = (msg.x - ORIGIN_X) / CELL_SIZE;
                int y = (msg.y - ORIGIN_Y) / CELL_SIZE;

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
                            if (result == 1) {
                                MessageBox(GetHWnd(), _T("白方胜利！"), _T("游戏结束"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            else if (result == 2) {
                                MessageBox(GetHWnd(), _T("黑方胜利！"), _T("游戏结束"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            //胜负判定
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
