# compiles the files into bitmap.exe
all: main  # compilation step names
	g++ main.o -o bitmap.exe

main: main.cpp
	g++ -c main.cpp

# removes compiled files and the executable
wipe:
	rm *.o *.exe
	echo "removed all object files and executable"


# removes only the compiled files
clean:
	rm *.o
	echo "removed all object files. (executable remains)"


# quick way to run the program via make
run:
	./bitmap.exe