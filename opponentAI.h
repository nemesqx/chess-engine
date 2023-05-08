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