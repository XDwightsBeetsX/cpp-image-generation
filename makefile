# Compiles the files into an executable in stages
# 1. Compile user methods/classes (use -c)
# 2. Compile main.cpp
# 3. Link the compiled object files

all: operations bitmap main
	g++ bin/main.o bin/bitmap.o bin/operations.o -o bin/main.exe

operations:
	g++ src/operations.cpp -c -o bin/operations.o

bitmap:
	g++ src/bitmap.cpp -c -o bin/bitmap.o

main: main.cpp
	g++ main.cpp -c -o bin/main.o


# removes only the compiled files
clean:
	rm bin/*.o
	echo "removed all object files. (executable remains)"


# removes compiled files and the executable
wipe:
	make clean
	rm bin/*.exe
	echo "removed all object files and executable"


# quick way to run the program via make
run:
	./bin/main.exe
