#ifndef KMINTAPP_STATEMACHINE_HPP
#define KMINTAPP_STATEMACHINE_HPP
#include <vector>
#include "kmint/play.hpp"   
#include "kmint/map/map.hpp"
#include "state.hpp"

class state_machine {
public:
	state_machine(kmint::map::map_graph &g, std::vector<size_t> items) : items_{ items }, graph_{ g }  {};

	State act() const;
	State roaming() const;
	State searching() const;
	State chasing() const;
private:
	std::vector<size_t> items_places_;
	std::vector<size_t> items_;
	kmint::map::map_graph &graph_;
};

#endif