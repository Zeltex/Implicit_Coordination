#pragma once
#include <cstddef>
#include <vector>
#include <optional>
#include "Formula.hpp"

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

		Event_Id(size_t id) : id(id) {};
		Event_Id(const Event_Id& other) :id(other.id) {}
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

	struct Edge_Condition {
		Edge_Condition(std::string event_from, std::string event_to, Formula&& condition) :
			event_from(event_from), event_to(event_to), condition(std::move(condition)) {}
		std::string event_from;
		std::string event_to;
		Formula condition;
	};

	struct Agent_Edges {
		Agent_Edges(size_t agents) : conditions(agents), current_size(0) {}
		std::unordered_map<size_t, std::unordered_map<size_t, Formula>> conditions;

		void insert(Event_Id event_from, Event_Id event_to, Formula&& condition) {
			auto it = conditions.find(event_from.id);
			if (it == conditions.end()) {
				conditions.insert({ event_from.id, {} });
			}
			conditions[event_from.id][event_to.id] = std::move(condition);
			current_size++;
		}

		std::optional<const Formula*> get_condition(Event_Id event_from, Event_Id event_to) const {
			auto it1 = conditions.find(event_from.id);
			if (it1 != conditions.end()) {
				auto it2 = it1->second.find(event_to.id);
				if (it2 != conditions.at(event_from.id).end()) {
					return { &(it2->second)};
				}
			}
			return {};
		}

		size_t size() const{
			return this->current_size;
		}

		std::string to_graph(const std::string& agent_name) const {
			std::string result;
			// Magic number, estimating around 20 characters per edge
			result.reserve(current_size * 20);
			for (const auto& entry1 : conditions) {
				for (const auto& entry2 : entry1.second) {
					result += "s" + std::to_string(entry1.first) + " -> s" + std::to_string(entry2.first) + "[label=\"" + (agent_name) + ":" + entry2.second.to_string() + "\"];\n";
				}
			}
			return std::move(result);
		}
	private:
		size_t current_size;
	};

}