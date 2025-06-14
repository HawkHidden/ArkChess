#include <graphics.h>
#include <conio.h>
#include "board.h"
#include "move_logic.h"

const int CELL_SIZE = 64;
const int ORIGIN_X = 50;
const int ORIGIN_Y = 50;
const int SCREEN_WIDTH = ORIGIN_X * 2 + CELL_SIZE * 8+100;
const int SCREEN_HEIGHT = ORIGIN_Y * 2 + CELL_SIZE * 8 + 150; // ��������һ����ʾ����λ��

// ��ǰѡ�и������꣨δѡ��Ϊ -1��
int selectedX = -1, selectedY = -1;
// �׷���ڷ����������߳��Ƿ��ƶ���
extern bool hasMovedWhiteKing=false, hasMovedWhiteRookLeft = false, hasMovedWhiteRookRight = false;
extern bool hasMovedBlackKing = false, hasMovedBlackRookLeft = false, hasMovedBlackRookRight = false;

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
void drawCastlingButtons(bool isWhiteTurn) {
    settextstyle(18, 0, _T("Consolas"));
    setbkmode(TRANSPARENT);
    setlinecolor(WHITE);
    settextcolor(WHITE);

    // ��ťλ��
    int leftX = 600, topY = 100, width = 120, height = 40;

    // ����λ��ť
    rectangle(leftX, topY, leftX + width, topY + height);
    outtextxy(leftX + 10, topY + 10, isWhiteTurn ? _T("�׷�����λ") : _T("�ڷ�����λ"));

    // ����λ��ť
    rectangle(leftX, topY + 60, leftX + width, topY + 60 + height);
    outtextxy(leftX + 10, topY + 70, isWhiteTurn ? _T("�׷�����λ") : _T("�ڷ�����λ"));
}
// ��������ܽ���������λ����ʾ�ĸ�������
bool showCastlingInvalid() {
    setbkmode(OPAQUE);
    settextstyle(20, 0, _T("Consolas"));
    settextcolor(RED);
    outtextxy(50, 600, _T("���ܽ���������λ�������Ƿ����������ƶ���·�����赲"));
    return false;
}
bool performCastling(bool isWhiteTurn, bool isKingside) {
    int row = isWhiteTurn ? 7 : 0;
    int king = isWhiteTurn ? KING_WHITE : KING_BLACK;
    int rook = isWhiteTurn ? ROOK_WHITE : ROOK_BLACK;

    // �ж��Ƿ��ƶ���
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

    // �ж�·���Ƿ�Ϊ��
    if (isKingside) {
        if (board[row][5] != EMPTY || board[row][6] != EMPTY) return showCastlingInvalid();
    }
    else {
        if (board[row][1] != EMPTY || board[row][2] != EMPTY || board[row][3] != EMPTY)
            return showCastlingInvalid();
    }

    // �ƶ����복
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

    // ���ñ��
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

    // �Ƿ����ˡ�����λ����ť
    if (x >= leftX && x <= leftX + width && y >= topY && y <= topY + height) {
        return performCastling(isWhiteTurn, true);  // Kingside = true
    }

    // �Ƿ����ˡ�����λ����ť
    if (x >= leftX && x <= leftX + width && y >= topY + 60 && y <= topY + 60 + height) {
        return performCastling(isWhiteTurn, false); // Kingside = false
    }

    return false; // δ�����λ��ť
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
        // ÿ֡�ػ������밴ť
        drawBoard();
        drawCastlingButtons(isWhiteTurn);


        // �¼�����
        while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                running = false;
                break;
            }

            if (msg.message == WM_LBUTTONDOWN) {
                int x = (msg.x - ORIGIN_X) / CELL_SIZE;
                int y = (msg.y - ORIGIN_Y) / CELL_SIZE;
                // �����ж��Ƿ�������λ��ť
                if (handleCastlingClick(msg.x, msg.y, isWhiteTurn)) {
                    isWhiteTurn = !isWhiteTurn; // �ɹ���λ����
                    selectedX = selectedY = -1; // ���ѡ��
                    continue; // ��������ͨ���Ӵ���
                }
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
                            // �������
                            if (piece == KING_WHITE)  hasMovedWhiteKing = true;
                            if (piece == KING_BLACK)  hasMovedBlackKing = true;

                            // ����ǳ�
                            if (piece == ROOK_WHITE) {
                                if (selectedX == 0 && selectedY == 7) hasMovedWhiteRookLeft = true;    // a1
                                if (selectedX == 7 && selectedY == 7) hasMovedWhiteRookRight = true;   // h1
                            }
                            if (piece == ROOK_BLACK) {
                                if (selectedX == 0 && selectedY == 0) hasMovedBlackRookLeft = true;    // a8
                                if (selectedX == 7 && selectedY == 0) hasMovedBlackRookRight = true;   // h8
                            }

                            if (result == 1) {
                                MessageBox(GetHWnd(), _T("�׷�ʤ����"), _T("��Ϸ����"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            else if (result == 2) {
                                MessageBox(GetHWnd(), _T("�ڷ�ʤ����"), _T("��Ϸ����"), MB_OK | MB_ICONINFORMATION);
                                break;
                            }
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
