# cpp-image-generation

Programs to make image files using c++

- [cpp-image-generation](#cpp-image-generation)
  - [Download/Install](#downloadinstall)
  - [Usage](#usage)

## Download/Install

- download the code [here](https://github.com/XDwightsBeetsX/cpp-image-generation)
- or via command line:

    ```shell
    git clone https://github.com/XDwightsBeetsX/cpp-image-generation.git
    ```

## Usage

1. Compile the object files and generate an executable with **Make**

    ```shell
    > make all
    g++ -c FileInfo.cpp
    g++ -c bitmap.cpp
    g++ -c main.cpp
    g++ main.o bitmap.o FileInfo.o -o bitmap.exe
    ```

    Distributions of *Make* can be found at [**sourceforge**](http://gnuwin32.sourceforge.net/packages/make.htm) or through [**MinGW**](https://www.mingw-w64.org/downloads/)

2. Run the program

    ```shell
    > make run
    g++ -c bitmap.cpp
    ./bitmap.exe
    running bitmap generator...
    done.
    ```

3. Open the output file!
