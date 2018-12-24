#ifndef KMINTAPP_MOVING_ENTITY_HPP
#define KMINTAPP_MOVING_ENTITY_HPP

#include "kmint/math/vector2d.hpp"


enum class Deceleration { slow = 3, normal = 2, fast = 1 };

class moving_entity {
public:
	moving_entity(double mass, double max_speed, double wander_radius, double wander_distance, double wander_jitter) 
		: mass{ mass }, max_speed{ max_speed }, wander_radius{ wander_radius }, wander_distance{ wander_distance }, wander_jitter{wander_jitter} {}
	//speed of the entity
	kmint::math::vector2d velocity;
	//a normalized vector pointing in the direction the entity is heading.
	kmint::math::vector2d acceleration;
	//weight of the object
	double mass;
	//the maximum speed at which this entity may travel.
	double max_speed;
	//radius of the wander circle 
	double wander_radius;
	//how far away the circle is drawn
	double wander_distance;
	//how far away the dot can be moved per second
	double wander_jitter;
};

#endif