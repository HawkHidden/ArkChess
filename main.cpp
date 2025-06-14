#include <graphics.h>
#include <conio.h>
#include "board.h"
#include "move_logic.h"

const int CELL_SIZE = 64;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 50;

int main() {
    initgraph(800, 650); // 略大窗口便于放提示文字
    loadPieceImages();
    initBoard();

    bool whiteTurn = true;
    bool hasSelected = false;
    int selectedX = -1, selectedY = -1;
    char message[100] = "";

    while (true) {
        cleardevice();
        drawBoard();

        // 绘制选中边框
        if (hasSelected) {
            setlinecolor(RED);
            setlinestyle(PS_SOLID, 3);
            rectangle(ORIGIN_X + selectedX * CELL_SIZE, ORIGIN_Y + selectedY * CELL_SIZE,
                ORIGIN_X + (selectedX + 1) * CELL_SIZE, ORIGIN_Y + (selectedY + 1) * CELL_SIZE);
        }

        // 输出信息文字
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("Consolas"));
        outtextxy(50, 580, whiteTurn ? _T("当前：白方") : _T("当前：黑方"));
        outtextxy(200, 580, _T(message));

        // ESC 退出
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) break; // ESC
        }

        // 鼠标点击处理
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                int x = (m.x - ORIGIN_X) / CELL_SIZE;
                int y = (m.y - ORIGIN_Y) / CELL_SIZE;

                if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                    int clicked = board[y][x];
                    if (!hasSelected) {
                        // 初次点击：只能选当前方的棋子
                        if (clicked != EMPTY &&
                            ((whiteTurn && clicked >= PAWN_WHITE && clicked <= KING_WHITE) ||
                                (!whiteTurn && clicked >= PAWN_BLACK && clicked <= KING_BLACK))) {
                            selectedX = x;
                            selectedY = y;
                            hasSelected = true;
                            strcpy_s(message, "");
                        }
                    }
                    else {
                        // 已选中，再次点击尝试走子
                        if (x == selectedX && y == selectedY) {
                            hasSelected = false;
                        }
                        else {
                            if (canMove(board, selectedX, selectedY, x, y)) {
                                board[y][x] = board[selectedY][selectedX];
                                board[selectedY][selectedX] = EMPTY;
                                whiteTurn = !whiteTurn;
                                hasSelected = false;
                                strcpy_s(message, "");
                            }
                            else {
                                strcpy_s(message, "走子不合规，请重新走子");
                            }
                        }
                    }
                }
            }
        }

        FlushMouseMsgBuffer();
        Sleep(30);
    }

    releasePieceImages();
    closegraph();
    return 0;
}
