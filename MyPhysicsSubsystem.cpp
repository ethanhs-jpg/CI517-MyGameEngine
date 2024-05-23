#include "MyPhysicsSubsystem.h"
#include <iostream>

// ========================
// Custom Physics Subsystem
// ========================

// private constructor to initialise an object when created
//MyPhysicsSubsystem::MyPhysicsSubsystem()
//{
//
//}

// public destructor called when an instance goes out of scope to release resources
//MyPhysicsSubsystem:: ~MyPhysicsSubsystem()
//{
//
//}

// NOTE: The basis of this code was provided as part of the Assessment Tutorials

// initialised for each object using the physics engine
PhysicsObject::PhysicsObject(const Point2& center, float x, float y) : center(center), lX(x), lY(y), hlX(x / 2.0f), hlY(y / 2.0f), force(0.0f, 0.0f)
{
	// Easter Egg output
	std::cout << "ETHAN_HOSFORD-CI517-2023-24\n";
}

bool PhysicsObject::isColliding(const PhysicsObject& other)
{
	// rect of the current object
	Rectf r1 = { center.x - hlX, center.y - hlY, lX, lY };
	// rect of any other object being collided with
	Rectf r2 = { other.center.x - other.hlX, other.center.y - other.hlY, other.lX, other.lY };

	return r1.intersects(r2); // returning true/false for if an intersect occurs
	//std::cout << r1.intersects(r2);
}

void PhysicsObject::applyForce(const Vector2f& v)
{
	force = v;
}

void PhysicsObject::applyGravity(const std::shared_ptr<MyPhysicsSubsystem>& engine)
{
	center += engine->gravity;
}

// ==========================
// Vertical/Horizontal Forces
// ==========================

void PhysicsObject::applyForceVertical(const float& speed, const float& acceleration)
{
	// integrating acceleration over time to update velocity
	yVel += acceleration; // removed "* frametime" as this was causing issues

	// limiting velocity to max speed
	if (yVel > speed) yVel = speed;
	if (yVel < -speed) yVel = -speed;

	// updating y coordinate given updated vertical velocity
	center.y += yVel;
}

void PhysicsObject::applyForceHorizontal(const float& speed, const float& acceleration)
{
	// integrating acceleration over time to update velocity
	xVel += acceleration; // removed "* frametime" as this was causing issues

	// limiting velocity to max speed
	if (xVel > speed) xVel = speed;
	if (xVel < -speed) xVel = -speed;

	// updating x coordinate given updated horizontal velocity
	center.x += xVel;
}

// ========================
// Vertical/Horizontal Drag
// ========================

// applying drag on each axis separately
void PhysicsObject::applyHorizontalDrag(const float& dragCoefficient)
{
	if (std::abs(xVel) > dragCoefficient) // if x velocity is greater than drag coefficient
	{
		// adding/subtracting drag coeff. depending on direction
		if (xVel > 0.0f) xVel -= dragCoefficient;
		else if (xVel < 0.0f) xVel += dragCoefficient;
	}
	else xVel = 0.0f; // setting velocity to 0 otherwise

	center.x += xVel; // updating the x coordinate of the object

	//std::cout << "applyHorizontalDrag called";
	/*if (xVel > 0.0f) // if the object is moving horizontally
	{
		xVel -= dragCoefficient; // subtract the drag coefficient from the velocity every function call
		if (xVel < 0.0f) xVel = 0.0f; // stopping movement if velocity is below a certain threshold
	}
	else if (xVel < 0.0f) // same logic for the opposing direction
	{
		xVel += dragCoefficient;
		if (xVel > 0.0f) xVel = 0.0f;
	}*/
}

void PhysicsObject::applyVerticalDrag(const float& dragCoefficient)
{
	if (std::abs(yVel) > dragCoefficient) // if y velocity is greater than drag coefficient
	{
		// adding/subtracting drag coeff. depending on direction
		if (yVel > 0.0f) yVel -= dragCoefficient;
		else if (yVel < 0.0f) yVel += dragCoefficient;
	}
	else yVel = 0.0f; // setting velocity to 0 otherwise

	center.y += yVel; // updating the y coordinate of the object

	//if (yVel > 0.0f) // if the object is moving vertically
	//{
	//	yVel -= dragCoefficient; // subtract the drag coefficient from the velocity every function call
	//	if (yVel < 0.0f) yVel = 0.0f; // stopping movement if velocity is below a certain threshold
	//}
	//else if (yVel < 0.0f) // same logic for the opposing direction
	//{
	//	yVel += dragCoefficient;
	//	if (yVel > 0.0f) yVel = 0.0f;
	//}
}

/*void PhysicsObject::applyDrag()
{
	//std::cout << "\napplyDrag called";

	// horizontal drag
	if (std::abs(xVel) > 0.1f) xVel *= 0.95f;
	else xVel = 0;
	//if (abs(xVel) < -0.1f) xVel *= 0.9f; else xVel = 0;

	// vertical drag
	if (std::abs(yVel) > 0.1f) yVel *= 0.95f;
	else yVel = 0;
	//if (abs(yVel) < -0.1f) yVel *= 0.9f; else yVel = 0;

	center.x += xVel;
	center.y += yVel;

	std::cout << "\nDrag applied: xVel: " << xVel << " yVel: " << yVel;
}*/

void PhysicsObject::applyAntiGravity(const MyPhysicsSubsystem& engine)
{
	center -= engine.gravity;
}

MyPhysicsSubsystem::MyPhysicsSubsystem() : gravity(Vector2f(0, DEFAULT_GRAVITY))
{

}

void MyPhysicsSubsystem::setGravity(float val, float interval)
{
	gravity = Vector2f(0, val * interval);
}

void MyPhysicsSubsystem::registerObject(std::shared_ptr<PhysicsObject> obj)
{
	objects.push_back(obj);
}

void MyPhysicsSubsystem::update()
{

}

// =============
// Screen Limits
// =============

// function for handling screen limits
void PhysicsObject::screenLimit(const float& width, const float& height)
{
	// Code sourced and adapted from my CI411 SDL game
	// limit to edges
	bool stopMoving = false;
	if (center.x + hlX > width) // if obj exceeds right edge
	{
		stopMoving = true;
		center.x = width - hlX;
	}
	if (center.x - hlX < 0) // if obj exceeds left edge
	{
		stopMoving = true;
		center.x = hlX;
	}
	if (center.y + hlY > height) // if obj exceeds bottom edge
	{
		stopMoving = true;
		center.y = height - hlY;
	}
	if (center.y - hlY < 0) // if obj exceeds top edge
	{
		// adjusted to account for half height
		stopMoving = true;
		center.y = hlY;
	}

	if (stopMoving)
	{
		// stopping movement when colliding with bounds
		xVel = 0;
		yVel = 0;
	}
}