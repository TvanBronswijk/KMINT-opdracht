#ifndef KMINTAPP_RECTANGLE_DRAWABLE_HPP
#define KMINTAPP_RECTANGLE_DRAWABLE_HPP

#include "kmint/play.hpp"
#include "kmint/ui.hpp"

class rectangle_drawable : public kmint::ui::drawable {
public:
	rectangle_drawable(kmint::play::actor const &actor) : drawable{}, actor_{ &actor } {}
	void draw(kmint::ui::frame &f) const override;

private:
	kmint::play::actor const *actor_;
};

#endif
