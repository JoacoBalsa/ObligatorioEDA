todo: main.o bd.o tablas.o tabla.o columnas.o
	g++ -Wall -o main main.o bd.o tablas.o tabla.o columnas.o
main.o: main.cpp
	g++ -Wall -c main.cpp
bd.o: bd.cpp bd.h
	g++ -Wall -c bd.cpp
tablas.o: tablas.cpp tablas.h
	g++ -Wall -c tablas.cpp
tabla.o: tabla.cpp tabla.h
	g++ -Wall -c tabla.cpp
columnas.o: columnas.cpp columnas.h
	g++ -Wall -c columnas.cpp
clean:
	rm -f *.o
	rm -f main
