LIB := libtest.a
BIN := main
HDRS := $(wildcard *.h)
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

CC := gcc
CFLAGS := -g -Wall -O2 -L.
CXX := g++
CXXFLAGS := -g -Wall -O2
AR := ar

all: lib bin

bin: $(BIN)

lib: $(LIB)

$(BIN): $(LIB) main.c
	$(CC) $(CFLAGS) main.c -o $(BIN) -ltest -lstdc++

$(LIB): $(OBJS)
	$(AR) rvs $(LIB) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(BIN) $(LIB) $(OBJS)

runc: $(BIN)
	./$(BIN)

rungo: $(LIB)
	go run main.go

runall: runc rungo
