MODE=${1:-Release}
mkdir -p Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=$MODE
cmake --build . --config $MODE
./$MODE/Pepper_Planner "..\\Examples\\MAPF\\"