#pragma once
#include <map>
#include <string>
#include <graphics.h>
#include "board.h"

// ����ÿ�����ӵ�ͼƬ��Դ
std::map<Piece, IMAGE*> pieceImages;

// ����ÿ�����Ӷ�ӦͼƬ·��
std::string getPieceImagePath(Piece piece) {
    switch (piece) {
    case WPAWN: return "img/pawn_white.bmp";
    case WROOK: return "img/rook_white.bmp";
    case WKNIGHT: return "img/knight_white.bmp";
    case WBISHOP: return "img/bishop_white.bmp";
    case WQUEEN: return "img/queen_white.bmp";
    case WKING: return "img/king_white.bmp";
    case BPAWN: return "img/pawn_black.bmp";
    case BROOK: return "img/rook_black.bmp";
    case BKNIGHT: return "img/knight_black.bmp";
    case BBISHOP: return "img/bishop_black.bmp";
    case BQUEEN: return "img/queen_black.bmp";
    case BKING: return "img/king_black.bmp";
    default: return "";
    }
}

// ��������ͼƬ
void loadPieceImages() {
    for (int i = WPAWN; i <= BKING; ++i) {
        Piece p = static_cast<Piece>(i);
        pieceImages[p] = new IMAGE();
        loadimage(pieceImages[p], getPieceImagePath(p).c_str());
    }
}

// �ͷ�ͼƬ��Դ
void releasePieceImages() {
    for (auto& entry : pieceImages) {
        delete entry.second;
    }
    pieceImages.clear();
}

// �������������ϵ���������
void drawAllPieces() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            Piece p = board[r][c];
            if (p != EMPTY) {
                drawPiece(p, r, c);
            }
        }
    }
}

// ���Ƶ�������
void drawPiece(Piece p, int row, int col) {
    IMAGE* img = pieceImages[p];
    if (img) {
        putimage(col * TILE_SIZE, row * TILE_SIZE, img);
    }
}
