#include "cow.hpp"

using namespace kmint;

static const char *cow_image = "resources/cow.png";
cow::cow(const kmint::map::map_graph &g, const kmint::map::map_node &initial_node, algorithm &a) : play::map_bound_actor{ g, initial_node },
drawable_{ *this,kmint::graphics::image{cow_image, 0.1} },
	algorithm_{ a } {}

void cow::act(delta_time dt) {
	t_passed_ += dt;
	if (to_seconds(t_passed_) >= 1) {
		int next_position = algorithm_.dijkstra(*this,*this->hare_);
		this->node(this->graph()[next_position]);
		//// pick random edge
		//int next_index = random_int(0, node().num_edges());
		//this->node(node()[next_index].to());
		t_passed_ = from_seconds(0);
	}
}