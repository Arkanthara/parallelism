CCPU = g++
CGPU = nvc++
CFLAGS = -g -Wall -c
OBJS = writer.o
CLIBCPU = -ltbb -std=c++17
CLIBGPU = -stdpar -std=c++17
.PHONY = clean cleanbmp

TARGET = tp7_cpu tp7_gpu

SRC_DIR = ./src
BUILD_DIR = $(shell if [ ! -d "./build" ]; then mkdir build; echo build; else echo build; fi;)

all: $(TARGET)

tp7_cpu: $(SRC_DIR)/heastSeq.cpp $(BUILD_DIR)/$(OBJS)
	$(CCPU) $^ -o $@ $(CLIBCPU)

tp7_gpu: $(SRC_DIR)/heastSeq.cpp $(BUILD_DIR)/$(OBJS)
	$(CGPU) $^ -o $@ $(CLIBGPU)

$(BUILD_DIR)/writer.o: $(SRC_DIR)/writer.cpp
	$(CCPU) $(CFLAGS) $< -o $@

clean:
	@rm -rf ./build $(TARGET)

cleanbmp:
	@rm T_*

cleanoutput:
	@rm -rf ./err ./out

cleanall:
	@rm -rf T_* ./err ./out ./build $(TARGET)
