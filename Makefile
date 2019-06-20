bin:
	mkdir -p bin

bin/interpret:	bin example/interpret.cpp src/simple-stack-lang.hpp
	clang -std=c++14 -O -I src -o bin/interpret example/interpret.cpp -lc++


%.bf.run:	bin/interpret
	cat example/bf/$*.bf | bin/interpret --bf

%.ls.run:	bin/interpret
	cat example/ls/$*.lssl | bin/interpret --ls

clean:
	rm -rf bin
