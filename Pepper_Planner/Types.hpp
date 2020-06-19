#pragma once
#include <cstddef>

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

	struct World_Id {
		size_t id;

		bool operator==(const World_Id& other) const {
			return this->id == other.id;
		}
	};

	struct Event_Id {
		size_t id;

		bool operator==(const Event_Id& other) const {
			return this->id == other.id;
		}
	};

	enum class Node_Type {
		Or,
		And
	};

	struct World_Relation {
		World_Relation(World_Id world_from, World_Id world_to) :
			world_from(world_from), world_to(world_to) {}
		World_Id world_from;
		World_Id world_to;
	};

	struct Event_Relation {
		Event_Relation(Event_Id event_from, Event_Id event_to) :
			event_from(event_from), event_to(event_to) {}
		Event_Id event_from;
		Event_Id event_to;
	};

	struct World_Entry {
		World_Entry(World_Id old_world, Event_Id old_event, World_Id new_world) : 
			old_world(old_world), old_event(old_event), new_world(new_world) {}
		World_Id old_world;
		Event_Id old_event;
		World_Id new_world;
	};
}