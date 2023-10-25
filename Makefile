CC = mpic++
OBJS = exercises.o
CFLAGS = -c -g -Wall
.PHONY = clean, cleanoutput


tp2: main.cpp exercises.o
	$(CC) $(OBJS) main.cpp -o tp2

exercises.o: exercises.cpp
	$(CC) $(CFLAGS) exercises.cpp -o exercises.o

clean:
	rm $(OBJS) tp2

cleanoutput:
	rm ./out/* ./err/*
