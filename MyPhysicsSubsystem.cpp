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

PhysicsObject::PhysicsObject(const Point2& center, float x, float y) : center(center), lX(x), lY(y), hlX(x / 2.0f), hlY(y / 2.0f), force(0.0f, 0.0f)
{


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

void PhysicsObject::applyForceVertical(const float& speed)
{
	center.y -= speed;
}

void PhysicsObject::applyForceHorizontal(const float& speed)
{
	center.x -= speed;
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
//
//void MyPhysicsSubsystem::wallCollision()
//{
//	std::cout << "\nWall collision function called";
//}