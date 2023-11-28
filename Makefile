CC = g++
CFLAGS = -g -Wall -fopenmp
.PHONY = clean

BUILD_DIR := $(shell mkdir build; echo build)
SRC_DIR := ./src

SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = tp4

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	@rm $(BUILD_DIR)/*
