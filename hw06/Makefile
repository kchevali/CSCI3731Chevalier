all: main.exe

image.o: image.cpp image.h
	g++ -std=c++11 -c -Wall -Werror image.cpp -I usr/local/include/jpeglib.h
angle.o: angle.cpp angle.h
	g++ -std=c++11 -c -Wall -Werror angle.cpp
shape.o: shape.cpp shape.h image.h angle.h
	g++ -std=c++11 -c -Wall -Werror shape.cpp
main.o: main.cpp image.h angle.h shape.h
	g++ -std=c++11 -c -Wall -Werror main.cpp
main.exe: main.o image.o angle.o shape.o
	g++ -std=c++11 -o main.exe main.o image.o angle.o shape.o -L /usr/local/lib -ljpeg