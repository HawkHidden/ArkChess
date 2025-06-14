#ifndef MOVE_QUEEN_H
#define MOVE_QUEEN_H

// 皇后走法判断函数
// 输入：棋盘数组、起始坐标 (fromX, fromY)、目标坐标 (toX, toY)
// 返回：是否为合法移动
bool canMoveQueen(int board[8][8], int fromX, int fromY, int toX, int toY);

#endif
