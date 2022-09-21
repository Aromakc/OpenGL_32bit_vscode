all: compile link run clean
compile:
	g++ -I include -c src/*.cpp src/glad.c
link:
	g++ *o -o bin/main -L lib -lglfw3dll
run:
	bin/main

clean:
	rm *o