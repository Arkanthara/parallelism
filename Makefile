CC = g++
CFLAGS = -g -Wall -c
OBJS = Grid.o write.o
.PHONY = clean cleanbmp

tp3: main.cpp $(OBJS)
	$(CC) $(OBJS) main.cpp -o tp3

Grid.o: Grid.cpp
	$(CC) $(CFLAGS) Grid.cpp -o Grid.o

write.o: write.cpp
	$(CC) $(CFLAGS) write.cpp -o write.o

tp3.o: tp3.cpp
	$(CC) $(CFLAGS) tp3.cpp -o tp3.o

clean:
	rm $(OBJS) tp3

cleanbmp:
	rm T_*
