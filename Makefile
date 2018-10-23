## TP 0 - Algoritmos y Programacion II (95.12)##

##Facultad de Ingenieria##
##Universidad de Buenos Aires##

CC = g++ -Wall -ansi -pedantic -g -std=c++11

all: tp0 clean

tp0: main.o cmdline.o isonlydigit.o Array.h sensor.h sensornet.h query.h segment_tree.h data.h
	$(CC) -o tp0 main.o cmdline.o

main.o: main.cpp cmdline.h isonlydigit.h sensornet.h sensor.h query.h data.h Array.h segment_tree.h 
	$(CC) -o main.o -c main.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CC) -o cmdline.o -c cmdline.cpp

isonlydigit.o: isonlydigit.cpp isonlydigit.h
	$(CC) -o isonlydigit.o -c isonlydigit.cpp

clean:
	rm *.o