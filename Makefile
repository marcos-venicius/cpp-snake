build:
	mkdir -p dist

	g++ -Wall -std=c++11 src/main.cpp -o program -lglut -lGLU -lGL

clean:
	rm program

run:
	./program