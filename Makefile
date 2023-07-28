all: run

build:
	g++ -std=c++17 -Wall -Wextra -pedantic src/Random.cpp src/Tile.cpp src/Board.cpp src/main.cpp -lncursesw -o dist/main.out

run: build
	dist/main.out

clean: dist/main.out
	rm dist/main.out
