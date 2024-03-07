bin/dorito: obj/dorito.o obj/cpu.o
	clang -o bin/dorito obj/dorito.o obj/cpu.o
obj/dorito.o: src/dorito.c src/dorito.h
	clang -c src/dorito.c -o obj/dorito.o
obj/cpu.o: src/cpu.c src/cpu.h
	clang -c src/cpu.c -o obj/cpu.o
