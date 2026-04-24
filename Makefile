CC=clang++
CXXFLAGS=-c -Wall -O0

TARGET=start
OBJ_DIR=build

SOURCES=$(wildcard *.cpp) $(shell find core -name "*.cpp")

OBJECTS=$(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
