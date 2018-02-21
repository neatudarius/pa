# doar linia urmatoare e nevoie sa o modificati cu sursa pe care o compilati
SRC = skel.cpp

# configurari g++
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lm

# fisiere obiect si executabile care vor fi  generate
OBJ = $(SRC:.cpp=.o)   # OBJ = inlocuiteste extensia .cpp cu .o
EXE = $(SRC:.cpp=.exe) # OBJ = inlocuiteste extensia .cpp cu .exe


build: $(SRC) 
	$(CC) $(CFLAGS) $^ -o $(EXE) $(LDFLAGS)


run: build
	./$(EXE)


.PHONY: clean
clean:
	rm -f *.o *.exe 