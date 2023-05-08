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