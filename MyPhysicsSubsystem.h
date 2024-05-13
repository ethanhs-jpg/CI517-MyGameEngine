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

// NOTE: The basis of this code was provided as part of the Assessment Tutorials

static const float DEFAULT_GRAVITY = -0.1f; // default value of gravity

// class declaration for objects with physics applied
class PhysicsObject;

// main class
class MyPhysicsSubsystem
{
	friend class XCube2Engine;
	friend class PhysicsObject;

	private:
		MyPhysicsSubsystem(); // private constructor to initialise an object when created

		Vector2f gravity;
		std::vector<std::shared_ptr<PhysicsObject>> objects;
	
	public:
		//~MyPhysicsSubsystem(); // public destructor called when an instance goes out of scope to release resources

		// ========================
		// Custom physics functions
		// ========================
		void setGravity(float gravityVal, float worldUpdateInterval); // setting gravity and updating every second
		void update(); // updating the physics state

		void registerObject(std::shared_ptr<PhysicsObject>); // registering an object for physics
		void applyGravity(std::shared_ptr<PhysicsObject> obj); // applying gravity to respective objects

		//void otherFunction();

		//void movement();
		//void collisionHandling();
		//void wallCollision(std::shared_ptr<PhysicsObject> obj); // declaring wall collision function
};

class PhysicsObject
{
	friend class GraphicsEngine;

	protected:
		Point2 center; // centre point of an object
		float lX, lY, hlX, hlY; // lengths/half lengths
		Vector2f force; // force applied to an object as a vector

		float xVel, yVel; // x and y velocity variables
		
		float frameTime = static_cast<float>(1) / 60; // frametime variable for smooth physics

		void applyForce(const Vector2f&); // applying force to the object

	public:
		PhysicsObject(const Point2& center, float x, float y);

		Point2 getCenter() { return center; } // getting the centre point of the object
		// getting the lengths/half lengths of the object
		float getLengthX() { return lX; }
		float getLengthY() { return lY; }
		float getHalfLengthX() { return hlX; }
		float getHalfLengthY() { return hlY; }

		bool isColliding(const PhysicsObject& other); // bool function checking for collisions between objects
		
		// screen limit collision handling
		void screenLimit();

		// applying horizontal and vertical forces
		void applyForceVertical(const float& speed, const float& acceleration);
		void applyForceHorizontal(const float& speed, const float& acceleration);

		// applying drag
		void applyDrag();

		// virtual functions for applying gravity in different ways
		virtual void applyGravity(const std::shared_ptr<MyPhysicsSubsystem>& engine); // overrides applyGravity() above
		virtual void applyAntiGravity(const MyPhysicsSubsystem& engine);
};