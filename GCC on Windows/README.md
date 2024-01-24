# Setting up GCC on windows

## To install GCC
- Install MSYS2 from https://www.msys2.org/
- Update MSYS2 by running the following commands in MSYS2 MSYS shell:
  ```
  pacman -Syu
  pacman -Su
  ```
  
- Install GCC (C and C++ compiler) by running the following commands:
  - For 64-bit GCC (on MSYS2 MINGW64 shell):
    ```
    pacman -S mingw-w64-x86_64-gcc
    ```
  - For 32-bit GCC (on MSYS2 MINGW32 shell):
    ```
    pacman -S mingw-w64-i686-gcc
    ```
- Add `C:\msys64\mingw64\bin` and `C:\msys64\mingw32\bin` to Windows path

## To run a C++ code using GCC
- Open MSYS2 MINGW64 (or MSYS2 MINGW32 for 32-bit app) and navigate to the folder containing the C++ file
  - For example if the C++ file is `C:/Work/Programs/hello.cpp`, navigate in MSYS2 MINGW64 as:
    ```
    cd /c/Work/Programs
    ```
- Build the file using g++ as follows
  ```
  g++ -static-libgcc -static-libstdc++ <fileName.cpp>
  ```
  - For example to build a file `hello.cpp` using C++ 17
    ```
    g++ -static-libgcc -static-libstdc++ --std=c++17 hello.cpp
    ```
- Run the executable as
  ```
  ./a.exe
  ```

## Note:
Add flags `-static-libgcc` and `-static-libstdc++` so that the executable can be run without a need of the libgcc and libstdc++ DLLs.

