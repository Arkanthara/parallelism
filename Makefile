CC = g++
CFLAGS = -g -Wall -c
OBJS = tp3.o
.PHONY = clean

tp3: main.cpp tp3.o
	$(CC) $(OBJS) main.cpp -o tp3

tp3.o: tp3.cpp
	$(CC) $(CFLAGS) tp3.cpp -o tp3.o

clean:
	rm $(OBJS) tp3
