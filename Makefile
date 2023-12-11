CC = g++
CFLAGS = -g -Wall
CLIB = -fopenmp
.PHONY = clean cleanbmp cleanall

SRC_DIR := ./src
TARGET = tp6_static tp6_dynamic

all: $(TARGET) 

tp6_static: $(SRC_DIR)/static.cpp $(SRC_DIR)/writer.cpp $(SRC_DIR)/global.hpp
	$(CC) $(CLIB) $(CFLAGS) $^ -o $@

tp6_dynamic: $(SRC_DIR)/dynamic.cpp $(SRC_DIR)/writer.cpp $(SRC_DIR)/global.hpp
	$(CC) $(CLIB) $(CFLAGS) $^ -o $@

clean:
	@rm -rf $(TARGET)

cleanbmp:
	@rm T_*

cleanall:
	@rm -rf ./err ./out $(TARGET) T_*
