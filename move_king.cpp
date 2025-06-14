#include "move_king.h"         // 包含国王走法函数的声明
#include "board.h"             // 引入棋盘与棋子类型定义
#include <cmath>               // 提供 abs 函数用于计算距离
// 判断国王（King）是否能从 (fromX, fromY) 移动到 (toX, toY)
bool canMoveKing(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];                // 获取当前棋子
    if (piece != KING_WHITE && piece != KING_BLACK) return false; // 必须是国王才能调用此函数
    int dx = std::abs(toX - fromX);                 // 横向移动距离
    int dy = std::abs(toY - fromY);                 // 纵向移动距离
    if (dx > 1 || dy > 1) return false;             // 国王每次只能移动一步（任意方向）
    int target = board[toY][toX];                   // 获取目标格子的棋子
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE); // 判断是否为白方棋子
    // 若目标格子是己方棋子，则不能移动过去
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    return true; // 一步可走、目标格无己方子，则合法
}
