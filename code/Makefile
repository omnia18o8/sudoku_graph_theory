# File: Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = sudoku
SOURCES = main.cpp load_board.cpp neighbours.cpp palettes.cpp propagation.cpp rules.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp sudoku.h
load_board.o: load_board.cpp sudoku.h
neighbours.o: neighbours.cpp sudoku.h
propagation.o: propagation.cpp sudoku.h
rules.o: rules.cpp sudoku.h
palettes.o: palettes.cpp sudoku.h

clean:
	rm -f $(OBJECTS) $(TARGET)