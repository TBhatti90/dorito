OBJS = src/*.c

CC = clang

COMPILER_FLAGS = -Wall -Wextra -ggdb3

LINKER_FLAGS = -lSDL2

OBJ_NAME = dorito

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)




#bin/dorito: obj/dorito.o obj/cpu.o
#	clang -o bin/dorito obj/dorito.o obj/cpu.o -Wall -Wextra -ggdb3 -lSDL2
#obj/dorito.o: src/dorito.c src/dorito.h
#	clang -c src/dorito.c -o obj/dorito.o -Wall -Wextra -ggdb3 -lSDL2
#obj/cpu.o: src/cpu.c src/cpu.h
#	clang -c src/cpu.c -o obj/cpu.o -Wall -Wextra -ggdb3 -lSDL2
