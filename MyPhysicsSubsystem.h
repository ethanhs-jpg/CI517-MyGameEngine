#pragma once

#include <stdio.h>
// necessary libraries to include
#include <vector>
#include <memory>
// including game math code for basic calculations
#include "GameMath.h"

// ========================
// Custom Physics Subsystem
// ========================

static const float DEFAULT_GRAVITY = -0.1f; // default value of gravity

// class declaration for objects with physics applied
class MyPhysicsObject;

// main class
class MyPhysicsSubsystem
{
	friend class XCube2Engine;
	friend class MyPhysicsObject;

	private:
		MyPhysicsSubsystem(); // private constructor to initialise an object when created

		Vector2f gravity;
		std::vector<std::shared_ptr<MyPhysicsObject>> objects;
	
	public:
		//~MyPhysicsSubsystem(); // public destructor called when an instance goes out of scope to release resources

		void otherFunction();

		// ========================
		// Custom physics functions
		// ========================
		void setGravity(float gravityVal, float worldUpdateInterval); // setting gravity and updating every second
		void update(); // updating the physics state

		void registerObject(std::shared_ptr<MyPhysicsObject>); // registering an object for physics
		void applyGravity(std::shared_ptr<MyPhysicsObject> obj); // applying gravity to respective objects

		/*void movement();
		void collisionHandling();
		void wallCollision();*/
};

class MyPhysicsObject
{
	friend class GraphicsEngine;

	protected:
		Point2 center; // centre point of an object
		float xLen, yLen, xHLen, yHLen; // lengths/half lengths
		Vector2f force; // force applied to an object as a vector

		void applyForce(const Vector2f&); // applying force to the object

	public:
		MyPhysicsObject(const Point2& center, float x, float y);

		Point2 getCenter() { return center; } // getting the centre point of the object
		// getting the lengths/half lengths of the object
		float getLengthX() { return xLen; }
		float getLengthY() { return yLen; }
		float getHalfLengthX() { return xHLen; }
		float getHalfLengthY() { return yHLen; }

		bool isColliding(const MyPhysicsObject& other); // bool function checking for collisions between objects

		// applying horizontal and vertical forces
		void applyForceVertical(const float& speed);
		void applyForceHorizontal(const float& speed);
		// virtual functions for applying gravity in different ways
		virtual void applyGravity(const std::shared_ptr<MyPhysicsSubsystem>& engine);
		virtual void applyAntiGravity(const MyPhysicsSubsystem& engine);
};