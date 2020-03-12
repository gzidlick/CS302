CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
PROGRAMS=	dijkstras	generate-map

all:		dijkstras	generate-map

dijkstras:	dijkstras.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

generate-map: generate-map.cpp
	$(CXX) $(CXXFLAGS) -o generate-map generate-map.cpp

.PHONY:		test test-output test-memory clean run

clean:
	rm -f $(PROGRAMS)

test:		test-output test-memory

test-output:	dijkstras
	@echo Testing output 0...
	@cat data/input0.txt <(./dijkstras < data/input0.txt) | ~tmn678/public/checkproj4 data/output0.txt
	@echo Testing output 1...
	@cat data/input1.txt <(./dijkstras < data/input1.txt) | ~tmn678/public/checkproj4 data/output1.txt
	@echo Testing output 2...
	@cat data/input2.txt <(./dijkstras < data/input2.txt) | ~tmn678/public/checkproj4 data/output2.txt
	@echo Testing output 3...
	@cat data/input3.txt <(./dijkstras < data/input3.txt) | ~tmn678/public/checkproj4 data/output3.txt

test-memory:	dijkstras
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./dijkstras < data/input1.txt 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

run: dijkstras
	./generate-map
	time ./dijkstras < map.txt
