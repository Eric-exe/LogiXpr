cd "$(dirname "$0")"
mkdir -p build
cd build
cmake ..
cmake --build .
ctest -C Debug
read -n 1 -s -r -p "Press any key to continue..."