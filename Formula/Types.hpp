#pragma once

struct Formula_Id {
	size_t id;
	Formula_Id() = default;
	Formula_Id(size_t id) : id(id) {}
	Formula_Id(size_t id, size_t id2) {}

	bool operator==(const Formula_Id& other) const {
		return this->id == other.id;
	}
};

enum class Formula_Types {
	Top,
	Bot,
	Prop,
	Not,
	And,
	Or,
	Believes,
	Everyone_Believes,
	Common_Knowledge
};