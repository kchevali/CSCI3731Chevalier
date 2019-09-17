all: main.exe

ppm.o: ppm.cpp ppm.h
	g++ -c -Wall -Werror ppm.cpp
main.o: main.cpp ppm.h
	g++ -c -Wall -Werror main.cpp
main.exe: main.o ppm.o
	g++ -o main.exe main.o ppm.o