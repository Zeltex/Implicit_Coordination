cmake_minimum_required (VERSION 2.8.11)
project (PEPPER_PLANNER)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDEBUG_PRINT -DPRINT_PARTIAL)


file(GLOB PLANNER_SRCS Pepper_Planner/*.cpp)
file(GLOB FORMULA_SRCS Formula/*.cpp)
file(GLOB DOMAIN_SRCS Domain_Loader/*.cpp)

add_executable(pepper_planner ${PLANNER_SRCS} ${FORMULA_SRCS} ${DOMAIN_SRCS})

target_include_directories(pepper_planner PUBLIC Pepper_Planner)
target_include_directories(pepper_planner PUBLIC Formula)
target_include_directories(pepper_planner PUBLIC Domain_Loader)
