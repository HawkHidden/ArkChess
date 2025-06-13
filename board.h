#pragma once
#include <graphics.h>

const int ROWS = 8;
const int COLS = 8;
const int TILE_SIZE = 64;

// 枚举所有棋子
enum Piece {
    EMPTY,
    WPAWN, WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING,
    BPAWN, BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING
};

extern Piece board[ROWS][COLS]; // 棋盘数据

// 初始化棋盘布局（默认布局）
void initBoard() {
    // 清空棋盘
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            board[r][c] = EMPTY;

    // 添加白棋
    board[6][0] = board[6][1] = board[6][2] = board[6][3] =
        board[6][4] = board[6][5] = board[6][6] = board[6][7] = WPAWN;

    board[7][0] = board[7][7] = WROOK;
    board[7][1] = board[7][6] = WKNIGHT;
    board[7][2] = board[7][5] = WBISHOP;
    board[7][3] = WQUEEN;
    board[7][4] = WKING;

    // 添加黑棋
    board[1][0] = board[1][1] = board[1][2] = board[1][3] =
        board[1][4] = board[1][5] = board[1][6] = board[1][7] = BPAWN;

    board[0][0] = board[0][7] = BROOK;
    board[0][1] = board[0][6] = BKNIGHT;
    board[0][2] = board[0][5] = BBISHOP;
    board[0][3] = BQUEEN;
    board[0][4] = BKING;
}

// 绘制棋盘格子
void drawBoard() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            COLORREF color = (r + c) % 2 == 0 ? RGB(240, 217, 181) : RGB(181, 136, 99);
            setfillcolor(color);
            solidrectangle(c * TILE_SIZE, r * TILE_SIZE,
                (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
        }
    }
}
