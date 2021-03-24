all: ca

test1: ca test/test1
	./ca -n 70 -p test/test1 -w res1 -g 70 -f g_test1_ -s 0 -o 0 -b 0 

ship: ca test/ship
	./ca -n 100 -p test/ship -w res_ship -g 100 -f g_ship -s 0 -o 0 -b 2 

pw: ca test/pinwheel
	./ca -n 30 -p test/pinwheel -w res_pw -g 30 -f g_pw -s 0 -o 1 -b 0 

square: ca test/square
	./ca -n 30 -p test/square -w res_square -g 30 -f g_square -s 1 -o 0 -b 0 

pd0: ca test/pentadecathlon
	./ca -n 30 -p test/pentadecathlon -w res_pd -g 30 -f g_pd -s 0 -o 0 -b 0 

pd1: ca test/pentadecathlon
	./ca -n 30 -p test/pentadecathlon -w res_pd1 -g 30 -f g_pd1 -s 0 -o 0 -b 1 

clear: 
	rm -r Stworzone_pliki

ca:  main.o generation.o images.o to_png.o to_pbm.o zasady_gry.o
	cc -o ca main.o generation.o images.o to_png.o to_pbm.o zasady_gry.o -lpng

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
zasady_gry.o: zasady_gry.c generation.h
	cc -c zasady_gry.c

clean:
	rm ca *.o
