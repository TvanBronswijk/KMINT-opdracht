#include "algorithm.hpp"
#include <set>
#include <queue>
#include <map>

#include "actors/cow.hpp"
#include "actors/hare.hpp"

using namespace kmint;

int algorithm::dijkstra(cow& begin,hare& end) const{	
	graph_.untag_all();

	for (size_t i = 0; i < begin.node().num_edges(); i++) { // check if cow is near rabbit. 
		if (begin.node()[i].to().node_id() == end.node().node_id()) {
			end.register_collision(begin);
			return begin.node().node_id();
		}
	}

	//if (this->timer_ > 1) {
	//	this->timer_ -= 1;
	//	return begin.node().node_id();
	//}

	int next_position = end.node().node_id();
	while (true) {//find the path to walk
		auto& node = graph_[next_position]; // get the node in visited.
		graph_[next_position].tagged(true);
		for (size_t i = 0; i < node.num_edges(); i++) { // loop closest nodes
			std::map<size_t, conditions>::const_iterator it1 = this->conditions_.find(graph_[next_position].node_id());
			std::map<size_t, conditions>::const_iterator it2 = this->conditions_.find(node[i].to().node_id());
			if (it1->second.weight_ > it2->second.weight_) { // check if next node has a lower weight then previous.
				next_position = it2->first;
				for (size_t i = 0; i < begin.node().num_edges(); i++) { // check if nodes is near the cow
					if (begin.node()[i].to().node_id() == next_position) {
						//if (begin.node()[i].weight() > 1) {
						//	this->timer_ = begin.node()[i].weight();
						//}else
						return next_position;
					}
				}
			}
		}
	}
	return next_position;
}

void algorithm::calculate_dijkstra_weight(cow& begin, hare& end){
	bool found = false;
	std::map<size_t, conditions> tmp_conditions; // dijkstra weight
	std::set<size_t> visited; // list of finished nodes
	std::vector<size_t> queue; // list of unfinished nodes

	queue.insert(queue.end(),begin.node().node_id());
	tmp_conditions.insert(std::pair<size_t, conditions>(begin.node().node_id(), conditions(0,0)));

	size_t default_weight = 9999;
	while (!queue.empty()) {
		auto& base = graph_[queue.front()];
		queue.erase(queue.begin());
		visited.insert(base.node_id());
		//base.tagged(true);
		for (size_t i = 0; i < base.num_edges(); i++) { //loop closest nodes
			std::set<size_t>::iterator it = visited.find(base[i].to().node_id());
			for (auto it = queue.begin(); it != queue.end(); ++it) {
				if (*it == base[i].to().node_id()) found = true;
			}
			if (it != visited.end() || found) { //check if node is already found in queue or visited.
				std::map<size_t, conditions>::iterator it1 = tmp_conditions.find(base.node_id());
				std::map<size_t, conditions>::iterator it2 = tmp_conditions.find(base[i].to().node_id());
				if (it2->second.weight_ > (base[i].weight() + it1->second.weight_)) { // check if next weight is lower than this one.
					it2->second.weight_ = (base[i].weight() + it1->second.weight_); // add weight to nodes
				}
			}
			else {
				std::map<size_t, conditions>::iterator it1 = tmp_conditions.find(base.node_id());
				queue.insert(queue.end(), base[i].to().node_id());
				tmp_conditions.insert(std::pair<size_t, conditions>(base[i].to().node_id(), conditions((base[i].weight() + it1->second.weight_), 0)));
			}
			found = false;
		}
	}

	this->conditions_ = tmp_conditions;
}

