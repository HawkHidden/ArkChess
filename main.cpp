#include <graphics.h>
#include <conio.h>
#include "board.h"
#include "move_logic.h"

const int CELL_SIZE = 64;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 50;
const int SCREEN_WIDTH = ORIGIN_X * 2 + CELL_SIZE * 8;
const int SCREEN_HEIGHT = ORIGIN_Y * 2 + CELL_SIZE * 8 + 40; // ������ʾ����λ��

// ��ǰѡ�и������꣨δѡ��Ϊ -1��
int selectedX = -1, selectedY = -1;
int checkVictory(); // ���� 0 ������1 ��ʤ��2 ��ʤ
// ��ǰִ�巽 true = �ף�false = ��
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
    if (!blackKingAlive) return 1; // ��ʤ
    if (!whiteKingAlive) return 2; // ��ʤ
    return 0; // δ��ʤ��
}

// ��ʾ�ı���ʾ
void drawMessage(const char* msg) {
    setfillcolor(WHITE);
    solidrectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, SCREEN_HEIGHT);
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    outtextxy(ORIGIN_X, SCREEN_HEIGHT - 35, msg);
}

// ����ѡ�и������Ϸ��ƶ�λ����ʾ
void drawHighlights() {
    setlinecolor(RED);
    if (selectedX != -1 && selectedY != -1) {
        rectangle(ORIGIN_X + selectedX * CELL_SIZE, ORIGIN_Y + selectedY * CELL_SIZE,
            ORIGIN_X + (selectedX + 1) * CELL_SIZE, ORIGIN_Y + (selectedY + 1) * CELL_SIZE);

        // ��ʾ���кϷ��߷�λ�ñ߿���ɫ��
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
    char message[100] = "�׷�����";

    while (running) {
        BeginBatchDraw();
        drawBoard();
        drawHighlights();
        drawMessage(message);
        FlushBatchDraw();

        // �¼�����
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

                    // ��һ�ε����ѡ�м�������
                    if (selectedX == -1 && selectedY == -1) {
                        if ((isWhiteTurn && isWhitePiece) || (!isWhiteTurn && isBlackPiece)) {
                            selectedX = x;
                            selectedY = y;
                        }
                    }
                    // �ڶ��ε������������
                    else {
                        if (canMove(board, selectedX, selectedY, x, y)) {
                            board[y][x] = board[selectedY][selectedX];
                            board[selectedY][selectedX] = EMPTY;
                            selectedX = selectedY = -1;
                            isWhiteTurn = !isWhiteTurn;
                            int result = checkVictory();
                            if (result == 1) {
                                MessageBox(GetHWnd(), _T("�׷�ʤ����"), _T("��Ϸ����"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            else if (result == 2) {
                                MessageBox(GetHWnd(), _T("�ڷ�ʤ����"), _T("��Ϸ����"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            //ʤ���ж�
                            sprintf_s(message, "%s������", isWhiteTurn ? "��" : "��");
                        }
                        else {
                            sprintf_s(message, "���Ӳ��Ϲ棬����������");
                        }
                        selectedX = selectedY = -1; // ���ۺϷ����ȡ��ѡ��
                    }
                }
            }
        }
        Sleep(10); // �����ȴ�����ռ��CPU
    }

    releasePieceImages();
    closegraph();
    return 0;
}
