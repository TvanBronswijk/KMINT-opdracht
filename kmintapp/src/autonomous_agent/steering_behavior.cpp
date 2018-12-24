#include "steering_behavior.hpp"
#include "autonomous_agent/preceptive_actor.hpp"
#include "kmint/random.hpp"

using namespace kmint;

math::vector2d steering_behavior::evade(perceptive_actor& target) {
	/* Not necessary to include the check for facing direction this time */

	auto to_target = target.location() - actor_->location();
	//the look-ahead time is proportional to the distance between the pursuer
	//and the evader; and is inversely proportional to the sum of the
	//agents' velocities

	const auto length = sqrt(to_target.x() * to_target.x()) + to_target.y() * to_target.y();
	const auto look_ahead_time = length / (actor_->max_speed + target.max_speed);
	//now flee away from predicted future position of the pursuer
	return flee(target.location() + target.velocity * look_ahead_time);

}

math::vector2d steering_behavior::pursuit(perceptive_actor& target){
	auto to_target = target.location() - actor_->location();

	const double relative_heading = math::dot(actor_->heading(), (target.heading()));

	if (dot(to_target, actor_->heading()) > 0 && relative_heading < -0.95)
	{
		std::cout << "LOCATION" << "\n";
		apply_force(seek(target.location()));
	}

	const auto length = sqrt(to_target.x() * to_target.x()) + to_target.y() * to_target.y();
	const auto look_ahead_time = length / (actor_->max_speed + target.max_speed);


	auto force = seek(target.location() + target.velocity * look_ahead_time);
	//auto force = arrive((target.location() + target.velocity * look_ahead_time), Deceleration::fast);

	return force/ actor_->mass;
}


float steering_behavior::random_clamped() {

	return random_int(-1, 1);
}

//kmint::math::vector2d steering_behavior::wander() {
//	//first, add a small random vector to the target’s position (RandomClamped
//	//returns a value between -1 and 1)
//	wander_target += math::vector2d(random_clamped() * actor_->wander_jitter,
//		random_clamped() * actor_->wander_jitter);
//
//	//reproject this new vector back onto a unit circle
//	normalize(wander_target);
//
//	//increase the length of the vector to the same as the radius
//	//of the wander circle
//	wander_target *= actor_->wander_radius;
//
//	//move the target into a position WanderDist in front of the agent
//	math::vector2d target_local = wander_target + math::vector2d(actor_->wander_distance, 0);
//	//project the target into world space
//	math::vector2d targetWorld = PointToWorldSpace(target_local,
//		actor_->Heading(),
//		actor_->Side(),
//		actor_->location());
//	//and steer toward it
//	return targetWorld - actor_->location();
//}

kmint::math::vector2d steering_behavior::arrive(kmint::math::vector2d target, Deceleration deceleration) const {
	math::vector2d to_target = target - actor_->location();
	//calculate the distance to the target position
	double dist_x = actor_->location().x() - to_target.x();
	double dist_y = actor_->location().y() - to_target.y();
	double dist = std::sqrt((dist_x * dist_x + dist_y * dist_y));
	if (dist > 0)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration.
		const double DecelerationTweaker = 200;
		//calculate the speed required to reach the target given the desired
		//deceleration
		double speed = dist / ((double)deceleration * DecelerationTweaker);
		//make sure the velocity does not exceed the max
		if(speed > actor_->max_speed)
		speed = actor_->max_speed;
		//from here proceed just like Seek except we don't need to normalize
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist.
		math::vector2d DesiredVelocity = to_target * speed / dist;
		return (DesiredVelocity - actor_->velocity);
	}
	return math::vector2d{ 0,0 };
}


kmint::math::vector2d steering_behavior::flee(kmint::math::vector2d target) const {
	//only flee if the target is within 'panic distance'. Work in distance
	//squared space.
	auto distance = actor_->range_of_perception();
			
	//only flee if the target is within 'panic distance'. Work in distance
	//squared space.
	const double PanicDistanceSq = actor_->range_of_perception() * actor_->range_of_perception();
	if (math::distance2(actor_->location(), target) > PanicDistanceSq)
	{
		return math::vector2d(0, 0);
	}

	math::vector2d DesiredVelocity = normalize(actor_->location() - target) * actor_->max_speed;
	return (DesiredVelocity - actor_->velocity);
}

math::vector2d steering_behavior::seek(math::vector2d target) const
{
	const auto desired_velocity = normalize(target - actor_->location()) * actor_->max_speed;
	return (desired_velocity - actor_->velocity);
}

void steering_behavior::apply_force(math::vector2d force) {
	actor_->acceleration += force;
}

void steering_behavior::update() {
	// Update velocity
	actor_->velocity += actor_->acceleration;
	// Limit speed
	actor_->move(actor_->velocity);
	// Reset accelerationelertion to 0 each cycle
	actor_->acceleration.x(0);
	actor_->acceleration.y(0);
}