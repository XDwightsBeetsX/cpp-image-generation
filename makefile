# compiles the files into bitmap.exe
all: main  # compilation step names
	g++ main.o -o bitmap.exe

main: main.cpp
	g++ -c main.cpp -o main.o

# removes only the compiled files
clean:
	rm *.o
	echo "removed all object files. (executable remains)"

# removes compiled files and the executable
wipe:
	make clean
	rm *.exe
	echo "removed all object files and executable"

# quick way to run the program via make
run:
	./bitmap.exe
