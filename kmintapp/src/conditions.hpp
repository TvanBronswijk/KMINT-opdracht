#ifndef KMINTAPP_CONDITIONS_HPP
#define KMINTAPP_CONDITIONS_HPP

class conditions {
public:
	conditions(size_t weight, size_t distance): weight_ { weight }, distance_{ distance } {}

	size_t weight_; // dijkstra weight
	size_t distance_;

};


#endif