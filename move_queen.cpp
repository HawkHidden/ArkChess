#include "move_queen.h"
#include "board.h"

// 判断皇后走法是否合规（直线 + 斜线均可）
bool canMoveQueen(int board[8][8], int fromX, int fromY, int toX, int toY) {
    // 1. 起点与终点不能相同（不能不动）
    if (fromX == toX && fromY == toY) {
        return false;
    }

    int dx = toX - fromX;
    int dy = toY - fromY;

    // 2. 确定走的是直线 or 对角线
    bool isStraight = (dx == 0 || dy == 0);
    bool isDiagonal = (abs(dx) == abs(dy));

    if (!isStraight && !isDiagonal) {
        // 既不是直线也不是斜线
        return false;
    }

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int x = fromX + stepX;
    int y = fromY + stepY;

    // 3. 检查路径上是否有阻挡（不能越子）
    while (x != toX || y != toY) {
        if (board[y][x] != EMPTY) {
            return false;  // 路径被阻挡
        }
        x += stepX;
        y += stepY;
    }

    // 4. 判断目标是否为敌方或空
    int piece = board[fromY][fromX];
    int target = board[toY][toX];

    bool isWhite = (piece >= PAWN_WHITE && piece <= KING_WHITE);
    bool targetIsWhite = (target >= PAWN_WHITE && target <= KING_WHITE);
    bool targetIsBlack = (target >= PAWN_BLACK && target <= KING_BLACK);

    if ((isWhite && targetIsWhite) || (!isWhite && targetIsBlack)) {
        return false;  // 不允许吃自己
    }

    // 合法移动
    return true;
}
