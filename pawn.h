// pawn.h
#pragma once
// 函数声明：判断一个小兵的走法是否合法
// 参数：fromX/fromY：起点坐标；toX/toY：目标坐标
//       piece：当前棋子；target：目标格子的棋子；board：整个棋盘
bool canPawnMove(int fromX, int fromY, int toX, int toY, PieceType piece, PieceType target, PieceType board[8][8]);
