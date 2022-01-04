# Compiles the files into an executable in stages
# 1. Compile user methods/classes (use -c)
# 2. Compile main.cpp
# 3. Link the compiled object files

all: Image main
	g++ bin/*.o -o bin/main.exe

Image:
	g++ src/Image.cpp -c -o bin/Image.o

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
