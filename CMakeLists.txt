cmake_minimum_required (VERSION 2.8.11)
project (PEPPER_PLANNER)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB BENCHMARK_SRCS Pepper_Planner_Benchmarks/*.cpp)
file(GLOB PLANNER_SRCS Pepper_Planner/*.cpp)
file(GLOB FORMULA_SRCS Formula/*.cpp)
file(GLOB DOMAIN_SRCS Domain_Loader/*.cpp)

add_executable(pepper_planner ${BENCHMARK_SRCS} ${PLANNER_SRCS} ${FORMULA_SRCS} ${DOMAIN_SRCS})

target_include_directories(pepper_planner PUBLIC Pepper_Planner_Benchmarks)
target_include_directories(pepper_planner PUBLIC Pepper_Planner)
target_include_directories(pepper_planner PUBLIC Formula)
target_include_directories(pepper_planner PUBLIC Domain_Loader)
