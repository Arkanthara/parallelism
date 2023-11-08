CC = mpic++
CFLAGS = -g -Wall -c
OBJS = Grid.o writer.o
.PHONY = clean cleanbmp

tp3: main.cpp $(OBJS)
	$(CC) $(OBJS) main.cpp -o tp3

Grid.o: Grid.cpp
	$(CC) $(CFLAGS) Grid.cpp -o Grid.o

writer.o: writer.cpp
	$(CC) $(CFLAGS) writer.cpp -o writer.o

clean:
	rm $(OBJS) tp3

cleanbmp:
	rm T_*

cleanoutput:
	rm ./err/* ./out/*
