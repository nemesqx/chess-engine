CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = Source.cpp board.h opponentAI.h piece.h renderer.h util.h
OBJS = Source.o
TARGET = chess-engine.out
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

Source.o: Source.cpp board.h opponentAI.h piece.h renderer.h util.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
