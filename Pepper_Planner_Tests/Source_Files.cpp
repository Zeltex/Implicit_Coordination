#include "pch.h"
#include "CppUnitTest.h"

#include "../Pepper_Planner/World.cpp"
#include "../Formula/formula.cpp"
#include "../Formula/Formula_Component.cpp"
#include "../Pepper_Planner/Graph.cpp"
#include "../Pepper_Planner/Node.cpp"
#include "../Pepper_Planner/State.cpp"
#include "../Pepper_Planner/Action.cpp"
#include "../Pepper_Planner/Action_Event.cpp"
#include "../Pepper_Planner/Action_Library.cpp"
#include "../Pepper_Planner/DEL_Operations.cpp"
#include "../Pepper_Planner/Agent.cpp"
#include "../Pepper_Planner/Planner.cpp"
#include "../Pepper_Planner/Policy.cpp"
#include "../Pepper_Planner/Misc.cpp"
#include "../Pepper_Planner/Bisimulation_Context.cpp"


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
