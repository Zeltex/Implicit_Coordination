START=${1:-1}
END=${2:-50}
./build.sh || exit 1
cd Build
./Release/Pepper_Planner coin $START $END