#include "promotion.h"       // ����ģ��ͷ�ļ������������뺯���ӿ�
#include <graphics.h>        // ���� EasyX ͼ�ο⣬���ڻ��ư�ť����ͼ
// ����ģ��ȫ�ֱ���
// showPromotion: ��־��ǰ�Ƿ�������ѡ��״̬
//   true  -> ��ʾ���䰴ť���ȴ���ҵ��
//   false -> ������Ϸ������ʾ���䰴ť
bool showPromotion = false;
// promotionX, promotionY: ��¼��Ҫ����ı�������������
//   �����ߵ��յ���ʱ�����������������Ա�����ťʱ�滻��ȷλ��
int promotionX = -1;
int promotionY = -1;
// ������drawPromotionButtons
// ���ã����Ҳഹֱ���� 4 ������ѡ�ť
// ������isWhiteTurn ��ʾ��ǰ���䷽�ǰ׷����Ǻڷ�
void drawPromotionButtons(bool isWhiteTurn) {
    if (!showPromotion) return;  // ����������״̬��ֱ�ӷ��ز�����
    // ��ť��ʼ����ͳߴ�
    const int BTN_X = 600;     // ��ť��� X ����
    const int BTN_Y = 400;     // ��һ����ť���� Y ���꣨λ����λ��ť�·���
    const int BTN_SIZE = 64;      // ��ť�����α߳�����������ͼ�ߴ�һ�£�
    const int BTN_GAP = 10;      // ��ť֮��Ĵ�ֱ���
    // �����ֵ��ķ���ѡ���Ӧ��������������ָ��
    // WHITE_PROMOTION_OPTIONS �� BLACK_PROMOTION_OPTIONS �� promotion.h �ж���
    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;
    // ���û�ͼ����
    setbkcolor(BLACK);             // ����ɫΪ�ڣ���ť�·��������
    settextcolor(WHITE);           // ������ɫΪ��
    setbkmode(TRANSPARENT);        // �ı�����͸��
    // ѭ������ 4 ����ť
    for (int i = 0; i < 4; ++i) {
        // ����� i ����ť�Ķ����͵ײ� Y ����
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;
        // �� ���ư�ť�߿�
        setlinecolor(WHITE);                                       // �߿���Ϊ��ɫ
        rectangle(BTN_X, top, BTN_X + BTN_SIZE, bottom);           // ���ƾ��α߿�
        // �� �ڰ�ť���ڻ��ƶ�Ӧ������ͼ�������϶���պ�����64��64��
        // options[i] ��ö��ֵ����Ӧ pieceImages �����±�
        putimage(BTN_X, top, &pieceImages[options[i]]);
    }
    // ����һ��������ʾ������ѡ�񡱣�λ�ڰ�ť���Ϸ�
    outtextxy(BTN_X, BTN_Y - 30, "����ѡ��");
}
// ������handlePromotionClick
// ���ã����������Ƿ���ĳһ���䰴ť�ϣ�������ִ������
// ������mouseX, mouseY Ϊ���������������
//       isWhiteTurn ���ò�����������ɺ�Ҫ�л����巽
// ���أ��Ƿ��������䣨true ��ʾ�������Ч��ť����ִ�У�
bool handlePromotionClick(int mouseX, int mouseY, bool& isWhiteTurn) {
    if (!showPromotion) return false;  // ����������״̬�����Ե��
    // �� drawPromotionButtons ����ͬ�İ�ťλ����ߴ糣��
    const int BTN_X = 600;
    const int BTN_Y = 400;
    const int BTN_SIZE = 64;
    const int BTN_GAP = 10;
    const int* options = isWhiteTurn ? WHITE_PROMOTION_OPTIONS : BLACK_PROMOTION_OPTIONS;
    // ���� 4 ����ť�������������Ƿ�����ĳ����ť����
    for (int i = 0; i < 4; ++i) {
        int top = BTN_Y + i * (BTN_SIZE + BTN_GAP);
        int bottom = top + BTN_SIZE;
        // ����� X �ڰ�ť���ұ߽�֮�䣬�� Y �ڰ�ť���±߽�֮��
        if (mouseX >= BTN_X && mouseX <= BTN_X + BTN_SIZE &&
            mouseY >= top && mouseY <= bottom) {
            // ѡ�е� i ������ѡ�
            // options[i] ��Ҫ�滻��ö��ֵ���� QUEEN_WHITE��
            board[promotionY][promotionX] = options[i];
            // �ر�����״̬����������
            showPromotion = false;
            promotionX = -1;
            promotionY = -1;
            // ��������ɹ�����ʾ��Ч
            PlaySound(TEXT("promotion.wav"), NULL, SND_FILENAME | SND_ASYNC);
            // ������ɺ��л����巽�����������㱾�غ��ж���һ���֣����ڽ����Է���
            isWhiteTurn = !isWhiteTurn;
            return true; // ��ʾ���ε���ѱ�����
        }
    }
    return false; // ��������κ����䰴ť��
}
