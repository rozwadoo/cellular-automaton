all: ca
ca:  main.o generation.o images.o
	cc -o ca main.o generation.o images.o
main.o: main.c generation.h
	cc -c main.c 
generation.o: generation.c generation.h images.h
	cc -c generation.c
images.o: images.c generation.h
	cc -c images.c
clean:
	rm ca *.o
