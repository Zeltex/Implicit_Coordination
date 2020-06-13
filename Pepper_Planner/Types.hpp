#pragma once
namespace del {
	struct Node_Id {
		size_t id;

		bool operator==(const Node_Id& other) const {
			return this->id == other.id;
		}
	};

	struct Agent_Id {
		size_t id;

		bool operator==(const Agent_Id& other) const {
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
}