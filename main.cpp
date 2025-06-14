#include <graphics.h>        // EasyX ͼ�ο⣺�ṩͼ�δ��ڡ���ͼ������
#include <conio.h>           // ����̨���������getch �ȣ����˴���������ͣ�����
#include "board.h"           // ����ģ�飺���� board ���顢�������ͣ�PieceType������ʼ���ͻ��ƺ���
#include "move_logic.h"      // �߷��߼������� canMove �Ⱥ����ж�
#include "promotion.h"       // ����ģ�飺���� showPromotion��drawPromotionButtons��handlePromotionClick
#include <mmsystem.h>        // Windows ��ý�� API������ PlaySound ������Ч
#pragma comment(lib, "winmm.lib") // ���� winmm �⣬ʹ PlaySound ��Ч
// ������ȫ�ֱ���
const int CELL_SIZE = 64;                                // ÿ���������ر߳�
const int ORIGIN_X = 50;                                // �������Ͻ� X ����
const int ORIGIN_Y = 50;                                // �������Ͻ� Y ����
const int SCREEN_WIDTH = ORIGIN_X * 2 + CELL_SIZE * 8 + 200; // ���ڿ�ȣ����ұ߾� + 8 ����� + �Ҳఴť��
const int SCREEN_HEIGHT = ORIGIN_Y * 2 + CELL_SIZE * 8 + 250; // ���ڸ߶ȣ����±߾� + 8 ����� + �·���ʾ��
// ��ǰѡ�и������ꡣ-1 ��ʾδѡ���κθ���
int selectedX = -1, selectedY = -1;
// �ⲿ�����������Ƿ��ƶ�����Ӱ����λ�Ϸ��ԣ�
// extern ��ʾ���������ڱ𴦣�promotion.cpp �� main.cpp ������
extern bool hasMovedWhiteKing = false, hasMovedWhiteRookLeft = false, hasMovedWhiteRookRight = false;
extern bool hasMovedBlackKing = false, hasMovedBlackRookLeft = false, hasMovedBlackRookRight = false;
// �������������ʤ��״̬������ 0=������1=��ʤ��2=��ʤ
int checkVictory();
// ȫ�ֱ�־����ǰִ�巽��true=�׷���false=�ڷ�
bool isWhiteTurn = true;
// ������checkVictory
// ���ã�ɨ������ board�����ķ���������
// ���أ�1 ��ʾ�׷�ʤ���������ԣ���2 ��ʾ�ڷ�ʤ���������ԣ���0 ��ʾ�Ծּ���
int checkVictory() {
    bool whiteKingAlive = false;
    bool blackKingAlive = false;
    // ���� 8��8 ����
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == KING_WHITE) whiteKingAlive = true; // �ҵ�����
            if (board[i][j] == KING_BLACK) blackKingAlive = true; // �ҵ�����
        }
    }
    if (!blackKingAlive) return 1; // ������ʧ �� ��ʤ
    if (!whiteKingAlive) return 2; // ������ʧ �� ��ʤ
    return 0;                      // ˫������ �� �Ծּ���
}
// ������drawMessage
// ���ã��ڴ��ڵײ�����һ����ʾ����
// ������msg ΪҪ��ʾ�� C �ַ�����const char*��
void drawMessage(const char* msg) {
    setfillcolor(WHITE);    // �������ɫ��
    solidrectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, SCREEN_HEIGHT); // �����ʾ��
    settextcolor(RED);      // �ı���ɫ��
    setbkmode(TRANSPARENT); // �ı�����͸��
    outtextxy(ORIGIN_X, SCREEN_HEIGHT - 35, msg); // ��ָ��λ�û����ı�
}
// ������drawHighlights
// ���ã����ơ�ѡ�и��ӡ��͡����кϷ��ƶ�λ�á��ĸ���
void drawHighlights() {
    setlinecolor(RED); // ��ɫ����������ǰѡ�и���
    if (selectedX != -1 && selectedY != -1) {
        // ����ɫ�߿򣬱�ʾ��ѡ�е����Ӹ�
        rectangle(
            ORIGIN_X + selectedX * CELL_SIZE,
            ORIGIN_Y + selectedY * CELL_SIZE,
            ORIGIN_X + (selectedX + 1) * CELL_SIZE,
            ORIGIN_Y + (selectedY + 1) * CELL_SIZE
        );
        // ����ɫ�߿򣬱�ʾ���������кϷ����
        setlinecolor(GREEN);
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                // ���ú����жϺ��� canMove����� (selectedX,selectedY) �� (x,y) �Ƿ�Ϸ�
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
// ������drawCastlingButtons
// ���ã��ڽ����Ҳ���ơ�����λ���͡�����λ��������ť
// ������isWhiteTurn ָʾ��ǰ�ֵ��׷����Ǻڷ�����
// ============================
void drawCastlingButtons(bool isWhiteTurn) {
    settextstyle(18, 0, _T("Consolas"));  // �������壺�ֺ�18������ת��Consolas�������ѡ��
    setbkmode(TRANSPARENT);               // �ı�����ģʽ��͸���������Ǳ������ӣ�
    setlinecolor(WHITE);                  // ������ɫ����ɫ
    settextcolor(WHITE);                  // �ı���ɫ����ɫ
    // ��ťλ�úʹ�С����
    int leftX = 600, topY = 100, width = 120, height = 40;
    // ���ơ�����λ����ť
    rectangle(leftX, topY, leftX + width, topY + height); // ����ť�߿�
    // outtextxy���ڰ�ť�ڲ��� 10 ���ر߾��������֣���Ŀ���������ʾ����
    outtextxy(leftX + 10, topY + 10,
        isWhiteTurn ? _T("�׷�����λ") : _T("�ڷ�����λ"));
    // ���ơ�����λ����ť��Y ��������60����
    rectangle(leftX, topY + 60, leftX + width, topY + 60 + height);
    outtextxy(leftX + 10, topY + 70,
        isWhiteTurn ? _T("�׷�����λ") : _T("�ڷ�����λ"));
}
// ������showCastlingInvalid
// ���ã�����λ����������ʱ�������ɫ������ʾ
// ���أ�false���Ա������ͳһ���� false ��ʾ��λʧ��
bool showCastlingInvalid() {
    setbkmode(OPAQUE);                   // �ı�����ģʽ����͸��������֮ǰ���ݣ�
    settextstyle(20, 0, _T("Consolas")); // �������壺�ֺ�20
    settextcolor(RED);                   // �ı���ɫ����ɫ��ǿ������
    // ������ (50,600) �������ʾ����
    outtextxy(50, 600, _T("���ܽ���������λ�������Ƿ����������ƶ���·�����赲"));
    return false;                        // ���� false��ʹ performCastling Ҳ���� false
}
// ������performCastling
// ���ã�ִ��������λ���������Ϸ��Լ�飩
// ������isWhiteTurn  �� ��ǰ�Ƿ�׷�����
//       isKingside    �� true=����λ�����������ƶ�����false=����λ���������ƶ���
// ���أ�true=��λ�ɹ���false=��λ���Ϸ�
bool performCastling(bool isWhiteTurn, bool isKingside) {
    // ȷ����λ�����У��׷���7�У��ڷ���0��
    int row = isWhiteTurn ? 7 : 0;
    // ȷ��Ҫ�ƶ��Ĺ����ͳ���ö��ֵ
    int king = isWhiteTurn ? KING_WHITE : KING_BLACK;
    int rook = isWhiteTurn ? ROOK_WHITE : ROOK_BLACK;
    // 1. �ж����Ͷ�Ӧ���Ƿ��Ѿ��ƶ����������ƶ���������λ��
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
    // 2. �ж�·���Ƿ�Ϊ�գ�����λҪ��� king->rook ֮�����񣬳���λ�������
    if (isKingside) {
        // ����λ�����5��6
        if (board[row][5] != EMPTY || board[row][6] != EMPTY)
            return showCastlingInvalid();
    }
    else {
        // ����λ�����1��2��3
        if (board[row][1] != EMPTY || board[row][2] != EMPTY || board[row][3] != EMPTY)
            return showCastlingInvalid();
    }
    // 3. ִ��ʵ���ƶ����Ƚ�ԭ����ԭ��λ����Ϊ�գ��ٰ����Ƿŵ���λ��
    if (isKingside) {
        board[row][4] = EMPTY;     // ԭ��λ�����
        board[row][7] = EMPTY;     // ԭ��λ�����
        board[row][6] = king;      // ���ƶ�����6
        board[row][5] = rook;      // ���ƶ�����5
    }
    else {
        board[row][4] = EMPTY;     // ԭ��λ�����
        board[row][0] = EMPTY;     // ԭ��λ�����
        board[row][2] = king;      // ���ƶ�����2
        board[row][3] = rook;      // ���ƶ�����3
    }
    // 4. ���±�־λ����¼���ͳ������ƶ�������ֹ�����ظ���λ
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
    return true; // ��λ�ɹ�
}
// ������handleCastlingClick
// ���ã��������������Ƿ�������λ��ť�ϣ������� performCastling
// ������x,y Ϊ����������ꣻisWhiteTurn ��ǰִ�巽
// ���أ�true=�ѵ����ִ����λ��false=δ�����λ��ť����λʧ��
bool handleCastlingClick(int x, int y, bool isWhiteTurn) {
    // �� drawCastlingButtons ʹ����ͬ�Ĳ���
    int leftX = 600, topY = 100, width = 120, height = 40;
    // ��⡰����λ����ť�������
    if (x >= leftX && x <= leftX + width &&
        y >= topY && y <= topY + height) {
        return performCastling(isWhiteTurn, true);  // Kingside = true
    }
    // ��⡰����λ����ť�������Y ��������60��
    if (x >= leftX && x <= leftX + width &&
        y >= topY + 60 && y <= topY + 60 + height) {
        return performCastling(isWhiteTurn, false); // Kingside = false
    }
    return false; // δ����κ���λ��ť
}
int main() {
    // ��ʼ��ͼ�δ��ڣ��� SCREEN_WIDTH���� SCREEN_HEIGHT
    // initgraph �� EasyX �ṩ�ĺ��������ڴ����������򿪴���
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    // ��ʼ���������ݣ�board ���飩����ʼ����
    initBoard();
    // ��������������ͼ�� pieceImages ����
    loadPieceImages();
    ExMessage msg;           // EasyX ����Ϣ�ṹ���������/�����¼�
    bool running = true;     // ������ѭ����־��false ʱ�˳�
    char message[100] = "�׷�����"; // �ײ���ʾ�У���ʼ��ʾ�׷�����
    // ������ѭ����ֱ�� running ��Ϊ false
    while (running) {
        BeginBatchDraw();         // ��ʼ�������ƣ�������˸
        drawBoard();              // �������̸��Ӻ�����
        drawHighlights();         // ����ѡ�и��ӺͿ���λ�ø���
        drawMessage(message);     // ������ʾ����
        drawCastlingButtons(isWhiteTurn);  // ����������λ��ť
        drawPromotionButtons(isWhiteTurn); // ��������ѡ��ť����������״̬��
        FlushBatchDraw();         // �����������Ʋ���ʾ������
        // �������й�������������Ϣ
        while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
            // ���� Esc ���˳�����
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                running = false;
                break;
            }
            // ��������������¼�
            if (msg.message == WM_LBUTTONDOWN) {
                // ������λ�ö�Ӧ�����̸�����
                int x = (msg.x - ORIGIN_X) / CELL_SIZE;
                int y = (msg.y - ORIGIN_Y) / CELL_SIZE;
                // 1. ���ȴ���������λ��ť���
                //    handleCastlingClick: �������ڰ�ť�ϲ������λ������ true
                if (handleCastlingClick(msg.x, msg.y, isWhiteTurn)) {
                    // ������λ��Ч��PlaySound ���� mmsystem.h
                    PlaySound(_T("crimson.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    isWhiteTurn = !isWhiteTurn;      // �ɹ���λ����
                    selectedX = selectedY = -1;      // ���ѡ��״̬
                    continue;                        // ������ͨ�����߼�
                }
                // 2. ���䰴ť������ȴ���
                //    handlePromotionClick: ��������䰴ť��������������䣬���� true
                if (handlePromotionClick(msg.x, msg.y, isWhiteTurn)) {
                    selectedX = selectedY = -1;      // ���ѡ�У��ȴ���һ������
                    continue;                        // ������ͨ�����߼�
                }
                // 3. �����������̷�Χ�ڣ���������ӻ�ѡ���߼�
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    int piece = board[y][x]; // ��ȡ��������ӵ���������
                    // �ж��Ƿ��ǵ�ǰִ�巽������
                    bool isWhitePiece = piece >= PAWN_WHITE && piece <= KING_WHITE;
                    bool isBlackPiece = piece >= PAWN_BLACK && piece <= KING_BLACK;
                    // ��һ�ε����ѡ�з��������ļ�������
                    if (selectedX == -1 && selectedY == -1) {
                        if ((isWhiteTurn && isWhitePiece) || (!isWhiteTurn && isBlackPiece)) {
                            selectedX = x;
                            selectedY = y;
                        }
                    }
                    // �ڶ��ε�������Խ�ѡ�������ƶ����ø�
                    else {
                        // ���ú��ĺ��� canMove �ж��߷��Ƿ�Ϸ�
                        if (canMove(board, selectedX, selectedY, x, y)) {
                            // ִ���ƶ�����ѡ�и����Ӹ��Ƶ�Ŀ��������ԭ��
                            board[y][x] = board[selectedY][selectedX];
                            board[selectedY][selectedX] = EMPTY;
                            int fromX = selectedX, fromY = selectedY; // �������
                            selectedX = selectedY = -1;               // ����ѡ��
                            // ����������Ч
                            PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            // ��ȡ���ƶ�����������
                            int movedPiece = board[y][x];
                            // �����⣺����ߵ��Է�������Ϊ������������
                            if ((movedPiece == PAWN_WHITE && y == 0) ||
                                (movedPiece == PAWN_BLACK && y == 7)) {
                                showPromotion = true;  // ��������״̬
                                promotionX = x;        // ��¼����λ��
                                promotionY = y;
                                continue;              // ��ͣ���֣��ȴ�����
                            }
                            // �л�ִ�巽
                            isWhiteTurn = !isWhiteTurn;
                            // ���ʤ����1=��ʤ��2=��ʤ��0=����
                            int result = checkVictory();
                            // ��������Ƿ��ƶ�����Ӱ����λ�Ϸ��ԣ�
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
                            // ʤ��ȷ��
                            if (result == 1) {
                                // ����ʤ����Ч
                                PlaySound(_T("manout.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                // MessageBox ���� Windows API�������Ի���
                                MessageBox(GetHWnd(), _T("�׷�ʤ����"), _T("��Ϸ����"),
                                    MB_OK | MB_ICONINFORMATION);
                                break; // �˳���Ϣ����������Ϸ
                            }
                            else if (result == 2) {
                                PlaySound(_T("manout.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                MessageBox(GetHWnd(), _T("�ڷ�ʤ����"), _T("��Ϸ����"),
                                    MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            // ���µײ���ʾ����ʾ�ķ�������
                            sprintf_s(message, "%s������", isWhiteTurn ? "��" : "��");
                        }
                        else {
                            // �Ƿ����ӣ���ʾ�û�����ѡ��
                            sprintf_s(message, "���Ӳ��Ϲ棬����������");
                        }
                        // �����Ƿ�Ϸ���������ѡ��
                        selectedX = selectedY = -1;
                    }
                }
            }
        }
        // ÿ֡ѭ������ͣ10���룬������Ч���ٿ���
        Sleep(10);
    }
    // �˳���ѭ�����ͷ���Դ���ر�ͼ�δ���
    releasePieceImages(); // �ͷ���ͼ��ʵ�������ֶ��ͷţ�
    closegraph();         // �ر� EasyX ����
    return 0;             // ����0����ʾ������������
}

