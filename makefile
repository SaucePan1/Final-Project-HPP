LDFLAGS=-I/usr/X11R6/include -L/usr/X11R6/lib -lX11

life: life.c
	gcc -Wall -o life life.c
life_graphics: life_graphics.c
	gcc -Wall -o life life_graphics.c graphics/graphics.c $(LDFLAGS)
clean:
	rm life life.o
