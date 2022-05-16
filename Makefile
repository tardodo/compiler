CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(EXECUTABLE)

run: clean all
    clear
    ./$(EXECUTABLE)

$(EXECUTABLE): *.cpp
    $(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

clean:
    -rm $(BIN)/*