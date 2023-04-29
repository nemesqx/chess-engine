#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

bool debug_mode = false;

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

  void render() { 
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.clear();
    window.draw(shape);
    window.display();
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

int main() {
  ChessBoard chessBoard;
  chessBoard.init();
  chessBoard.print();

  ChessAI chessAI(chessBoard);

  

    while (true) {
    chessAI.move();
    chessBoard.print(); }

  return 0;
}
