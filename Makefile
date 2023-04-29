CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE = chess-engine.out
SOURCE_FILES = Source.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $^ -o $@ $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECT_FILES)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
