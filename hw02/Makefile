all: runCount.exe runSwap.exe

runCount.o: runCount.cpp
	g++ -c -Wall -Werror runCount.cpp
runCount.exe: runCount.o
	g++ -o runCount.exe runCount.o

swap.o: swap.cpp swap.h
	g++ -c -Wall -Werror swap.cpp
runSwap.o: runSwap.cpp swap.h
	g++ -c -Wall -Werror runSwap.cpp
runSwap.exe: runSwap.o swap.o
	g++ -o runSwap.exe runSwap.o swap.o