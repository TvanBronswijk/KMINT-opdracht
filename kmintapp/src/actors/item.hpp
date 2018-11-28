#ifndef KMINTAPP_ITEM_HPP
#define KMINTAPP_ITEM_HPP
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"

class cow;
class item : public kmint::play::map_bound_actor {
public:
	item(const char item_,const char *image, kmint::map::map_graph &g);
	void act(kmint::delta_time dt) override;
	kmint::ui::drawable const &drawable() const override { return drawable_; }
	bool incorporeal() const override { return false; }
	kmint::scalar radius() const override { return 16.0; }

	void set_cow(cow& cow) { cow_ = &cow; };

private:
	cow *cow_ = nullptr;
	kmint::play::image_drawable drawable_;
	char item_;
};
#endif /* KMINTAPP_ITEM_HPP */
