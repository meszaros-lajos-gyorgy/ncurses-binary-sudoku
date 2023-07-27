all: run

build:
	g++ src/Tile.cpp src/Board.cpp src/main.cpp -std=c++17 -Wall -lncursesw -o dist/main.out

run: build
	dist/main.out

clean: dist/main.out
	rm dist/main.out
