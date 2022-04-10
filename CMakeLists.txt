cmake_minimum_required (VERSION 3.10)
project (PEPPER_PLANNER)

set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++17")
set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++17")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB BENCHMARK_SRCS Pepper_Planner_Benchmarks/*.cpp)
file(GLOB PLANNER_SRCS Pepper_Planner/*.cpp)
file(GLOB FORMULA_SRCS Formula/*.cpp)
file(GLOB DOMAIN_SRCS Domain_Loader/*.cpp)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_BINARY_DIR}/Debug)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
endif()

add_executable(Pepper_Planner ${BENCHMARK_SRCS} ${PLANNER_SRCS} ${FORMULA_SRCS} ${DOMAIN_SRCS})

target_include_directories(Pepper_Planner PUBLIC Pepper_Planner_Benchmarks)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner)
target_include_directories(Pepper_Planner PUBLIC Formula)
target_include_directories(Pepper_Planner PUBLIC Domain_Loader)
