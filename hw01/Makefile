all: bitbybit.exe
maxmin.o: maxmin.cpp maxmin.h
	g++ -c -Wall -Werror maxmin.cpp
bitbybit.o: bitbybit.cpp maxmin.h
	g++ -c -Wall -Werror bitbybit.cpp
bitbybit.exe: bitbybit.o maxmin.o
	g++ -o bitbybit.exe bitbybit.o maxmin.o