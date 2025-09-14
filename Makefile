all: run

build:
	g++ \
		src/Random.cpp \
		src/Text.cpp \
		src/pages/Page.cpp \
		src/pages/Home.cpp \
		src/pages/GenerateBoard.cpp \
		src/board/Tile.cpp \
		src/board/Row.cpp \
		src/board/Board.cpp \
		src/App.cpp \
		src/main.cpp \
		-std=c++17 \
		-Wall \
		-Wextra \
		-pedantic \
		-lncursesw \
		-o dist/ncurses-binary-sudoku.out

run: build
	dist/ncurses-binary-sudoku.out

clean: dist/ncurses-binary-sudoku.out
	rm dist/ncurses-binary-sudoku.out
