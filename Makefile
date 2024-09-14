.SILENT: test
test:
	g++ -O3 bf.cpp
	echo "Running hello.b"
	echo
	./a.out benches/hello.b
	echo
	echo "Running deadcodetest.b"
	echo
	./a.out benches/deadcodetest.b
	echo
	echo "Running mandel.b"
	echo
	./a.out benches/mandel.b
	echo
	echo "Running bench.b"
	./a.out benches/bench.b
	echo
	echo "Running loopremove.b"
	./a.out benches/loopremove.b
	echo
	echo "Running twinkle.b"
	./a.out benches/twinkle.b
	echo
	echo "Running hanoi.b"
	./a.out benches/hanoi.b
	echo
	echo "Running bottles.b"
	./a.out benches/bottles.b
	echo
	echo "Running long.b"
	./a.out benches/long.b
	echo
	echo "Running serptri.b"
	./a.out benches/serptri.b
	echo
	echo "All tests completed."
	echo
hanoi:
	g++ -O3 bf.cpp
	./a.out benches/hanoi.b
hanoi-d:
	g++ -O3 bf.cpp
	./a.out benches/hanoi.b -d
hello:
	g++ -O3 bf.cpp
	./a.out benches/hello.b
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