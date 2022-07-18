MODE=${1:-Release}
mkdir -p Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=$MODE -DCMAKE_CXX_COMPILER=g++ || exit 1
cmake --build . --config $MODE > cmake_output.txt || exit 1