# Using a C++ library in a Python script

This is the full code, which fragments were presented in my article, that I wrote for one of "Paged Out!" issues, freely accessible here: (yet to be published).

### Structure
./mylib - Code for a library being wrapped \
./mylib_wrappers - Code for library wrappers and test script

### Build
Build library code. Makefile script will install the library to "/usr/local/lib":
```sh
cd mylib
make install
```
If you don't want to polute your system directories you can also use just "make", but you will need to e.g. set "LD_LIBRARY_PATH" to the absolute path of the "build" directory, so it is possible to link it. \
Build the wrapper and install it:
```sh
cd mylib_wrappers
sudo python3 setup.py install
```
Run the test script to check if it works:
```sh
cd mylib_wrappers/py
python3 script.py
```
If you encounter a following error:
`ImportError: libmylib.so: cannot open shared object file: No such file or directory
` you probably need to properly set the "LD_LIBRARY_PATH" environment variable to the (preferably absolute) path to "./mylib/build" (if you used "make") or "/usr/local/lib" (if you used "make install").

### Dependencies
- g++
- Python development package (python3-devel)

### Tested with
- g++ 9.2.1
- Python 3.6.9 and 3.7.7