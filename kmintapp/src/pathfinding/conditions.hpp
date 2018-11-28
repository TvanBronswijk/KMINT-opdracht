#ifndef KMINTAPP_CONDITIONS_HPP
#define KMINTAPP_CONDITIONS_HPP

class conditions {
public:
	conditions() : conditions(9999) {}
	conditions(size_t weight): weight_{ weight }{}

	size_t weight_; // dijkstra weight

};


#endif