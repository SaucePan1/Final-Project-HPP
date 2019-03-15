#-I/opt/X11/include -L/opt/X11/lib -lX11
#LDFLAGS=-I/usr/X11R6/include -L/usr/X11R6/lib -lX11
LDFLAGS = -I/opt/X11/include -L/opt/X11/lib -lX11
CFLAGS= -w

life: life_graphics.c
	gcc -Wall -o life life_graphics.c graphics/graphics.c $(LDFLAGS)

generate_with_01:${argument}
	@gcc $(CFLAGS) -O1 -o first_optimization ${argument} graphics/graphics.c $(LDFLAGS)

generate_with_02:${argument}
	@gcc $(CFLAGS) -O2 -o second_optimization ${argument} graphics/graphics.c $(LDFLAGS)

generate_with_03:${argument}
	@gcc $(CFLAGS) -O3 -o third_optimization ${argument} graphics/graphics.c $(LDFLAGS)

generate_with_ffast_math:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -o ffast_math ${argument} graphics/graphics.c $(LDFLAGS)

generate_with_ffast_native:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -march=native -o ffast_native ${argument} graphics/graphics.c $(LDFLAGS)

generate_with_ffast_msse4:${argument}
	@gcc $(CFLAGS) -O3 -ffast-math -msse4.2 -o ffast_native ${argument} graphics/graphics.c $(LDFLAGS)


clean:
	@rm -f first_optimization
	@rm -f second_optimization
	@rm -f third_optimization
	@rm -f ffast_math
	@rm -f ffast_native
	@rm time.txt
