#include <graphics.h>
#include "board.h"
#include "piece_images.h"
#include "move_logic.h"

int main() {
    initgraph(512, 512); // 8x8 * 64px

    initBoard();          // 初始化棋盘数组
    loadPieceImages();    // 加载贴图资源
    drawBoard();          // 绘制棋盘格子
    drawAllPieces();      // 绘制所有棋子

    // 简易主循环，可扩展点击事件
    while (!_kbhit()) {
        // 暂无交互逻辑
        Sleep(10);
    }

    closegraph();
    releasePieceImages(); // 释放贴图
    return 0;
}
