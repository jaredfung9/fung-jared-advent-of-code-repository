main: main.cpp build/dialSolver.o
	g++ -g -o main main.cpp build/*.o

build/dialSolver.o: dialSolver/dialSolver.cpp
	g++ -c -g -o build/dialSolver.o dialSolver/dialSolver.cpp

test: tests/test.cpp build/dialSolver.o
	g++ -g -o test tests/test.cpp build/dialSolver.o
	./test