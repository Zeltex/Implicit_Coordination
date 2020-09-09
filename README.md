# Pepper_Planner

## Run

The code can be run from Visual Studio (tested on Visual Studio 2019 (v142)) via the included Pepper_Planner.sln (.sln file is as is and can currently not be generated via a script).

The CMakeLists.txt file has been used to compile the code on g++ as part of the larger robot project.

## Settings

The Pepper_Planner/Core.hpp file contains flags for enabling various settings in the algorithm aswell as setting whether debug information is printed.


## Dependencies

The project is split into 3 parts; Domain_Loader, Formula and Pepper_Planner, of which Pepper_Planner/Main.cpp is the main file. 
The project does not have any external dependencies, however optionally debug information can be printed to a file (set in Pepper_Planner/Core.hpp) and manually compiled with [GraphViz](https://graphviz.org/download/) via the scripts Compile_*.sh in Debug_Output 


## Scenarios

The Examples folder contains the block search and false belief synthesis tasks, which are setup to be run through the Pepper_Planner/Main.cpp file
