#include "pch.h"
#include "CppUnitTest.h"

#include "World.cpp"
#include "formula.cpp"
#include "Formula_Component.cpp"
#include "Graph.cpp"
#include "Node.cpp"
#include "State.cpp"
#include "Action.cpp"
#include "Action_Event.cpp"
#include "Action_Library.cpp"
#include "DEL_Operations.cpp"
#include "Agent.cpp"
#include "Planner.cpp"
#include "Policy.cpp"
#include "Misc.cpp"
#include "Bisimulation_Context.cpp"
#include "General_Action.cpp"
#include "Domain.cpp"



/*
The test project has to have access to the source code of the main project (Pepper_Planner)
or else simply including the headers will cause link errors. However including the source files in 
multiple files will cause duplicate definition errors, hence this (hack) class.
*/


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	//using namespace del;
	TEST_CLASS(Source_Files)
	{
	public:

	};
}
