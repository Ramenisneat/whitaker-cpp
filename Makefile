.PHONY: all run clean

all:
	cmake -S . -B build && cmake --build build

run: all
	./build/whitaker

clean:
	rm -rf build
