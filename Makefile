# IDIR = ../include
# CC=g++
# CFLAGS=-I$(IDIR) -std=c++17 -g

# ODIR=../src

# .PHONY: all

# _OBJ = maxmeandpCalculator.o greedy.o graph.o main.o
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


# all: maxmeanDP

# $(ODIR)/maxmeandpCalculator.o: $(ODIR)/MaxmeandpCalculator.cpp $(IDIR)/MaxmeandpCalculator.hpp $(IDIR)/Maxmeandp.hpp $(IDIR)/Greedy.hpp $(IDIR)/Graph.hpp
# 	$(CC) -c -o $@ $< $(CFLAGS)

# $(ODIR)/greedy.o: $(ODIR)/Greedy.cpp $(IDIR)/Maxmeandp.hpp $(IDIR)/Greedy.hpp $(IDIR)/Graph.hpp
# 	$(CC) -c -o $@ $< $(CFLAGS)

# $(ODIR)/graph.o: $(ODIR)/Graph.cpp $(IDIR)/Graph.hpp
# 	$(CC) -c -o $@ $< $(CFLAGS)

# $(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/Graph.hpp
# 	$(CC) -c -o $@ $< $(CFLAGS)


# maxmeanDP: $(OBJ)
# 	$(CC)  -o $@ $^ $(CFLAGS)


# .PHONY: clean

# clean:
# 		rm -f $(ODIR)/*.o ./P1


CXX          := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN        := bin
SRC        := src
INCLUDE    := include
LIB        := lib

LIBRARIES    :=
EXECUTABLE    := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*