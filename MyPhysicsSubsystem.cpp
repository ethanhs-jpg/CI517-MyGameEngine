#include "MyPhysicsSubsystem.h"
#include <iostream>

// ========================
// Custom Physics Subsystem
// ========================

// private constructor to initialise an object when created
MyPhysicsSubsystem::MyPhysicsSubsystem()
{

}

// public destructor called when an instance goes out of scope to release resources
MyPhysicsSubsystem:: ~MyPhysicsSubsystem()
{

}

void MyPhysicsSubsystem::otherFunction()
{
	std::cout << "\nOther function called";
}

// ========================
// Custom physics functions
// ========================
void MyPhysicsSubsystem::gravity()
{
	std::cout << "\nGravity function called";
}

void MyPhysicsSubsystem::movement()
{
	std::cout << "\nMovement function called";
}

void MyPhysicsSubsystem::collisionHandling()
{
	std::cout << "\nCollision handling function called";
}

void MyPhysicsSubsystem::wallCollision()
{
	std::cout << "\nWall collision function called";
}