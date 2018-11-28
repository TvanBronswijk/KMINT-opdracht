#ifndef KMINTAPP_STEERING_BEHAVIOR_HPP
#define KMINTAPP_STEERING_BEHAVIOR_HPP

#include "kmint/math/vector2d.hpp"
#include "moving_enitity.hpp"

class perceptive_actor;
class steering_behavior : public moving_entity {
public:
	steering_behavior(perceptive_actor* actor, double mass, double max_speed, double max_force, double max_turn_rate) : moving_entity(mass, max_speed, max_force, max_turn_rate), actor_{ actor } {};
	kmint::math::vector2d seek(kmint::math::vector2d seek);
	void apply_force(kmint::math::vector2d location);
	void update();

private:
	perceptive_actor* actor_ = nullptr;
};

#endif