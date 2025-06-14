#include "move_knight.h"         // 声明马（Knight）的走法判断函数
#include "board.h"               // 包含棋盘与棋子类型定义
#include <cmath>                 // 提供 abs 函数，用于距离计算
// 判断马（Knight）是否能从 (fromX, fromY) 移动到 (toX, toY)
bool canMoveKnight(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];                             // 当前选中的棋子
    if (piece != KNIGHT_WHITE && piece != KNIGHT_BLACK) return false; // 只能处理马的移动
    int dx = std::abs(toX - fromX);                              // 横向距离
    int dy = std::abs(toY - fromY);                              // 纵向距离
    // 马的合法走法是“L形”移动：一个方向走2格，另一个方向走1格
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) return false;
    int target = board[toY][toX];                                // 获取目标格的棋子
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);// 判断当前是否白方棋子
    // 如果目标格上是己方棋子，则不能跳过去
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // 马跳跃时可以越过其它棋子，因此不判断路径是否有阻挡
    return true; // 合法 L 形 + 非己方目标格，即可移动
}
