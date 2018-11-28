#ifndef KMINTAPP_MOVING_ENTITY_HPP
#define KMINTAPP_MOVING_ENTITY_HPP

#include "kmint/math/vector2d.hpp"

class moving_entity {
public:
	moving_entity(double mass, double max_speed, double max_force, double max_turn_rate) : mass{ mass }, max_speed{ max_speed }, max_force{ max_force }, max_turn_rate{ max_turn_rate } {}
protected:
	//speed of the entity
	kmint::math::vector2d velocity;
	//a normalized vector pointing in the direction the entity is heading.
	kmint::math::vector2d acceleration;
	//weight of the object
	double mass;
	//the maximum speed at which this entity may travel.
	double max_speed;
	//the maximum force this entity can produce to power itself
	//(think rockets and thrust)
	double max_force;
	//the maximum rate (radians per second) at which this vehicle can rotate
	double max_turn_rate;
};

#endif