#define CHESS_AI_H

// the ai for now is the hooman 

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