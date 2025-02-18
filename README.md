## Text Transformer

### About
    
Using text transformer cli tool, you can transformer any input file into various formats: ascii-drawing, binary, hex, numeric, utf-8. This is a hobby project to practice C++ in a random project I thought up.

**WARNING:** some translations are **_lossy_** if input file contains incompatible data for the destination formatt. A best-effort attempt is made.

### Build-Source [OUT OF DATE]
    
```
git clone git@github.com:SummerGautier/text-transformer.git
clang++ -std=c++20 main.cpp transformConfig.cpp -o ttransform.exe
# For how to use ttransform look at "Usage"
```

### Usage [OUT OF DATE]
     
 ```
 ./ttransform.exe --src my-text.txt --out destination.txt --ascii-draw
 # use an appropriate output file format [destination.bin, destination.hex, etc.]
 ```

### Testing [OUT OF DATE]

This project uses GoogleTest, a C++ framework for testing. The tests are defined under the "Targets" section in CMakeLists.txt

Step 0. Install CMake. 
On ios you can install CMake with brew:
```
brew install cmake
```

Step 1. Write Build Files Folder
```
cmake -S . -B build
```
The build files should be in /build. The '-S .' specifies the location of source files (current directiory). The -B specifies path of where to put build (i.e. /build).


Step 2. Execute Build of Tests
```
cmake --build build
```
This actually builds the tests in the /build folder with gtest.

Step 3. Run Tests
```
cd build && ctest
```