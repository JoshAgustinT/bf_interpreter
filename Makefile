a5:
	g++ bf.cpp -g
	./a.out nestedloops.b -p
test:
	g++ -O3 bf.cpp
	time ./a.out benches/hello.b -p
	time ./a.out benches/deadcodetest.b -p
	time ./a.out benches/mandel.b -p
	time ./a.out benches/bench.b -p
	time ./a.out benches/loopremove.b -p
	time ./a.out benches/twinkle.b -p
	time ./a.out benches/hanoi.b -p
	time ./a.out benches/bottles.b -p
	time ./a.out benches/long.b -p
	time ./a.out benches/serptri.b -p
	@echo "All tests completed."
	@echo
hanoi:
	g++ -O3 bf.cpp 
	./a.out benches/hanoi.b -p 
hanoi-d:
	g++ -O3 bf.cpp
	./a.out benches/hanoi.b -d
hello:
	g++ -O3 bf.cpp 
	./a.out benches/hello.b -p
hello-d:
	g++ -O3 bf.cpp
	./a.out benches/hello.b -d

compile:
	g++ -O3 bf.cpp

test-nolong:
	g++ -O3 bf.cpp
	./a.out benches/hello.b
	./a.out benches/deadcodetest.b
	./a.out benches/mandel.b
	./a.out benches/bench.b
	./a.out benches/loopremove.b
	./a.out benches/twinkle.b
	./a.out benches/hanoi.b
	./a.out benches/bottles.b
	./a.out benches/serptri.b
