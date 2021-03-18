all: ca
ca:  main.o generation.o images.o to_png.o
	cc -o ca main.o generation.o images.o to_png.o -lpng
main.o: main.c generation.h
	cc -c main.c 
generation.o: generation.c generation.h images.h
	cc -c generation.c
images.o: images.c generation.h
	cc -c images.c
to_png.o: images.h generation.h to_png.c 
	cc -c to_png.c

clean:
	rm ca *.o
