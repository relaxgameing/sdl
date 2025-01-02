
libsFlag= `sdl2-config --libs`
cflags = `sdl2-config --cflags`
exeName = staticRayTracing

all:
	clear
	gcc main.c -o $(exeName) $(libsFlag) $(cflags)
	./$(exeName)

clean:
	rm $(exeName)