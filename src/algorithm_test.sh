cd algorithm
cmake -S . -B build
cmake --build build
cd build && ctest -V
cd ../..
