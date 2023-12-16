CC = g++
CFLAGS = -g -Wall -c
OBJS = writer.o
CLIBS = -ltbb -std=c++17
.PHONY = clean cleanbmp

TARGET = tp7

SRC_DIR = ./src
BUILD_DIR = $(shell if [ ! -d "./build" ]; then mkdir build; echo build; else echo build; fi;)

all: $(TARGET)

$(TARGET): $(SRC_DIR)/heastSeq.cpp $(BUILD_DIR)/$(OBJS)
	$(CC) $^ -o $@ $(CLIBS) 

$(BUILD_DIR)/writer.o: $(SRC_DIR)/writer.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf ./build $(TARGET)

cleanbmp:
	@rm T_*

cleanoutput:
	@rm ./err/* ./out/*

cleanall:
	@rm -rf T_* ./err ./out ./build $(TARGET)
