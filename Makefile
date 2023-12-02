CC = g++
CFLAGS = -g -Wall
CLIB = -fopenmp
.PHONY = clean cleanbmp

SRC_DIR := ./src


TARGET = tp5

all: $(TARGET)

$(TARGET): $(SRC_DIR)/main.cpp $(SRC_DIR)/writer.cpp
	$(CC) $(CLIB) $(CFLAGS) $(wildcard $(SRC_DIR)/*.cpp) -o $@

clean:
	@rm -rf $(TARGET)

cleanbmp:
	@rm T_*
