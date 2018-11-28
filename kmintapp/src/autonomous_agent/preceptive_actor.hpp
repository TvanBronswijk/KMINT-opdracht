#ifndef KMINTAPP_PERCEPTIVE_ACTOR_HPP
#define KMINTAPP_PERCEPTIVE_ACTOR_HPP

#include <iostream>
#include "kmint/math/vector2d.hpp"
#include "kmint/ui.hpp"
#include "kmint/primitives.hpp"
#include "kmint/play.hpp"
#include "autonomous_agent/rectangle_drawable.hpp"
#include "autonomous_agent/steering_behavior.hpp"

class perceptive_actor : public kmint::play::free_roaming_actor {
public:
	perceptive_actor(kmint::math::vector2d location, bool shout, double mass, double max_speed, double max_force, double max_turn_rate)
		: free_roaming_actor{ location }, drawable_{ *this }, shout_{ shout }, steering_{ steering_behavior(this, mass, max_speed, max_force, max_turn_rate) } {}

	const kmint::ui::drawable &drawable() const override { return drawable_; }
	void move(kmint::math::vector2d delta) { location(location() + delta); }
	void act(kmint::delta_time dt) override {
		if (target_ != nullptr) {
			kmint::math::vector2d seek = steering_.seek(target_->location());
			steering_.apply_force(seek);
			steering_.update();
		}
		if (!shout_)
			return;
		for (auto i = begin_perceived(); i != end_perceived(); ++i) {
			std::cout << "saw something at " << i->location().x() << ", "
				<< i->location().y() << "\n";
		}
	}
	void set_target(perceptive_actor& target) {
		this->target_ = &target;
	}

	// belangrijk! Dit zorgt ervoor dat jouw actor andere actors kan zien
	bool perceptive() const override { return true; }

	// straal waarin een actor andere actors kan waarnemen
	kmint::scalar range_of_perception() const override { return 30.0f; }

private:
	perceptive_actor* target_ = nullptr;
	steering_behavior steering_;
	rectangle_drawable drawable_;
	bool shout_;
};

#endif
