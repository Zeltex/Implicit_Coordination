#include "World.hpp"
#include "Domain.hpp"

namespace del {

	World_Id World::get_id() const {
		return id;
	}

	World World::create_copy(World_Id id) const {
		return World(id, true_propositions);
	}

	void World::add_true_propositions(const std::vector<Proposition>& propositions) {
		for (const auto& proposition : propositions) {
			if (std::find(true_propositions.begin(), true_propositions.end(), proposition) == true_propositions.end()) {
				true_propositions.push_back(proposition);
			}
		}
	}

	void World::remove_true_propositions(const std::vector<Proposition>& propositions) {
		for (const auto& proposition : propositions) {
			auto result = std::find(true_propositions.begin(), true_propositions.end(), proposition);
			if (result != true_propositions.end()) {
				true_propositions.erase(result);
			}
		}
	}

	const std::vector<Proposition>& World::get_true_propositions() const {
		return true_propositions;
	}

	std::string World::to_string(const Domain& domain) const{
		std::string result = "World " + std::to_string(id.id) + ": ";
		bool first = true;
		for (const auto& proposition : true_propositions) {
			if (first) {
				first = false;
			} else {
				result += ";";
			}
			result += domain.get_proposition_instance(proposition).to_string(domain.get_id_to_atom());
		}
		return result;
	}
	void World::set_id(World_Id id) {
		this->id = std::move(id);
	}

	bool World::operator!=(const World& other) const {
		if (true_propositions.size() != other.true_propositions.size()) return true;

		auto props1 = true_propositions;
		auto props2 = other.true_propositions;
		std::sort(props1.begin(), props1.end());
		std::sort(props2.begin(), props2.end());


		for (size_t i = 0; i < props1.size(); i++) {
			if (props1[i] != props2[i]) return true;
		}
		return false;
	}
	std::string World::to_hash() const {
		std::string hash;
		auto temp = true_propositions;
		std::sort(temp.begin(), temp.end());
		for (const auto& prop : temp) {
			hash += prop.to_hash();
		}
		return hash;
	}
}