all: run

build:
	g++ src/Tile.cpp src/board.cpp src/main.cpp -lncursesw -o dist/main.out

run: build
	dist/main.out

clean: dist/main.out
	rm dist/main.out
