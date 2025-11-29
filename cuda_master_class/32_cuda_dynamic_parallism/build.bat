# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug

nsys profile -o output --trace=cuda,nvtx .\bin\parallelReduction.exe

nsys stats output.nsys-rep