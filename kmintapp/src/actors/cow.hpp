#ifndef KMINTAPP_COW_HPP
#define KMINTAPP_COW_HPP
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "hare.hpp"
#include "kmint/map/map.hpp"
#include "../pathfinding/algorithm.hpp"
#include "kmint/random.hpp"

class cow : public kmint::play::map_bound_actor {
public:
	cow(const kmint::map::map_graph &g, const kmint::map::map_node &initial_node, algorithm &a);
//	cow(const kmint::map::map_graph &g, const kmint::map::map_node &initial_node, algorithm &a);
	// wordt elke game tick aangeroepen
	void act(kmint::delta_time dt) override;
	kmint::ui::drawable const &drawable() const override { return drawable_; }
	// als incorporeal false is, doet de actor mee aan collision detection
	bool incorporeal() const override { return false; }
	// geeft de radius van deze actor mee. Belangrijk voor collision detection
	kmint::scalar radius() const override { return 16.0; }
	void set_hare(hare &h) { hare_ = &h; }

private:
	// hoeveel tijd is verstreken sinds de laatste beweging
	kmint::delta_time t_passed_{};
	// weet hoe de koe getekend moet worden
	kmint::play::image_drawable drawable_;
	// edge_type const *next_edge_{nullptr};
	// edge_type const *pick_next_edge();
	hare *hare_ = nullptr;
	algorithm &algorithm_;
	
};
#endif /* KMINTAPP_COW_HPP */