main.out: build/Grid.o main.cpp
	g++ -g -o main.out main.cpp build/Grid.o

test: testGrid.out
	./testGrid.out
testGrid.out: build/Grid.o testGrid.cpp
	g++ -g -o testGrid.out build/Grid.o testGrid.cpp

build/Grid.o: Grid.cpp
	g++ -g -c -o build/Grid.o Grid.cpp
clean:
	rm *.out
	rm build/*.o