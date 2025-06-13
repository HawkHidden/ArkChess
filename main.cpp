#include <graphics.h>     // EasyX 图形库
#include <conio.h>        // 控制台输入
#include <string>
#include <iostream>
#include"pawn.h"

const int CELL_SIZE = 64;     // 棋盘格子大小
const int BOARD_SIZE = 8;     // 棋盘行列数
const int WINDOW_SIZE = CELL_SIZE * BOARD_SIZE;

enum PieceType {
    EMPTY = 0,
    WPAWN, WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING,
    BPAWN, BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING
};

// 棋盘数组（初始化为示意摆法）
int board[8][8] = {
    { BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK },
    { BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN },
    { WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK }
};

// 棋子贴图
IMAGE pieceImgs[13];  // EMPTY 不加载图像

// 将棋子变量名类型映射到图片路径
std::string getImagePath(PieceType type) {
    switch (type) {
    case WPAWN: return "pawn_white.bmp";
    case WROOK: return "rook_white.bmp";
    case WKNIGHT: return "knight_white.bmp";
    case WBISHOP: return "bishop_white.bmp";
    case WQUEEN: return "queen_white.bmp";
    case WKING: return "king_white.bmp";
    case BPAWN: return "pawn_black.bmp";
    case BROOK: return "rook_black.bmp";
    case BKNIGHT: return "knight_black.bmp";
    case BBISHOP: return "bishop_black.bmp";
    case BQUEEN: return "queen_black.bmp";
    case BKING: return "king_black.bmp";
    default: return "";
    }
}

void loadImages() {
    for (int i = 1; i <= 12; ++i) {
        loadimage(&pieceImgs[i], getImagePath((PieceType)i).c_str(), CELL_SIZE, CELL_SIZE, true);
    }
}

void drawBoard() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            bool isLight = (row + col) % 2 == 0;
            setfillcolor(isLight ? RGB(240, 217, 181) : RGB(181, 136, 99));
            solidrectangle(col * CELL_SIZE, row * CELL_SIZE,
                (col + 1) * CELL_SIZE, (row + 1) * CELL_SIZE);
        }
    }
}

void drawPieces() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            int piece = board[row][col];
            if (piece != EMPTY) {
                putimage(col * CELL_SIZE, row * CELL_SIZE, &pieceImgs[piece]);
            }
        }
    }
}

void gameLoop() {
    while (true) {
        drawBoard();
        drawPieces();
        FlushBatchDraw();

        MOUSEMSG m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            int col = m.x / CELL_SIZE;
            int row = m.y / CELL_SIZE;
            std::cout << "Clicked: (" << row << ", " << col << ")\n";
            // 后续可处理点击选中/移动逻辑
        }
    }
}

int main() {
    initgraph(WINDOW_SIZE, WINDOW_SIZE);
    loadImages();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);

    BeginBatchDraw(); // 开启批量绘制（减少闪烁）

    gameLoop();

    EndBatchDraw();
    closegraph();
    return 0;
}


// 判断当前位置是否是敌方棋子（简化版）
bool isEnemy(PieceType from, PieceType to) {
    if (from == EMPTY || to == EMPTY) return false;

    // 白色棋子编号范围：1~6
    // 黑色棋子编号范围：7~12
    return (from <= WKING && to >= BPAWN) || (from >= BPAWN && to <= WKING);
}


