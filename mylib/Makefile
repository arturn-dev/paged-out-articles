main: mylib.cpp
	mkdir -p build
	g++ -shared -fPIC mylib.cpp -I ./inc -o ./build/libmylib.so

install: main
	sudo cp ./build/libmylib.so /usr/local/lib/

clean:
	rm -rf ./build/*