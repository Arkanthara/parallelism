CC = mpic++
CFLAGS = -g -Wall -c
OBJS = grid.o writer.o
.PHONY = clean cleanbmp

tp3: main.cpp $(OBJS)
	$(CC) $(OBJS) main.cpp -o tp3

grid.o: grid.cpp
	$(CC) $(CFLAGS) grid.cpp -o grid.o

writer.o: writer.cpp
	$(CC) $(CFLAGS) writer.cpp -o writer.o

clean:
	rm $(OBJS) tp3

cleanbmp:
	rm T_*

cleanoutput:
	rm ./err/* ./out/*
