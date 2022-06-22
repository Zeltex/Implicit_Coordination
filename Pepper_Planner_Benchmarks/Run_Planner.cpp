#include "Graph.hpp"
#include "Formula.hpp"
#include <iostream>
#include <chrono>
#include <ctime>    
#include <time.h>


#include "World.hpp"
#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "Action.hpp"
#include "Action_Library.hpp"
#include "Planner.hpp"
#include "Domain.hpp"
#include "DEL_Interface.hpp"
#include "Loader.hpp"

#include "Run_Planner.hpp"

namespace del {

	void execute(DEL_Interface& del_interface) {
		bool failed = false;
		while (!del_interface.is_solved()) {
			std::optional<Action> action = del_interface.get_next_action();
			if (action.has_value()) {
				del_interface.perform_action(action.value());
			}
			else 
			{
				std::cerr << "NO APPLIABLE ACTION" << std::endl;
				std::cout << "-=-=- Fail -=-=-";
				failed = true;
				break;
			}
		}
		if (!failed) {
			std::cout << "-=-=- Success -=-=-" << std::endl;
		}
	}

	DEL_Interface find_plan2(const std::string& file_name, const std::string& planning_agent) {
		return DEL_Interface("../Examples/" + file_name);
	}

	DEL_Interface find_plan(const std::string& file_name, const std::string& planning_agent) {
		auto time1 = std::chrono::high_resolution_clock::now();

		DEL_Interface del_interface("../Examples/" + file_name);

		auto time2 = std::chrono::high_resolution_clock::now();
		auto elapsed1 = time2 - time1;
		std::cout << ".maepl load time " << (elapsed1.count() / 1000000) << "ms\n";
		del_interface.create_policy(planning_agent);
		auto time3 = std::chrono::high_resolution_clock::now();

		//auto elapsed1 = time2 - time1;
		auto elapsed2 = time3 - time2;



		//std::cout << ".maepl load time " << (elapsed1.count() / 1000000) << "ms\n";
		std::cout << "planning execution time " << (elapsed2.count() / 1000000) << "ms\n";
		return del_interface;
	}


	void find_and_execute(std::string file_name, const std::string& planning_agent) {
		auto del_interface = find_plan(file_name, planning_agent);

		execute(del_interface);
	}

}