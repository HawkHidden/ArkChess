#include "board.h"           // 引入棋盘头文件，包含常量定义和棋盘相关函数声明
#include <graphics.h>        // 引入 EasyX 图形库，用于图形绘制
// 模块一：棋盘数据结构
// 定义棋盘数组，保存当前棋盘每个格子的棋子类型
// board[i][j] 表示第 i 行 j 列上的棋子
// 每个格子的值是一个枚举类型（PieceType），例如 PAWN_WHITE、KING_BLACK 等
int board[BOARD_SIZE][BOARD_SIZE]; // A处修改
// 模块二：棋盘初始化函数
// 初始化棋盘函数：设置初始布局，包括黑白兵与主力棋子
void initBoard() {
    // 第一步：先将整个棋盘清空，即每个格子都设为 EMPTY
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    // 第二步：放置白兵在第6行（数组下标为6）
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[6][j] = PAWN_WHITE;
    }
    // 第三步：放置黑兵在第1行（数组下标为1）
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[1][j] = PAWN_BLACK;
    }
    // 第四步：设置白方主力棋子（第7行）
    board[7][0] = ROOK_WHITE;
    board[7][1] = KNIGHT_WHITE;
    board[7][2] = BISHOP_WHITE;
    board[7][3] = QUEEN_WHITE;
    board[7][4] = KING_WHITE;
    board[7][5] = BISHOP_WHITE;
    board[7][6] = KNIGHT_WHITE;
    board[7][7] = ROOK_WHITE;
    // 第五步：设置黑方主力棋子（第0行）
    board[0][0] = ROOK_BLACK;
    board[0][1] = KNIGHT_BLACK;
    board[0][2] = BISHOP_BLACK;
    board[0][3] = QUEEN_BLACK;
    board[0][4] = KING_BLACK;
    board[0][5] = BISHOP_BLACK;
    board[0][6] = KNIGHT_BLACK;
    board[0][7] = ROOK_BLACK;
}
// 模块三：棋子图片加载管理
// 定义棋子贴图资源数组
// 每个下标对应一个棋子类型，如 1=PAWN_WHITE，12=KING_BLACK
IMAGE pieceImages[13]; // 共13种：包括空格子 + 6种棋子 × 2种颜色
// 加载棋子贴图，加载的是 BMP 图片文件，按下标一一对应
void loadPieceImages() {
    const char* filenames[13] = {
        "empty.bmp",        // 下标0，对应 EMPTY
        "pawn_white.bmp",   // 下标1
        "rook_white.bmp",
        "knight_white.bmp",
        "bishop_white.bmp",
        "queen_white.bmp",
        "king_white.bmp",   // 下标6
        "pawn_black.bmp",   // 下标7
        "rook_black.bmp",
        "knight_black.bmp",
        "bishop_black.bmp",
        "queen_black.bmp",
        "king_black.bmp"    // 下标12
    };
    for (int i = 0; i < 13; i++) {
        loadimage(&pieceImages[i], filenames[i]);  // EasyX 函数，加载指定 BMP 图片到图像对象中
    }
}
// 模块四：资源释放（可选）
// 释放贴图资源函数，目前未具体实现
void releasePieceImages() {   
		//没做悔棋功能，所以不需要释放贴图资源    
}
// 模块五：绘制棋盘与棋子
// 绘制棋盘背景与当前棋子分布
void drawBoard() {
    const int CELL_SIZE = 64;         // 每个棋盘格子的边长（单位：像素）
    const int ORIGIN_X = 50;          // 棋盘左上角的 X 坐标
    const int ORIGIN_Y = 50;          // 棋盘左上角的 Y 坐标
    // 遍历整个棋盘 8x8，每个格子都绘制背景和棋子
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // 计算当前格子的左上角与右下角坐标
            int left = ORIGIN_X + j * CELL_SIZE;
            int top = ORIGIN_Y + i * CELL_SIZE;
            int right = left + CELL_SIZE;
            int bottom = top + CELL_SIZE;
            // 交错设定格子颜色，实现国际象棋黑白格
            if ((i + j) % 2 == 0) {
                setfillcolor(RGB(240, 217, 181)); // 浅色格子
            }
            else {
                setfillcolor(RGB(181, 136, 99));  // 深色格子
            }
            fillrectangle(left, top, right, bottom); // 绘制矩形背景
            // 获取该格子的棋子编号
            int piece = board[i][j];
            if (piece != EMPTY) {
                // 如果不是空格子，绘制对应的棋子贴图
                // putimage 将图片贴到指定坐标
                putimage(left, top, &pieceImages[piece]);
            }
        }
    }
}




