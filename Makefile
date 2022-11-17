.DEFAULT: all
.PHONY: clean all

EXE=main.exe
OBJ=input.o main.o player.o render.o room.o roomgen.o
CFLAGS=-O3
LIBS=-lm -lncurses

all: $(EXE)

clean:
	rm -f $(EXE) $(OBJ)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LIBS)