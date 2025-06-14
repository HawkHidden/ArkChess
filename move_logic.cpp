#include "move_logic.h"      // 本文件头部：统一调度各类棋子走法
#include "move_rook.h"       // 车
#include "move_bishop.h"     // 主教
#include "move_knight.h"     // 马骑士
#include "move_queen.h"      // 后
#include "move_king.h"       // 王
#include "move_pawn.h"       // 兵
#include "board.h"           // 棋盘与棋子枚举常量定义
// 核心函数：判断某个棋子是否能从 (fromX, fromY) 移动到 (toX, toY)
bool canMove(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];         // 获取起始格上的棋子编号
    if (piece == EMPTY) return false;        // 空格上无棋子，不能移动
    int target = board[toY][toX];            // 获取目标格上的棋子编号
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE); // 判断是否白方棋子
    // 如果目标格上是己方棋子，则不能移动（不能吃自己人）
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // 根据棋子类型，调用对应的“走法判断函数”
    switch (piece) {
    case ROOK_WHITE: case ROOK_BLACK:
        return canMoveRook(board, fromX, fromY, toX, toY);       // 车
    case BISHOP_WHITE: case BISHOP_BLACK:
        return canMoveBishop(board, fromX, fromY, toX, toY);     // 象
    case KNIGHT_WHITE: case KNIGHT_BLACK:
        return canMoveKnight(board, fromX, fromY, toX, toY);     // 马
    case QUEEN_WHITE: case QUEEN_BLACK:
        return canMoveQueen(board, fromX, fromY, toX, toY);      // 后
    case KING_WHITE: case KING_BLACK:
        return canMoveKing(board, fromX, fromY, toX, toY);       // 王
    case PAWN_WHITE: case PAWN_BLACK:
        return canMovePawn(board, fromX, fromY, toX, toY);       // 兵
    default:
        return false;                                            // 非法棋子编号
    }
}

