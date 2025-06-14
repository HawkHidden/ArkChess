#ifndef BOARD_H
#define BOARD_H
#include <graphics.h> // EasyX图形库头文件
#include <iostream>
using namespace std;
// 棋子类型枚举
enum PieceType {
    EMPTY = 0,
    PAWN_WHITE, ROOK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, QUEEN_WHITE, KING_WHITE,
    PAWN_BLACK, ROOK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, QUEEN_BLACK, KING_BLACK
};

// 棋盘大小定义
const int BOARD_SIZE = 8;

// 棋盘数组定义
// 0 表示空格，其他值对应枚举的棋子类型
extern int board[BOARD_SIZE][BOARD_SIZE];

// 初始化棋盘函数，设置初始棋子位置
void initBoard();

// 绘制棋盘与棋子，参数为绘图相关，放EasyX调用
void drawBoard();
void releasePieceImages();
void loadPieceImages();

#endif
