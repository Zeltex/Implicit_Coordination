MODE=${1:-Release}
mkdir -p Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=$MODE -DCMAKE_CXX_COMPILER=g++ || exit 1
cmake --build . --config $MODE > cmake_output.txt || exit 1
#./$MODE/Pepper_Planner mapf 1 27
#./$MODE/Pepper_Planner coin 1 50
./$MODE/Pepper_Planner single "../examples/MAPF/p1.maepl" "a0"