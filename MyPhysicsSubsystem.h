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

		void setGravity(float gravityVal, float worldUpdateInterval); // setting gravity and updating every second
		void update(); // updating the physics state

		void registerObject(std::shared_ptr<PhysicsObject>); // registering an object for physics
		void applyGravity(std::shared_ptr<PhysicsObject> obj); // applying gravity to respective objects
};

class PhysicsObject
{
	friend class GraphicsEngine;

	protected:
		Point2 center; // centre point of an object
		float lX, lY, hlX, hlY; // lengths/half lengths
		Vector2f force; // force applied to an object as a vector
		//Point2 previousPos; // previous position of an object
		float xVel, yVel; // x and y velocity variables
		void applyForce(const Vector2f&); // applying force to the object

	public:
		PhysicsObject(const Point2& center, float x, float y); // spawn position (x,y), collision width, collision height

		Point2 getCenter() { return center; } // getting the centre point of the object
		// getting the lengths/half lengths of the object
		float getLengthX() { return lX; }
		float getLengthY() { return lY; }
		float getHalfLengthX() { return hlX; }
		float getHalfLengthY() { return hlY; }
		// getting velocities along each axis
		float getVelX() { return xVel; }
		float getVelY() { return yVel; }
		bool isColliding(const PhysicsObject& other); // bool function checking for collisions between objects
		
		// ========================
		// Custom physics functions
		// ========================
		// screen limit collision handling with adjustable width and height
		void screenLimit(const float& screenWidth, const float& screenHeight);
		// applying horizontal and vertical forces
		void applyForceVertical(const float& speed, const float& acceleration);
		void applyForceHorizontal(const float& speed, const float& acceleration);
		//void applyDrag(); // applying drag
		void applyHorizontalDrag(const float& dragCoefficient);
		void applyVerticalDrag(const float& dragCoefficient);
		// virtual functions for applying gravity in different ways
		virtual void applyGravity(const std::shared_ptr<MyPhysicsSubsystem>& engine); // overrides applyGravity() above
		virtual void applyAntiGravity(const MyPhysicsSubsystem& engine);
};