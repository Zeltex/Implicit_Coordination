#pragma once

#include "../Domain_Loader/Domain_Interface.hpp"
namespace del {

	class Domain_Interface_Implementation : public Domain_Interface {
	public:
		Domain_Interface_Implementation() : working(false) {}
		virtual void set_debug_working() override;
	private:
		bool working;
	};
}