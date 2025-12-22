all: part1 part2

part1: part1.cpp Machine/Machine.cpp
	g++ -g -o part1 part1.cpp Machine/Machine.cpp -Wall -Werror

part2: part2.cpp Machine/Machine.cpp
	g++ -g -o part2 part2.cpp Machine/Machine.cpp -Wall -Werror
run:
	./part1 inputs/demo.txt
	./part2 inputs/demo.txt
clean:
	rm part1
	rm part2