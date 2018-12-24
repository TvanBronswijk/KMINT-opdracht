#ifndef KMINTAPP_STEERING_BEHAVIOR_HPP
#define KMINTAPP_STEERING_BEHAVIOR_HPP

#include "kmint/math/vector2d.hpp"
#include "moving_enitity.hpp"

class perceptive_actor;
class steering_behavior{
public:
	steering_behavior(perceptive_actor* actor) : actor_{ actor } 
	{
		//wander_target = kmint::math::vector2d(actor_->location().x() + actor_->wander_radius,actor_->location().y);
	};
	kmint::math::vector2d pursuit(perceptive_actor& seek);
	kmint::math::vector2d evade(perceptive_actor& seek);
	//kmint::math::vector2d wander();
	kmint::math::vector2d seek(kmint::math::vector2d target) const;
	kmint::math::vector2d flee(kmint::math::vector2d target) const;
	kmint::math::vector2d arrive(kmint::math::vector2d target, Deceleration deceleration) const;
	void apply_force(kmint::math::vector2d location);
	void update();

private:
	float random_clamped();
	//kmint::math::vector2d wander_target = kmint::math::vector2d{ 0,0 };
	perceptive_actor* actor_ = nullptr;
};

#endif