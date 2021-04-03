cmake -G Ninja -Bbuild -DCMAKE_CXX_COMPILER="D:/msys64/mingw64/bin/g++.exe" -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build
cd build
ctest
test_circle_map.exe