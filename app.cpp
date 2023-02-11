#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8;

enum Piece {
  Empty,
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King
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
      board[1][i] = Pawn;
      board[6][i] = Pawn;
    }
    board[0][0] = board[0][7] = Rook;
    board[7][0] = board[7][7] = Rook;
    board[0][1] = board[0][6] = Knight;
    board[7][1] = board[7][6] = Knight;
    board[0][2] = board[0][5] = Bishop;
    board[7][2] = board[7][5] = Bishop;
    board[0][3] = Queen;
    board[7][3] = Queen;
    board[0][4] = King;
    board[7][4] = King;
  }

  void print() {
    cout << "  A B C D E F G H" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
      cout << 8 - i << " ";
      for (int j = 0; j < BOARD_SIZE; j++) {
        switch (board[i][j]) {
          case Empty:
            cout << "- ";
            break;
          case Pawn:
            cout << "P ";
            break;
          case Rook:
            cout << "R ";
            break;
          case Knight:
            cout << "N ";
            break;
          case Bishop:
            cout << "B ";
            break;
          case Queen:
            cout << "Q ";
            break;
          case King:
            cout << "K ";
            break;
        }
      }
      cout << endl;
    }
  }

bool isValidMove(Move move) {
      // logic for validating a move
      return true; // for now, just return true
    }
    
  void makeMove(Move move) {
      board[move.to_row][move.to_col] = board[move.from_row][move.from_col];
      board[move.from_row][move.from_col] = Empty;
    }


  Piece board[BOARD_SIZE][BOARD_SIZE];
};

class ChessAI {
public:

  ChessAI(ChessBoard& chessBoard) : chessBoard(chessBoard) {}

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
    if (isValidMove(move)) {
      chessBoard.makeMove(move);
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
  chessAI.move();
  system("cls");
  chessBoard.print();
}
 
