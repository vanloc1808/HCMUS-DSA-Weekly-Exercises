CXX = g++
CXXFLAGS = -g -O3 -std=c++17

BASE_DIR = $(shell pwd)
OBJ_DIR = obj
BUILD_DIR = build

SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
BUILD_FILES = $(patsubst %.cpp, $(BUILD_DIR)/%, $(SRC_FILES))

all: $(BUILD_FILES)

$(BUILD_DIR)/%: $(OBJ_DIR)/%.o
	$(CXX) -o $@ $<

$(OBJ_DIR)/%.o: $(BASE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILD_FILES) 
	rm -f $(OBJ_FILES) 

