all: ca
ca:  main.o generation.o images.o to_png.o to_pbm.o zasady_gry.o
	cc -o ca main.o generation.o images.o to_png.o to_pbm.o zasady_gry.o -lpng
ggdb:  main.o generation.o images.o to_png.o to_pbm.o
	cc -o ca main.o generation.o images.o to_png.o to_pbm.o -lpng -ggdb
main.o: main.c generation.h
	cc -c main.c 
generation.o: generation.c generation.h zasady_gry.h
	cc -c generation.c 
images.o: images.c generation.h
	cc -c images.c
to_png.o: images.h generation.h to_png.c 
	cc -c to_png.c
to_pbm.o: images.h generation.h to_pbm.c
	cc -c to_pbm.c
zasady_gry.o: zasady_gry.c
	cc -c zasady_gry.c


clean:
	rm ca *.o
