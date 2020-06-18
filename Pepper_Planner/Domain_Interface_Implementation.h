#pragma once

#include <iostream>

#include "../Domain_Loader/Domain_Interface.hpp"
namespace del {

	class Domain_Interface_Implementation : public Domain_Interface {
	public:
		Domain_Interface_Implementation() : working(false) {}
		virtual void set_debug_working() override;
		virtual void new_domain(std::string name) override;
		virtual void finish_domain() override;
		virtual void new_action(std::string name) override;
		virtual void finish_action() override;
		virtual void add_action_input(std::string type, std::string name) override;
	private:
		bool working;
		std::string current_domain_name;
	};
}