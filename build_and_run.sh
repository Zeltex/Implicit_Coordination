MODE=${1:-Release}
mkdir -p Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=$MODE -DCMAKE_CXX_COMPILER=g++
cmake --build . --config $MODE > cmake_output.txt
./$MODE/Pepper_Planner 1 27
#./$MODE/Pepper_Planner "../examples/MAPF/p1.maepl" "a0"