#pragma once
#include <string>
#include <map>

namespace del
{
	class Atom_Id;
	class Inputs;
	class General_Objects;
	class Atom_Buffer
	{
	public:
		void set(Inputs& inputs);
		void set(General_Objects& objects);
		Atom_Id get(const std::string& name);
	private:
		std::map<std::string, Atom_Id> atoms;
	};
}