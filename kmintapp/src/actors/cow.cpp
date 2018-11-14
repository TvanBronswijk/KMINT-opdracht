#include "cow.hpp"
#include "kmint/random.hpp"
#include <queue>          // std::queue

using namespace kmint;

static const char *cow_image = "resources/cow.png";
cow::cow(map::map_graph const &g, map::map_node const &initial_node)
	: play::map_bound_actor{ g, initial_node }, drawable_{ *this,
	kmint::graphics::image{
	cow_image, 0.1} } {}

void cow::act(delta_time dt) {
	t_passed_ += dt;
	if (to_seconds(t_passed_) >= 1) {
		dijkstra(node(), hare_->node());
		//// pick random edge
		//int next_index = random_int(0, node().num_edges());
		//this->node(node()[next_index].to());
		t_passed_ = from_seconds(0);
	}
}

void cow::dijkstra(const kmint::graph::basic_node<kmint::map::map_node_info>& begin, const kmint::graph::basic_node<kmint::map::map_node_info>& end){
	auto starting_position = const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(&begin); // make pointer of node to store it in a queue	


	for (size_t i = 0; i < starting_position->num_edges(); i++) { // check if cow is near rabbit. 
		if (starting_position[0][i].to().node_id() == end.node_id()) {
			this->register_collision(*this);
			return;
		}
	}
	
	std::map<int,const kmint::graph::basic_node<kmint::map::map_node_info>*> visited; // list of finished nodes
	std::queue<const kmint::graph::basic_node<kmint::map::map_node_info>*> queue; // list of unfinished nodes

	starting_position->weight(0);
	queue.push(starting_position);

	while (!queue.empty()) {
		auto base = const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(queue.front()); // ugly!!
		queue.pop();
		visited.insert(std::pair<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>(base->node_id(), base));
		base->tagged(true); // does not work when making a using;
		for (size_t i = 0; i < base->num_edges(); i++) { //loop closest nodes
			std::map<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>::iterator it = visited.find(base[0][i].to().node_id()); //get one off the closest nodes
			if (base[0][i].to().weight() > (base->weight() + base[0][i].weight())) // check if next weight is lower than this one.
				const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(&base[0][i].to())->weight(base->weight() + base[0][i].weight());// add weight to nodes
			if (it == visited.end() && base[0][i].to().queue() == false) {
				queue.push(&base[0][i].to());//doubt
				const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(&base[0][i].to())->queue(true);
			}
		}
	}
	int next_position = end.node_id();
	while (true) {//find the path to walk
		std::map<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>::iterator it = visited.find(next_position); // get the node in visited.
		for (size_t i = 0; i < it->second->num_edges(); i++) { // loop closest nodes
			if (it->second[0][i].to().weight() < it->second->weight()) { // check if next node has a lower weight then previous.
				next_position = it->second[0][i].to().node_id();
				for (size_t i = 0; i < starting_position->num_edges(); i++) { // check if nodes is near the cow
					if (starting_position[0][i].to().node_id() == next_position) {
						node(node()[i].to());
						restore_nodes(false, visited); //TODO: change this to begin when i now how to get all nodes. 
						return;
					}
				}
			}
		}
	}
}

void cow::restore_nodes(bool check, std::map<int, const kmint::graph::basic_node<kmint::map::map_node_info>*> visited){
	for (std::map<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>::iterator it = visited.begin(); it != visited.end(); ++it) {
		const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(it->second)->tagged(check);
		const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(it->second)->queue(check);
		const_cast<kmint::graph::basic_node<kmint::map::map_node_info>*>(it->second)->weight(99999);
	}
}