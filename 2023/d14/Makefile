main: bin/charMatrix.o src/part1.cpp
	g++ -g -o main src/part1.cpp
bin/charMatrix.o: src/charMatrix.cpp
	g++ -g -c -o bin/charMatrix.o src/charMatrix.cpp
clean:
	rm bin/*.o
	rm main