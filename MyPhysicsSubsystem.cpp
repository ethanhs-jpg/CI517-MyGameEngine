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
	Rectf r1 = { center.x - hlX, center.y - hlY, lX, lY }; // rect of the current object
	Rectf r2 = { other.center.x - other.hlX, other.center.y - other.hlY, other.lX, other.lY }; // rect of any other object being collided with

	return r1.intersects(r2); // returning true/false for if an intersect occurs
}

void PhysicsObject::applyForce(const Vector2f& v)
{
	force = v;
}

void PhysicsObject::applyGravity(const std::shared_ptr<MyPhysicsSubsystem>& engine)
{
	center += engine->gravity;
}

void PhysicsObject::applyForceVertical(const float& speed, const float& acceleration)
{
	// integrating acceleration over time to update velocity
	yVel += acceleration * frameTime;

	// limiting velocity to max speed
	if (yVel > speed) yVel = speed;
	if (yVel < -speed) yVel = -speed;

	center.y += yVel;

	//std::cout << "\nAcceleration: " << acceleration;
	std::cout << "\nyVel: " << yVel;
}

void PhysicsObject::applyForceHorizontal(const float& speed, const float& acceleration)
{
	// integrating acceleration over time to update velocity
	xVel += acceleration * frameTime;

	// limiting velocity to max speed
	if (xVel > speed) xVel = speed;
	if (xVel < -speed) xVel = -speed;

	center.x += xVel;
	
	//std::cout << "\nAcceleration: " << acceleration;
	std::cout << "\nxVel: " << xVel;
}

void PhysicsObject::applyDrag()
{
	//std::cout << "\napplyDrag called";

	// horizontal drag
	if (abs(xVel) > 0.2f) xVel *= 0.9f; else xVel = 0;
	if (abs(xVel) < -0.2f) xVel *= 0.9f; else xVel = 0;

	// vertical drag
	if (abs(yVel) > 0.2f) yVel *= 0.9f; else yVel = 0;
	if (abs(yVel) < -0.2f) yVel *= 0.9f; else yVel = 0;

	center.x += xVel;
	center.y += yVel;
}

void PhysicsObject::applyAntiGravity(const MyPhysicsSubsystem& engine)
{
	center -= engine.gravity;
}

// ========================

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

// ========================

//void MyPhysicsSubsystem::otherFunction()
//{
//	std::cout << "\nOther function called";
//}

// ========================
// Custom physics functions
// ========================
//void MyPhysicsSubsystem::gravity()
//{
//	std::cout << "\nGravity function called";
//}
//
//void MyPhysicsSubsystem::movement()
//{
//	std::cout << "\nMovement function called";
//}
//
//void MyPhysicsSubsystem::collisionHandling()
//{
//	std::cout << "\nCollision handling function called";
//}

// function for handling screen limits
void PhysicsObject::screenLimit()
{
	//std::cout << "\nScreen limit handling function called\n";

	// !!! Code sourced and adapted from my CI411 SDL game !!!
	// Limit to edges
	bool stopMoving = false;
	if (center.x + hlX > 800) // if obj exceeds right edge
	{
		stopMoving = true;
		center.x = 800 - hlX;
	}
	if (center.x - hlX < 0) // if obj exceeds left edge
	{
		stopMoving = true;
		center.x = hlX;
	}
	if (center.y + hlY > 600) // if obj exceeds bottom edge
	{
		stopMoving = true;
		center.y = 600 - hlY;
	}
	if (center.y < 0) // if obj exceeds top edge
	{
		stopMoving = true;
		center.y = 0;
	}

	if (stopMoving)
	{
		// stopping movement when colliding with bounds
		//applyForceVertical(0, 1.5);
		//applyForceHorizontal(0, 1.5);
		
		xVel = 0;
		yVel = 0;
	}
}