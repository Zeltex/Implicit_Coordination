MODE=${1:-Release}
mkdir -p Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=$MODE -DCMAKE_CXX_COMPILER=g++
cmake --build . --config $MODE
./$MODE/Pepper_Planner "../Examples/Coin_Flip/" "Coin_Flip_" 1 50
