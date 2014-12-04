gomoku: main.o humanplayer.o computerplayer.o chessboard.o
	g++ -Wall -o gomoku main.o humanplayer.o computerplayer.o chessboard.o player.o

main.o: main.cpp humanplayer.h computerplayer.h chessboard.h
	g++ -Wall -c main.cpp

chessboard.o: chessboard.cpp chessboard.h
	g++ -Wall -c chessboard.cpp

player.o: player.cpp player.h chessboard.h
	g++ -Wall -c player.cpp

humanplayer.o: humanplayer.cpp humanplayer.h player.h
	g++ -Wall -c humanplayer.cpp

computerplayer.o: player.o computerplayer.cpp computerplayer.h player.h
	g++ -Wall -c computerplayer.cpp

clean:
	rm -f gomoku *.o
