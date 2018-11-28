#ifndef KMINTAPP_HARE_HPP
#define KMINTAPP_HARE_HPP
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/random.hpp"
#include "../pathfinding/algorithm.hpp"

class cow;
class hare : public kmint::play::map_bound_actor {
public:
	hare(kmint::map::map_graph &g);
	void act(kmint::delta_time dt) override;
	kmint::ui::drawable const &drawable() const override { return drawable_; }
	void set_cow(cow &c) { cow_ = &c; }
	bool incorporeal() const override { return false; }
	kmint::scalar radius() const override { return 16.0; }
private:
	kmint::play::image_drawable drawable_;
	cow *cow_ = nullptr;
};
#endif /* KMINTAPP_HARE_HPP */