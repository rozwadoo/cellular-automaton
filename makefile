all: ca
test1: ca test/test1
	./ca -n 30 -p test/test1 -w res1 -g 30 -f g_test1_ -s 0 -o 0 -b 0 
ship: ca test/ship
	./ca -n 50 -p test/ship -w res_ship -g 50 -f g_ship -s 0 -o 0 -b 0 
pw: ca test/pinwheel
	./ca -n 30 -p test/pinwheel -w res_pw -g 30 -f g_pw -s 0 -o 0 -b 0 
pd: ca test/pentadecathlon
	./ca -n 30 -p test/pentadecathlon -w res_pd -g 30 -f g_pd -s 0 -o 0 -b 0 
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
