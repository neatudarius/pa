SRC =  main.cpp

CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=.exe)

build:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(EXE) 

run: build
	time ./$(EXE) && echo "pwp" &> /dev/null

.PHONY: clean
clean:
	rm -f *.o *.exe *.out