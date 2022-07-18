# Implicit Coordination Planner

This repository contains the planner described in the paper *DEL-based Epistemic Planning for Human-Robot Collaboration: Theory and Implementation* currently under review. The planner uses Dynamic Epistemic Logic to find *implicitly coordinated* plans, that is, plans where the agents uses perspective shifts to reason about the knowledge and capabilities of the other agents in the planning task, thus reducing the need for explicit communication between the agents.

***The exact code used in the paper is on branch 'kr_2021'. Branch 'master' contains an optimised version, with k logic (directional accessbility relations)***

## Demo

Video of a Softbank's Pepper robot using this planner to solve a *multi-agent pathfinding with destination uncertainty* problem.
[![Link to the video](media/MAPFDUYoutube.png?raw=true)](https://youtu.be/48h3Kbov9lo)

Video of a Pepper robot using the reasoning capabilities of the planner to solve the Sally-Anne false belief task.
See our prior article [*Implementing Theory of Mind on a Robot Using Dynamic Epistemic Logic*](https://doi.org/10.24963/ijcai.2020/224) for further detail.
[![Link to the video](media/SallyAnneYoutube.png?raw=true)](https://youtu.be/T0lTlRgoBLg)

## Install

The project does not have any external dependencies, but requires a reasonable new C++-17 compiler.

> Optionally debug information can be printed to a file (set in Pepper_Planner/Core.hpp) and manually compiled with [GraphViz](https://graphviz.org/download/) via the scripts Compile_*.sh in Debug_Output.

#### Windows

Tested on Windows 10 with Visual Studio 2019 (v142).
The code can be run from Visual Studio via the included Pepper_Planner.sln (.sln file is as-is and can currently not be generated via a script).

#### Linux

Tested on Ubuntu 18.04 & 20.10 with g++-7.2 and clang++-11 respectively.
The planner can be compiled using the supplied CMake build files:

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Usage

The Examples folder contains the block search, coin flip and Multi-Agent Path Finding with Destination Uncertainty (MAPF) tasks, which are setup to be run through the Pepper_Planner_Benchmarks/Main.cpp file. The build_and_run_coin_flip.sh and build_and_run_mapf.sh bash scripts are setup to run the coin flip and MAPF benchmarks from the paper (Benchmarks are saved in the Benchmarks/ directory). 

To run the OPR benchmark, the Pepper_Planner/Core.hpp must be set to:
BISIM_COMPARISON_ENABLED = 1
BISIM_CONTRACTION_ENABLED = 1
And for the Baseline benchmark:
BISIM_COMPARISON_ENABLED = 0
BISIM_CONTRACTION_ENABLED = 0

## Settings

The Pepper_Planner/Core.hpp file contains flags for enabling various settings in the algorithm, most noticably:

- BISIMILAR_USE_HASH_ENABLED: If enabled uses hashing to lookup states, otherwise performs a comparison based linear search.
- BISIM_COMPARISON_ENABLED: If enabled maintains a single node/state per set of bisimilar states via either a linear search or hashing (see BISIMILAR_USE_HASH_ENABLED)
- BISIM_CONTRACTION_ENABLED: If enabled performs bisimilar contraction on nodes (If OPR_ENABLED is enabled, performs OPR)

## Code overview

The project is split into 3 parts:

- Domain_Loader contains a parser for the PDDL-like language used for domain descriptions. The parser only detects syntax errors.
- Formula contains various classes for representing and reasoning with Dynamic Epistemic Logic.
- Pepper_Planner contains the planner itself. Some notable files includes:
  - Action.hpp - The *Action* class represents a pointed DEL event model.
  - Bisimulation_Context.cpp - Contains the novel Ordered Partition Refinement algorithm.
  - Domain.hpp - The *Domain* class contains a representation of an implicitly coordinated planning problem.
  - Planner.cpp - Contains the breadth-first AND/OR graph search algorithm.
  - State.hpp - The *State* class represents a pointed DEL model.
- Pepper_Planner_Benchmarks contains code to run the benchmarks presented in the paper (Benchmarks are saved in the Benchmarks/ directory)
