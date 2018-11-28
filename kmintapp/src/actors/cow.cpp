#include "cow.hpp"
#include "kmint/random.hpp"

using namespace kmint;

static const char *cow_image = "resources/cow.png";
cow::cow(kmint::map::map_graph &g, const kmint::map::map_node &initial_node, std::vector<std::reference_wrapper<item>>& items) : play::map_bound_actor{ g, initial_node },
drawable_{ *this,kmint::graphics::image{cow_image, 0.1} },
state_machine_{ state_machine(algorithm(g)) }, 
state_{ State::Roaming },
items_{ items }, target_{ nullptr } {}

void cow::act(delta_time dt) {
	t_passed_ += dt;
	if (to_seconds(t_passed_) >= 1) {
		size_t next_position;
		if (this->state_ == State::Searching) {
			if(target_ == nullptr) target_ = &items_[random_int(0, items_.size())].get();
			next_position = state_machine_.act(this, this->target_);
			if (target_->node().node_id() == this->graph()[next_position].node_id()) target_ = nullptr;
		}
		else {
			next_position = state_machine_.act(this, this->hare_);
		}
		this->node(this->graph()[next_position]);
		//// pick random edge
		//int next_index = random_int(0, node().num_edges());
		//this->node(node()[next_index].to());
		t_passed_ = from_seconds(0);
	}
}

State cow::getState() const{
	return state_;
}
void cow::setState(State state_) {
	this->state_ = state_;
}

bool cow::getBoolWeapon() const {
	return this->weapon_;
}
bool cow::getBoolPill() const {
	return this->pill_;
}
void cow::setBoolPill(bool pill) {
	this->pill_ = pill;
}
void cow::setBoolWeapon(bool weapon) {
	this->weapon_ = weapon;
}