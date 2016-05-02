EXEC=main
LIBFRACTAL_DIR = libfractal

all : $(EXEC)

lib :
	cd libfractal && $(MAKE)

$(EXEC) : main.o libfractal/libfractal.a
	gcc -o main main.o libfractal/libfractal.a -lpthread -lSDL

main.o : main.c
	gcc -c main.c

clean :
	rm -rf *.o
	rm -rf libfractal/*.o
	rm -rf test
	rm -rf $(EXEC)
	rm -rf *.bmp
