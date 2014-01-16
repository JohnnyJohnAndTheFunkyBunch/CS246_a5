CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = quadris
OBJECTS = main.o block.o iblock.o lblock.o tblock.o jblock.o oblock.o sblock.o zblock.o board.o scoreboard.o level.o level0.o level1.o level2.o level3.o level4.o textdisplay.o point.o game.o blockgraveyard.o window.o inputhandler.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -L/usr/X11R6/lib -lX11 -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
