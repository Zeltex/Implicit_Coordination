cmake_minimum_required (VERSION 3.10)
project (PEPPER_PLANNER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "/std:c++17")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /MTd")

else()
  set(CMAKE_CXX_FLAGS "-Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++17")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++17")
endif()





file(GLOB BENCHMARK_SRCS Pepper_Planner_Benchmarks/*.cpp)
file(GLOB SRC_SRCS Pepper_Planner/src/*.cpp)
file(GLOB DEL_SRCS Pepper_Planner/src/DEL/*.cpp)
file(GLOB ACTION_SRCS Pepper_Planner/src/DEL/Action/*.cpp)
file(GLOB FORMULA_SRCS Pepper_Planner/src/DEL/Formula/*.cpp)
file(GLOB LOADER_SRCS Pepper_Planner/src/Domain_Loader/*.cpp)
file(GLOB BUFFER_SRCS Pepper_Planner/src/Domain_Loader/Buffers/*.cpp)
file(GLOB LOADER_DEL_SRCS Pepper_Planner/src/Domain_Loader/DEL/*.cpp)
file(GLOB PLANNER_SRCS Pepper_Planner/src/Planner/*.cpp)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_BINARY_DIR}/Debug)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
endif()

add_executable(Pepper_Planner ${BENCHMARK_SRCS} ${SRC_SRCS} ${DEL_SRCS} ${ACTION_SRCS} ${FORMULA_SRCS} ${LOADER_SRCS} ${BUFFER_SRCS} ${LOADER_DEL_SRCS} ${PLANNER_SRCS})

target_include_directories(Pepper_Planner PUBLIC Pepper_Planner_Benchmarks)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/DEL)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/DEL/Action)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/DEL/Formula)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/Domain_Loader)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/Domain_Loader/Buffers)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/Domain_Loader/DEL)
target_include_directories(Pepper_Planner PUBLIC Pepper_Planner/src/Planner)
