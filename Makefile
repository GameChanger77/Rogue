.DEFAULT: all
.PHONY: clean all

EXE=main.exe
OBJ=input.o main.o player.o render.o room.o roomgen.o
CFLAGS=-O3
LIBS=-lm -lncurses

all: $(EXE)

clean:
	rm -f $(EXE) $(OBJ) roomgen-index.h

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LIBS)

roomgen.o: roomgen-index.h

roomgen-index.h: levels.txt
	echo "#define NUM_EASY" $(shell cat levels.txt | grep e | wc -l) > roomgen-index.h
	echo "#define NUM_MEDIUM" $(shell cat levels.txt | grep m | wc -l) >> roomgen-index.h
	echo "#define NUM_HARD" $(shell cat levels.txt | grep h | wc -l) >> roomgen-index.h
	echo "#define NUM_LEVELS NUM_EASY + NUM_MEDIUM + NUM_HARD" >> roomgen-index.h
