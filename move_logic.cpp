// move_logic.cpp
#include "move_logic.h"
#include "move_rook.h"
#include "move_bishop.h"
#include "move_knight.h"
#include "move_queen.h"
#include "move_king.h"
#include "move_pawn.h"
#include "board.h"

bool canMove(int board[8][8], int fromX, int fromY, int toX, int toY) {
    int piece = board[fromY][fromX];
    if (piece == EMPTY) return false;  // 无棋子
    // 目标不能落在己方棋子上
    int target = board[toY][toX];
    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    if ((isWhite && target >= PAWN_WHITE && target <= KING_WHITE) ||
        (!isWhite && target >= PAWN_BLACK && target <= KING_BLACK)) {
        return false;
    }
    // 根据类型调用相应函数
    switch (piece) {
    case ROOK_WHITE: case ROOK_BLACK:
        return canMoveRook(board, fromX, fromY, toX, toY);
    case BISHOP_WHITE: case BISHOP_BLACK:
        return canMoveBishop(board, fromX, fromY, toX, toY);
    case KNIGHT_WHITE: case KNIGHT_BLACK:
        return canMoveKnight(board, fromX, fromY, toX, toY);
    case QUEEN_WHITE: case QUEEN_BLACK:
        return canMoveQueen(board, fromX, fromY, toX, toY);
    case KING_WHITE: case KING_BLACK:
        return canMoveKing(board, fromX, fromY, toX, toY);
    case PAWN_WHITE: case PAWN_BLACK:
        return canMovePawn(board, fromX, fromY, toX, toY);
    default:
        return false;
    }
}