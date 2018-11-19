#ifndef KMINTAPP_ALGORITHM_HPP
#define KMINTAPP_ALGORITHM_HPP
#include "kmint/map/map.hpp"
#include <map>
#include "conditions.hpp"

class cow;
class hare;

class algorithm {
private:
	//size_t timer_ = 0;
	std::map<size_t, conditions> conditions_; // dijkstra weight
	kmint::map::map_graph &graph_;
public:
	algorithm(kmint::map::map_graph &g) : graph_(g) {};
	int dijkstra( cow& begin, hare& end) const;
	void calculate_dijkstra_weight(cow& begin, hare& end);
		
	
};
#endif