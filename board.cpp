#include "board.h"
#include <graphics.h> // EasyX

// 棋盘数组定义
int board[BOARD_SIZE][BOARD_SIZE];// A处修改

// 初始化棋盘函数实现
void initBoard() {
    // 清空棋盘，全部设为 EMPTY
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    // 白兵初始行
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[6][j] = PAWN_WHITE;
    }
    // 黑兵初始行
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[1][j] = PAWN_BLACK;
    }
    // 其余白方主力棋子
    board[7][0] = ROOK_WHITE;
    board[7][1] = KNIGHT_WHITE;
    board[7][2] = BISHOP_WHITE;
    board[7][3] = QUEEN_WHITE;
    board[7][4] = KING_WHITE;
    board[7][5] = BISHOP_WHITE;
    board[7][6] = KNIGHT_WHITE;
    board[7][7] = ROOK_WHITE;

    // 其余黑方主力棋子
    board[0][0] = ROOK_BLACK;
    board[0][1] = KNIGHT_BLACK;
    board[0][2] = BISHOP_BLACK;
    board[0][3] = QUEEN_BLACK;
    board[0][4] = KING_BLACK;
    board[0][5] = BISHOP_BLACK;
    board[0][6] = KNIGHT_BLACK;
    board[0][7] = ROOK_BLACK;
}

// 棋子贴图列表
IMAGE pieceImages[13]; // 下标与 PieceType 对应

// 加载棋子贴图，文件名统一格式如 "queen_white.bmp"
void loadPieceImages() {
    const char* filenames[13] = {
        "empty.bmp", // 空图，或忽略
        "pawn_white.bmp",
        "rook_white.bmp",
        "knight_white.bmp",
        "bishop_white.bmp",
        "queen_white.bmp",
        "king_white.bmp",
        "pawn_black.bmp",
        "rook_black.bmp",
        "knight_black.bmp",
        "bishop_black.bmp",
        "queen_black.bmp",
        "king_black.bmp"
    };
    for (int i = 0; i < 13; i++) {
        loadimage(&pieceImages[i], filenames[i]);
    }
}

// 释放贴图资源
void releasePieceImages() {
    for (int i = 0; i < 13; i++) {
        // EasyX 无需显式释放 IMAGE，空实现留作接口扩展
    }
}

// 绘制棋盘和棋子
void drawBoard() {
    // 棋盘格尺寸
    const int CELL_SIZE = 64;
    // 棋盘左上角起点坐标
    const int ORIGIN_X = 50;
    const int ORIGIN_Y = 50;

    // 画格子，黑白相间
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int left = ORIGIN_X + j * CELL_SIZE;
            int top = ORIGIN_Y + i * CELL_SIZE;
            int right = left + CELL_SIZE;
            int bottom = top + CELL_SIZE;

            // 黑白格子颜色交替
            if ((i + j) % 2 == 0) {
                setfillcolor(RGB(240, 217, 181)); // 浅色
            }
            else {
                setfillcolor(RGB(181, 136, 99)); // 深色
            }
            fillrectangle(left, top, right, bottom);

            // 画棋子图片
            int piece = board[i][j];
            if (piece != EMPTY) {
                // 贴图绘制居中
                putimage(left, top, &pieceImages[piece]);
            }
        }
    }
}
