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

	// updating y coordinate given updated vertical velocity
	center.y += yVel;

	//std::cout << "\nAcceleration: " << acceleration;
	//std::cout << "\nyVel: " << yVel;
}

void PhysicsObject::applyForceHorizontal(const float& speed, const float& acceleration)
{
	// integrating acceleration over time to update velocity
	xVel += acceleration * frameTime;

	// limiting velocity to max speed
	if (xVel > speed) xVel = speed;
	if (xVel < -speed) xVel = -speed;

	// updating x coordinate given updated horizontal velocity
	center.x += xVel;
	
	//std::cout << "\nAcceleration: " << acceleration;
	//std::cout << "\nxVel: " << xVel;
}

void PhysicsObject::applyHorizontalDrag(const float& dragCoefficient)
{
	if (xVel > 0.0f)
	{
		xVel -= dragCoefficient;
		if (xVel < 0.0f) xVel = 0.0f;
	}
	else if (xVel < 0.0f)
	{
		xVel += dragCoefficient;
		if (xVel > 0.0f) xVel = 0.0f;
	}

	center.x += xVel;
}

void PhysicsObject::applyVerticalDrag(const float& dragCoefficient)
{
	if (yVel > 0.0f)
	{
		yVel -= dragCoefficient;
		if (yVel < 0.0f) yVel = 0.0f;
	}
	else if (yVel < 0.0f)
	{
		yVel += dragCoefficient;
		if (yVel > 0.0f) yVel = 0.0f;
	}

	center.y += yVel;
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
	//playerObject = obj;
}

void MyPhysicsSubsystem::update()
{
	//objects.applyForceHorizontal(const float& speed, const float& acceleration);
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
void PhysicsObject::screenLimit(const float& width, const float& height)
{
	//std::cout << "\nScreen limit handling function called\n";

	// !!! Code sourced and adapted from my CI411 SDL game !!!
	// Limit to edges
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