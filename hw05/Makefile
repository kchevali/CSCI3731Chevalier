all: main.exe

img.o: img.cpp img.h
	g++ -c -Wall -Werror img.cpp -I usr/local/include/jpeglib.h
menu.o: menu.cpp menu.h
	g++ -c -Wall -Werror menu.cpp
main.o: main.cpp img.h menu.h
	g++ -c -Wall -Werror main.cpp
main.exe: main.o img.o menu.o
	g++ -o main.exe main.o img.o menu.o -L /usr/local/lib -ljpeg