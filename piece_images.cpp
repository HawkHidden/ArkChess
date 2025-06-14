#include "piece_images.h"
#include <string>

std::map<int, IMAGE*> pieceImages;

std::string getPieceImagePath(int piece) {
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

void loadPieceImages() {
    for (int i = WPAWN; i <= BKING; ++i) {
        IMAGE* img = new IMAGE();
        loadimage(img, getPieceImagePath(i).c_str());
        pieceImages[i] = img;
    }
}

void releasePieceImages() {
    for (auto& p : pieceImages) delete p.second;
    pieceImages.clear();
}

void drawPiece(int piece, int row, int col) {
    if (piece == EMPTY || pieceImages.count(piece) == 0) return;
    putimage(col * 64, row * 64, pieceImages[piece]);
}

void drawAllPieces() {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            drawPiece(board[r][c], r, c);
}