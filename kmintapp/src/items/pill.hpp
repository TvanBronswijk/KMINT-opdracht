#ifndef KMINTAPP_PILL_HPP
#define KMINTAPP_PILL_HPP
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/map/map.hpp"

static const char *pill = "resources/pill.png";
class pill {
public:
	pill(const kmint::map::map_graph &g, const kmint::map::map_node &initial_node) : play::map_bound_actor{ g, initial_node },
		drawable_{ *this,kmint::graphics::image{pill, 0.1} }, {}

private:
	kmint::play::image_drawable drawable_;
};
#endif /* KMINTAPP_PILL_HPP */
