CC = mpic++
OBJS = exercises.o
CFLAGS = -c -g -Wall
.PHONY = clean


tp2: main.cpp exercises.o
	$(CC) $(OBJS) main.cpp -o tp2

exercises.o: exercises.cpp
	$(CC) $(CFLAGS) exercises.cpp -o exercises.o

clean:
	rm $(OBJS) tp2

1: tp2
	mpirun tp2 1

2: tp2
	mpirun tp2 2

3: tp2
	mpirun tp2 3
