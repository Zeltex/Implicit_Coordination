# Implicit Coordination Planner

This repository contains the planner described in the paper *DEL-based Epistemic Planning for Human-Robot Collaboration: Theory and Implementation* currently under review for KR 2021 in Hanoi, Vietnam. The planner uses Dynamic Epistemic Logic to find *implicitly coordinated* plans, that is, plans where the agents uses perspective shifts to reason about the knowledge and capabilities of the other agents in the planning task, thus reducing the need for explicit communication between the agents.

## Demo

Video of a Softbank's Pepper robot using this planner to solve a *multi-agent pathfinding with destination uncertainty* problem.
[![Link to the video](media/MAPFDUYoutube.png?raw=true)](https://youtu.be/48h3Kbov9lo)

Video of a Pepper robot using the reasoning capabilities of the planner to solve the Sally-Anne false belief task.
See our prior article ![*Implementing Theory of Mind on a Robot Using Dynamic Epistemic Logic*](https://doi.org/10.24963/ijcai.2020/224) for further detail.
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

The Examples folder contains the block search and false belief synthesis tasks, which are setup to be run through the Pepper_Planner/Main.cpp file.

## Settings

The Pepper_Planner/Core.hpp file contains flags for enabling various settings in the algorithm, most noticably:
- BISIMILAR_USE_HASH_ENABLED: ??
- BISIM_COMPARISON_ENABLED: ??
- BISIM_CONTRACTION_ENABLED: ??


## Code overview
The project is split into 3 parts:
- Domain_Loader contains a parser for the PDDL-like language used for domain descriptions.
- Formula contains various classes for representing and reasoning with Dynamic Epistemic Logic.
- Pepper_Planner contains the planner itself. Some notable files includes:
  - Action.hpp - The *Action* class represents a pointed DEL event model.
  - Bisimulation_Context.cpp - Contains the novel Ordered Partition Refinement algorithm.
  - Domain.hpp - The *Domain* class contains a representation of an implicitly coordinated planning problem.
  - Main.cpp - Contains the entry point of the planner.
  - Planner.cpp - Contains the breadth-first AND/OR graph search algorithm.
  - World.hpp - The *World* class represents a pointed DEL world model.
