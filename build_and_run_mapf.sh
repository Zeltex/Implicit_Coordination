START=${1:-1}
END=${2:-27}
./build.sh || exit 1
cd Build
./Release/Pepper_Planner mapf $START $END