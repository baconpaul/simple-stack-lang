bin:
	mkdir -p bin

bin/interpret:	bin example/interpret.cpp src/simple-stack-lang.hpp
	clang -std=c++14 -O -I src -o bin/interpret example/interpret.cpp -lc++

run:	bin/interpret
	cat example/mul.smsl | ./bin/interpret

%.run:	bin/interpret
	cat example/$*.smsl | bin/interpret

clean:
	rm -rf bin
