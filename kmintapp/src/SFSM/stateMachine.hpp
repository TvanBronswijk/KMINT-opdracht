#ifndef KMINTAPP_STATEMACHINE_HPP
#define KMINTAPP_STATEMACHINE_HPP
#include "kmint/play.hpp"   
#include "kmint/map/map.hpp"
#include "state.hpp"
#include "../pathfinding/algorithm.hpp"
#include "kmint/random.hpp"
#include <iostream>
#include "actors/Item.hpp"

class state_machine {
public:
	state_machine(algorithm a) : algorithm_{a} {};

	template <class S, class T>
	size_t act(S s, T t) {
		switch (s->getState()) {
		case State::Roaming:  return roaming(s, t);
		case State::Chasing: return chasing(s, t);
		case State::Searching: return searching(s, t);
		default: std::cout << "wrong input \n";
		}
	}
	template <class S, class T>
	size_t roaming(S s, T t) const {
		if (s->getBoolPill() == true && s->getBoolWeapon() == true) {
			s->setState(State::Chasing);
		}
		else {
			if (kmint::random_int(0, 10) < 2) {
				s->setState(State::Searching);
			}
		}
		return s->node()[kmint::random_int(0, s->node().num_edges())].to().node_id();
	}
	template <class S, class T>
	size_t searching(S s, T t) {
		if (algorithm_.get_conditions_().empty())
		algorithm_.A_star(*s, *t);
		return algorithm_.next_position(*s, *t);
	}
	template <class S, class T>
	size_t chasing(S s, T t){
		if(algorithm_.get_conditions_().empty())
		algorithm_.A_star(*s, *t);
		return algorithm_.next_position(*s,*t);
	}
private:
	algorithm algorithm_;
};

#endif