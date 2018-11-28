#include "item.hpp"
#include "kmint/random.hpp"
#include "cow.hpp"

using namespace kmint;

map::map_node const &random_item_node(map::map_graph const &graph) {
	int r = kmint::random_int(0, graph.num_nodes());
	return graph[r];
}

item::item(const char item_, const char *image, kmint::map::map_graph &g)
	: play::map_bound_actor{ g, random_item_node(g) },
	drawable_{ *this, kmint::graphics::image{image, 0.05} }, item_{ item_ } {}

void item::act(kmint::delta_time dt) {
	for (std::size_t i = 0; i < num_colliding_actors(); ++i) {
		auto &a = colliding_actor(i);
		if (&a == cow_) {
			node(random_item_node(graph()));
			switch (this->item_) {
			case 'p':
				cow_->setBoolPill(true);
				break;
			case 'w':
				cow_->setBoolWeapon(true);
				break;
			}
		}
	}
}
