/* Copyright (c) 2023 nemesis 
Scroll down to the bottom of the file to see extensive license information.*/

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector>
using namespace std;

bool debug_mode = false; // not implemented yet

const int BOARD_SIZE = 8;

enum Piece {
  Empty,
  WPawn,
  WRook,
  WKnight,
  WBishop,
  WQueen,
  WKing,
  BPawn,
  BRook,
  BKnight,
  BBishop,
  BQueen,
  BKing
};

enum PieceType {
  Black,
  White,
  EmptyPieceType
};

struct Square {
  int row;
  int col;
};

class Move {
public:
    int from_row, from_col, to_row, to_col;
    Move(int from_row, int from_col, int to_row, int to_col) {
        this->from_row = from_row;
        this->from_col = from_col;
        this->to_row = to_row;
        this->to_col = to_col;
    }
};

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
    // Initialize the pieces on the board
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

        else if ((dirX == 1 && dirY == 1 || dirX == -1 && dirY == 1) && moveToPiece != Empty && canCapture(piece, moveToPiece)) {
          return true;
        } 

        else {
          return false;
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
      board[move.from_row][move.from_col] = Empty;
      return true;
    }


  Piece board[BOARD_SIZE][BOARD_SIZE];
};

class ChessAI {
public:

  ChessAI(ChessBoard& chessBoard) : chessBoard(chessBoard) {}

  bool isValidMove(Move move) { 
    return true;
  }

  void move() {
  int moveMade = false;

  while (!moveMade) {
    cout << "Enter your move in algebraic notation (e.g. e2e4): ";
    string moveInput;
    cin >> moveInput;
    if (moveInput == "exit") {
      exit(0);
    }
    int fromFile = moveInput[0] - 'a';
    int fromRank = 8 - (moveInput[1] - '0');
    int toFile = moveInput[2] - 'a';
    int toRank = 8 - (moveInput[3] - '0');
    Move move(fromRank, fromFile, toRank, toFile);

    if (chessBoard.makeMove(move)) {
      moveMade = true;
    } else {
      cout << "Invalid move. Try again." << endl;
    }
  } 


}

private:

 ChessBoard& chessBoard;

};

class ChessRenderer {
public:
  ChessRenderer() : window(sf::VideoMode(1000, 1000), "SFML") {}

  void init() {
    textureWPawn.loadFromFile("chess-pack/wpawn.png");
    textureWRook.loadFromFile("chess-pack/wrook.png");
    textureWKnight.loadFromFile("chess-pack/wknight.png");
    textureWBishop.loadFromFile("chess-pack/wbishop.png");
    textureWQueen.loadFromFile("chess-pack/wqueen.png");
    textureWKing.loadFromFile("chess-pack/wking.png");
    textureBPawn.loadFromFile("chess-pack/bpawn.png");
    textureBRook.loadFromFile("chess-pack/brook.png");
    textureBKnight.loadFromFile("chess-pack/bknight.png");
    textureBBishop.loadFromFile("chess-pack/bbishop.png");
    textureBQueen.loadFromFile("chess-pack/bqueen.png");
    textureBKing.loadFromFile("chess-pack/bking.png");

    textureArray[WPawn] = &textureWPawn;
    textureArray[WRook] = &textureWRook;
    textureArray[WKnight] = &textureWKnight;
    textureArray[WBishop] = &textureWBishop;
    textureArray[WQueen] = &textureWQueen;
    textureArray[WKing] = &textureWKing;
    textureArray[BPawn] = &textureBPawn;
    textureArray[BRook] = &textureBRook;
    textureArray[BKnight] = &textureBKnight;
    textureArray[BBishop] = &textureBBishop;
    textureArray[BQueen] = &textureBQueen;
    textureArray[BKing] = &textureBKing;
  }

  void render(ChessBoard& chessBoard) {
    window.clear();

    sf::RectangleShape square(sf::Vector2f(0.f, 0.f));
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        if ((i + j) % 2 == 0) {
          square.setFillColor(sf::Color(255, 206, 158)); 
        } else {
          square.setFillColor(sf::Color(209, 139, 71)); 
        }
        square.setPosition(j*0, i*0);
        window.draw(square);

        Piece piece = chessBoard.board[i][j];
        if (piece != Empty) {
          sf::Sprite sprite(*textureArray[piece]);
          sprite.setScale(0.5f, 0.5f);
          sprite.setPosition(j*100, i*50);
          window.draw(sprite);
        }
      }
    }

    window.display();
  }

private:
  sf::RenderWindow window;
  sf::Texture textureEmpty, textureWPawn, textureWRook, textureWKnight, textureWBishop, textureWQueen, textureWKing;
  sf::Texture textureBPawn, textureBRook, textureBKnight, textureBBishop, textureBQueen, textureBKing;
  sf::Texture* textureArray[13];
};

int main() {
  ChessBoard chessBoard;
  chessBoard.init();
  chessBoard.print();

  ChessRenderer chessRenderer;
  chessRenderer.init();

  ChessAI chessAI(chessBoard);

  while (true) {
    chessRenderer.render(chessBoard);
    chessAI.move();
  }

  return 0;
}

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