#include "board.h"
// ����ģ��ȫ�ֿ���
extern bool showPromotion;  // �Ƿ�������ʾ���䰴ť
extern int promotionX;      // ����Ŀ������� X
extern int promotionY;      // ����Ŀ������� Y
// �׷�����ѡ�����Ϊ�󡢳�������
const int WHITE_PROMOTION_OPTIONS[4] = { QUEEN_WHITE, ROOK_WHITE, BISHOP_WHITE, KNIGHT_WHITE };
// �ڷ�����ѡ��
const int BLACK_PROMOTION_OPTIONS[4] = { QUEEN_BLACK, ROOK_BLACK, BISHOP_BLACK, KNIGHT_BLACK };
// �������䰴ť
void drawPromotionButtons(bool isWhiteTurn);
// ����ť���
bool handlePromotionClick(int mouseX, int mouseY, bool& isWhiteTurn);
