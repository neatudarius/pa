# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -Werror=vla

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:%.cpp=%.o)
TARGETS=$(OBJS:%.o=%)

build: $(OBJS) $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJS)
