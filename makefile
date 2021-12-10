# compiles the files into bitmap.exe
all: FileInfo bitmap main  # compilation step names
	g++ main.o bitmap.o FileInfo.o -o bitmap.exe

main: main.cpp bitmap.h FileInfo.h
	g++ -c main.cpp
	
bitmap: bitmap.cpp bitmap.h FileInfo.h
	g++ -c bitmap.cpp

FileInfo: FileInfo.cpp FileInfo.h
	g++ -c FileInfo.cpp


# removes compiled files and the executable
wipe:
	rm *.o *.exe
	echo "removed all object files and executable"


# removes only the compiled files
clean:
	rm *.o
	echo "removed all object files. (executable remains)"


# quick way to run the program via make
run: bitmap
	./bitmap.exe