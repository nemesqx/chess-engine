/*
MIT License

Copyright (c) 2023 nemesis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include "piece.h"
#include "util.h"

using namespace std;

const int BOARD_SIZE = 8;

class ChessBoard {
public:
  ChessBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        board[i][j] = Empty;
      }
    }
  }

  void init() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      board[1][i] = BPawn;
      board[6][i] = WPawn;
    }
    board[0][0] = board[0][7] = BRook;
    board[7][0] = board[7][7] = WRook;
    board[0][1] = board[0][6] = BKnight;
    board[7][1] = board[7][6] = WKnight;
    board[0][2] = board[0][5] = BBishop;
    board[7][2] = board[7][5] = WBishop;
    board[0][3] = BQueen;
    board[7][3] = WQueen;
    board[0][4] = BKing;
    board[7][4] = WKing;
  }

  void print() {
    cout << "  A  B  C  D  E  F  G  H" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
      cout << 8 - i << " ";
      for (int j = 0; j < BOARD_SIZE; j++) {
        switch (board[i][j]) {
          case Empty:
            cout << "-- ";
            break;
          case WPawn:
            cout << "WP ";
            break;
          case WRook:
            cout << "WR ";
            break;
          case WKnight:
            cout << "WN ";
            break;
          case WBishop:
            cout << "WB ";
            break;
          case WQueen:
            cout << "WQ ";
            break;
          case WKing:
            cout << "WK ";
            break;
          case BPawn:
            cout << "BP ";
            break;
          case BRook:
            cout << "BR ";
            break;
          case BKnight:
            cout << "BN ";
            break;
          case BBishop:
            cout << "BB ";
            break;
          case BQueen:
            cout << "BQ ";
            break;
          case BKing:
            cout << "BK ";
            break;
        } 
      }
      cout << endl;
    }
}

Piece getPiece(Square square) {
    return board[square.row][square.col];
}

PieceType blackOrWhite(Piece &piece) { 
  if (piece == WKing || piece == WKnight || piece == WRook || piece == WPawn || piece == WQueen || piece == WBishop) {
    return White;
  } else if (piece == BKing || piece == BKnight || piece == BRook || piece == BPawn || piece == BQueen || piece == BBishop) {
    return Black; 
  } else {
    return EmptyPieceType;
  }
}

bool canCapture(Piece piece, Piece toCapture) { 
  if (blackOrWhite(piece) == White && (blackOrWhite(toCapture) == Black || blackOrWhite(toCapture) == EmptyPieceType)) {
    return true;
  } else if (blackOrWhite(piece) == Black && (blackOrWhite(toCapture) == White || blackOrWhite(toCapture) == EmptyPieceType)) {
    return true;
  } else {
    return false;
  }
}

bool canMove2Squares(Square square) {
  Piece piece = getPiece(square);
  if (piece == WPawn) {
    if (square.row == 6) {
      return true;
    } else {
      return false;
    }
  } else if (piece == BPawn) {
    if (square.row == 1) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool isValidMove(Move move) {
      Square fromSquare;
      Square toSquare;

      fromSquare.row = move.from_row;
      fromSquare.col = move.from_col;

      toSquare.row = move.to_row;
      toSquare.col = move.to_col;

      int dirX = toSquare.col - fromSquare.col;
      int dirY = fromSquare.row - toSquare.row;

      Piece piece = getPiece(fromSquare);
      Piece moveToPiece = getPiece(toSquare);
      PieceType pieceType = blackOrWhite(piece);

      if (canCapture(piece, moveToPiece) == false) {
        return false;
      }
      
      switch(piece) {

        case Empty:
        return false;
        break;

        case WKnight: case BKnight:
        if (dirY == 2 && dirX == 1 || dirY == 2 && dirX==-1 || dirY == -2 && dirX == 1 || dirY == -2 && dirX == -1) {
          return true;
        } 
        else {
          return false;
        }

        break;

        case WPawn: case BPawn: 
        if ((dirX == 0 && dirY == 1 && moveToPiece == Empty && pieceType == White) || (dirX == 0 && dirY == -1 && moveToPiece == Empty && pieceType == Black)) {
             return true;
          } 
          else if ( (dirX == 0 && dirY == 2 && pieceType == White) || (dirX == 0 && dirY == -2 && pieceType == Black) ) {
             int displacement1 = 1;
             int displacement2 = 2;

             if (pieceType == Black) { 
                displacement1 = -displacement1;
                displacement2 = -displacement2;
             }
             Square squareToCheck; 
             squareToCheck.row = fromSquare.row - displacement1;
             squareToCheck.col = fromSquare.col;

             Square squareToCheck2;
             squareToCheck2.row = fromSquare.row - displacement2;
             squareToCheck2.col = fromSquare.col;

             if (canMove2Squares(fromSquare) && getPiece(squareToCheck) == Empty && getPiece(squareToCheck2) == Empty) { 
                 return true;
              } else {
                 return false;
              }
        }

        else if ( ( ( (dirX == 1 && dirY == 1 || dirX == -1 && dirY == 1) && blackOrWhite(piece) == White) || ((dirX== 1 && dirY == -1 || dirX == -1 && dirY == -1) && blackOrWhite(piece) == Black)) && moveToPiece != Empty && canCapture(piece, moveToPiece)) {
          return true;
        } 

        else {
          return false;
        }
        
        break;

        case BBishop: case WBishop:
        if (abs(dirX) != abs(dirY)) {
          return false; 
        } else {
          return true;
        }

        break;
      }
      
      std::cout << "no case resolved";
      return true;  
}
    
  bool makeMove(Move move) {
      if (!isValidMove(move)) {
        return false;
      }

      board[move.to_row][move.to_col] = board[move.from_row][move.from_col];
      board[move.from_row][move.from_col] = Piece::Empty;
      return true;
    }


  Piece board[BOARD_SIZE][BOARD_SIZE];
};