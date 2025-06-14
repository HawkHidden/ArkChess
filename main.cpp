#include <graphics.h>
#include <conio.h>
#include "board.h"
#include "move_logic.h"

const int CELL_SIZE = 64;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 50;

int main() {
    initgraph(800, 650); // �Դ󴰿ڱ��ڷ���ʾ����
    loadPieceImages();
    initBoard();

    bool whiteTurn = true;
    bool hasSelected = false;
    int selectedX = -1, selectedY = -1;
    char message[100] = "";

    while (true) {
        cleardevice();
        drawBoard();

        // ����ѡ�б߿�
        if (hasSelected) {
            setlinecolor(RED);
            setlinestyle(PS_SOLID, 3);
            rectangle(ORIGIN_X + selectedX * CELL_SIZE, ORIGIN_Y + selectedY * CELL_SIZE,
                ORIGIN_X + (selectedX + 1) * CELL_SIZE, ORIGIN_Y + (selectedY + 1) * CELL_SIZE);
        }

        // �����Ϣ����
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("Consolas"));
        outtextxy(50, 580, whiteTurn ? _T("��ǰ���׷�") : _T("��ǰ���ڷ�"));
        outtextxy(200, 580, _T(message));

        // ESC �˳�
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) break; // ESC
        }

        // ���������
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                int x = (m.x - ORIGIN_X) / CELL_SIZE;
                int y = (m.y - ORIGIN_Y) / CELL_SIZE;

                if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                    int clicked = board[y][x];
                    if (!hasSelected) {
                        // ���ε����ֻ��ѡ��ǰ��������
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
                        // ��ѡ�У��ٴε����������
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
                                strcpy_s(message, "���Ӳ��Ϲ棬����������");
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
