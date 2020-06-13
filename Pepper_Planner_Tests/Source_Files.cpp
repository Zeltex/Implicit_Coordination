#include "pch.h"
#include "CppUnitTest.h"

#include "../Pepper_Planner/World.cpp"
#include "../Pepper_Planner/Formula.cpp"
#include "../Pepper_Planner/Formula_Component.cpp"
#include "../Pepper_Planner/Formula_Creator.cpp"
#include "../Pepper_Planner/Graph.cpp"
#include "../Pepper_Planner/Node.cpp"
#include "../Pepper_Planner/State.cpp"

/*
The test project has to have access to the source code of the main project (Pepper_Planner)
or else simply including the headers will cause link errors. However including the source files in 
multiple files will cause duplicate definition errors, hence this (hack) class.
*/


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Source_Files)
	{
	public:

	};
}
