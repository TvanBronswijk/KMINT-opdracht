#ifndef KMINTAPP_ALGORITHM_HPP
#define KMINTAPP_ALGORITHM_HPP
#include "kmint/map/map.hpp"

#include "kmint/play.hpp"
#include "actors/cow.hpp"
#include "actors/hare.hpp"

class pathfinding {
private:
	const kmint::map::map_graph &graph_;
public:
	pathfinding(kmint::map::map_graph &ding) : graph_(ding) {};
	int dijkstra(const cow& begin,const hare& end) const;
		
	
};
#endif