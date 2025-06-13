#include <graphics.h>
#include "board.h"
#include "piece_images.h"
#include "move_logic.h"

int main() {
    initgraph(512, 512); // 8x8 * 64px

    initBoard();          // ��ʼ����������
    loadPieceImages();    // ������ͼ��Դ
    drawBoard();          // �������̸���
    drawAllPieces();      // ������������

    // ������ѭ��������չ����¼�
    while (!_kbhit()) {
        // ���޽����߼�
        Sleep(10);
    }

    closegraph();
    releasePieceImages(); // �ͷ���ͼ
    return 0;
}
