// pawn.h
#pragma once
// �����������ж�һ��С�����߷��Ƿ�Ϸ�
// ������fromX/fromY��������ꣻtoX/toY��Ŀ������
//       piece����ǰ���ӣ�target��Ŀ����ӵ����ӣ�board����������
bool canPawnMove(int fromX, int fromY, int toX, int toY, PieceType piece, PieceType target, PieceType board[8][8]);
