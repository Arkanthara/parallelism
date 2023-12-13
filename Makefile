CC = g++
CFLAGS = -g -Wall
CLIB = -fopenmp
.PHONY = clean cleanbmp cleanall

CHUNK_SIZE?=1


SRC_DIR := ./src
TARGET = tp6_static tp6_dynamic

all: $(TARGET) 

tp6_static: $(SRC_DIR)/static.cpp $(SRC_DIR)/writer.cpp $(SRC_DIR)/global.hpp
	$(CC) $(CLIB) $(CFLAGS) $^ -o $@

tp6_dynamic: $(SRC_DIR)/dynamic.cpp $(SRC_DIR)/writer.cpp $(SRC_DIR)/global.hpp
	$(CC) $(CLIB) $(CFLAGS) $^ -o $@

define_chunk_size:
	sed -i 's/const int chunk_size =.*/const int chunk_size = $(CHUNK_SIZE);/g' $(SRC_DIR)/global.hpp

clean:
	@rm -rf $(TARGET)

cleanbmp:
	@rm T_*

cleanall:
	@rm -rf ./err ./out $(TARGET) T_*
