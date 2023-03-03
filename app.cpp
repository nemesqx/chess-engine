#include <iostream>
#include <vector>

using namespace std;

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

PieceType pieceType(Piece piece) { 
  if (piece == WKing || piece == WKnight || piece == WRook || piece == WPawn || piece == WQueen || piece == WBishop) {
    return White;
  } else if (piece == BKing || piece == BKnight || piece == BRook || piece == BPawn || piece == BQueen || piece == BBishop) {
    return Black; 
  } else {
    return EmptyPieceType;
  }
}

bool canCapture(Piece piece, Piece toCapture) { 
  if (pieceType(piece) == White && (pieceType(toCapture) == Black || pieceType(toCapture) == EmptyPieceType)) {
    return true;
  } else if (pieceType(piece) == Black && (pieceType(toCapture) == White || pieceType(toCapture) == EmptyPieceType)) {
    return true;
  } else {
    return false;
  }
}

bool canMove2Squares(Square square) {
  Piece piece = getPiece(square);
  if (piece == WPawn) {
    if (square.row == 2) {
      return true;
    } else {
      return false;
    }
  } else if (piece == BPawn) {
    if (square.row == 7) {
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

        case WPawn: 
        std::cout << dirX << " , " << dirY;
          if (dirX == 1 && dirY == 0 && moveToPiece == Empty) {
             return true;
          } 
        
          else if (dirX == 0 && dirY == 2) {
             Square squareToCheck;
             squareToCheck.row = fromSquare.row;
             squareToCheck.col = fromSquare.col + 2;

             Square squareToCheck2;
             squareToCheck.row = fromSquare.row;
             squareToCheck.col = fromSquare.col + 2;

             if (canMove2Squares(fromSquare) && getPiece(squareToCheck) == Empty && getPiece(squareToCheck2) == Empty) { 
                 std::cout << "canMove";
                 return true;
              }
        }

        else if (dirX == 1 && dirY == 1 || dirX == 1 && dirY == -1 && moveToPiece != Empty && canCapture(piece, moveToPiece)) {
          return true;
        } 

        else {
          return false;
        }
        
        break;
      }
      std::cout << "got here";
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
}
 
