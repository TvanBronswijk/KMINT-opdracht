#ifndef KMINTAPP_ALGORITHM_HPP
#define KMINTAPP_ALGORITHM_HPP
#include "kmint/map/map.hpp"
#include <map>
#include <set>
#include <queue>
#include "conditions.hpp"

class cow;
class hare;

class algorithm {
private:
	kmint::map::map_graph &graph_;

	std::map<size_t, conditions> conditions_; // dijkstra weight
public:
	algorithm(kmint::map::map_graph &g) : graph_(g) {};
	std::map<size_t, conditions> get_conditions_() { return conditions_; }

	template <class S, class T>
	size_t dijkstra(S& begin, T& end) {
		bool found = false;
		std::map<size_t, conditions> conditions_; // dijkstra weight
		std::set<size_t> visited; // list of finished nodes
		std::vector<size_t> queue; // list of unfinished nodes

		queue.insert(queue.end(), begin.node().node_id());
		conditions_.insert(std::pair<size_t, conditions>(begin.node().node_id(),
			conditions(0)));

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
					std::map<size_t, conditions>::iterator it1 = conditions_.find(base.node_id());
					std::map<size_t, conditions>::iterator it2 = conditions_.find(base[i].to().node_id());
					if (it2->second.weight_ > (base[i].weight() + it1->second.weight_)) { // check if next weight is lower than this one.
						it2->second.weight_ = (base[i].weight() + it1->second.weight_); // add weight to nodes
					}
				}
				else {
					std::map<size_t, conditions>::iterator it1 = conditions_.find(base.node_id());
					queue.insert(queue.end(), base[i].to().node_id());
					conditions_.insert(std::pair<size_t, conditions>(base[i].to().node_id(), conditions((base[i].weight() + it1->second.weight_))));
				}
				found = false;
			}
		}

		graph_.untag_all();
	}
		

	template <class S, class T>
	void A_star(S& begin, T& end) {
		std::set<size_t> visited; // list of finished nodes
		std::vector<size_t> queue; // list of unfinished nodes

		queue.insert(queue.end(), begin.node().node_id());
		conditions_.insert(std::pair<size_t, conditions>(begin.node().node_id(),
			conditions(0)));

		while (!queue.empty()) {
			auto& base = graph_[queue.front()];
			queue.erase(queue.begin());
			visited.insert(base.node_id());

			std::map<size_t, int> distances;
			for (size_t i = 0; i < base.num_edges(); i++) { //loop edges. calculate distance to end.
				std::map<size_t, conditions>::iterator it2 = conditions_.find(base[i].to().node_id());
				if (it2 == conditions_.end()) {

					int distance_x = std::abs((end.node().location().x() - base[i].to().location().x()));
					int distance_y = std::abs((end.node().location().y() - base[i].to().location().y()));

					int absolute_distance = std::sqrt((distance_x * distance_x) + (distance_y * distance_y));
					distances.insert(std::pair<int, int>(i, absolute_distance));
				}
			}
			for (std::map<size_t, int>::iterator loop1 = distances.begin(); loop1 != distances.end(); ++loop1) {
				int closest;
				int closest_distance = 99999;
				for (std::map<size_t, int>::iterator loop2 = distances.begin(); loop2 != distances.end(); ++loop2) {
					if (loop2->second < closest_distance) {
						closest_distance = loop2->second;
						closest = loop2->first;
					}
				}
				std::map<size_t, conditions>::iterator base_node = conditions_.find(base.node_id());
				queue.insert(queue.end(), base[closest].to().node_id());
				conditions_.insert(std::pair<size_t, conditions>(base[closest].to().node_id(), conditions((base[closest].weight() + base_node->second.weight_))));
				if (base[closest].to().node_id() == end.node().node_id()) {
					std::map<size_t, conditions>::iterator last_node = conditions_.find(base[closest].to().node_id());
					conditions_.insert(std::pair<size_t, conditions>(base[closest].to().node_id(), conditions((base[closest].weight() + last_node->second.weight_))));
					return;
				}
			}
		}
	}



	template <class S, class T>
	size_t next_position(S& begin, T& end) {
		int next_position = end.node().node_id();

		for (size_t i = 0; i < begin.node().num_edges(); i++) { // loop closest nodes
			if (begin.node()[i].to().node_id() == end.node().node_id()) {
				//end.register_collision(begin);
				begin.setState(State::Roaming);
				conditions_.clear();
				graph_.untag_all();
				return begin.node()[i].to().node_id();
			}
		}
			while (true) {//find the path to walk
				auto& node = graph_[next_position]; // get the node in visited.
				graph_[next_position].tagged(true);
				for (size_t i = 0; i < node.num_edges(); i++) { // loop closest nodes
					std::map<size_t, conditions>::const_iterator it1 = conditions_.find(graph_[next_position].node_id());
					std::map<size_t, conditions>::const_iterator it2 = conditions_.find(node[i].to().node_id());
					if (it2 != conditions_.end()) {
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
			}
			return next_position;
		}
};


#endif