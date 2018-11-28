#include "steering_behavior.hpp"
#include "autonomous_agent/preceptive_actor.hpp"

using namespace kmint;

math::vector2d steering_behavior::seek(math::vector2d seek) {
	math::vector2d desired = (seek - this->actor_->location()); // A vector pointing from the position to the target

	// Scale to maximum speed
	desired.x(desired.x() + max_speed);
	desired.y(desired.y() + max_speed);


	// Steering = Desired minus velocity
	math::vector2d steer((desired.x() - velocity.x()), (desired.y() - velocity.y()));
	if (steer.x() > (actor_->location().x() + max_force))
		steer.x(actor_->location().x() + max_force);
	if (steer.y() > (actor_->location().y() + max_force))
		steer.y(actor_->location().y() + max_force);

	return steer;
}

void steering_behavior::apply_force(math::vector2d force) {
	acceleration += force;
}

void steering_behavior::update() {
	// Update velocity
	velocity += acceleration;
	// Limit speed
	if (velocity.x() > max_speed)
		velocity.x(max_speed);
	if (velocity.y() > max_speed)
		velocity.y(max_speed);
	if (velocity.x() < (max_speed - (max_speed + max_speed)))
		velocity.x((max_speed - (max_speed + max_speed)));
	if (velocity.y() < (max_speed - (max_speed + max_speed)))
		velocity.y((max_speed - (max_speed + max_speed)));
	actor_->move(velocity);
	// Reset accelerationelertion to 0 each cycle
	acceleration.x(0);
	acceleration.y(0);
}