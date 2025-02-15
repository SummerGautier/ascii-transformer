## Text Transformer

### About
    
Using text transformer cli tool, you can transformer any input file into various formats: ascii-drawing, binary, hex, numeric, utf-8. This is a hobby project to practice C++ in a random project I thought up.

**WARNING:** some translations are **_lossy_** if input file contains incompatible data for the destination formatt. A best-effort attempt is made.

### Build-Source
    
```
git clone git@github.com:SummerGautier/text-transformer.git
clang++ -std=c++20 main.cpp transformConfig.cpp -o ttransform.exe
# For how to use ttransform look at "Usage"
```

### Usage
     
 ```
 ./ttransform.exe --src my-text.txt --out destination.txt --ascii-draw
 # use an appropriate output file format [destination.bin, destination.hex, etc.]
 ```
