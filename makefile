LIBDIR = ./libfdr
INCLUDE = -I ./include
LIBFDRINCLUDE = -I $(LIBDIR)/include
CFLAGS = $(INCLUDE) $(LIBFDRINCLUDE)
LIBS = $(LIBDIR)/objs/libfdr.a

CC = gcc
EXECUTABLES = \
    kripto \

all: $(EXECUTABLES)

clean:
	rm -rf $(RM) $(OBJ) $(EXE)

kripto: 
	gcc -I ./include -o ./lib/dllist.o -c ./src/dllist.c
	gcc -I ./include -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include -o ./lib/jrb.o -c ./src/jrb.c
	gcc -I ./include -o ./bin/a.out ./lib/dllist.o ./lib/fields.o ./lib/jrb.o ./lib/jval.o ./src/main.c

