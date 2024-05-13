//
//  MyGame.cpp
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), numKeys(5), box{ 20, 20, 60, 60 }, box2{ 0, 0, 60, 2000 }, score(0), lives(3), gameWon(false), phy({ 0,0 }, 10, 100), phyobj2({ 0,400 }, 2000,10)
{
	gfx->setVerticalSync(true);

	// calling custom subsystem function(s)
	//customSystem->otherFunction();
	// TEST calling physics functions
	//customSystem->gravity();
	//customSystem->movement();
	//customSystem->collisionHandling();

	customSystem->setGravity(2, 2); // (1)value of gravity, (2)interval of application

	// draw points on random locations
	for (int i = 0; i < numKeys; i++)
	{
		std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
		k->isAlive = true;
		k->pos = Point2(getRandom(0, 600), getRandom(0, 500)); // x, y (random range)
		gameKeys.push_back(k);
	}
}

// destructor
MyGame::~MyGame() {

}

// handling gameplay events
void MyGame::handleKeyEvents()
{
	// speed and acceleration values defined here
	int speed = 3;
	float acceleration = 2;

	bool wPressed, sPressed, aPressed, dPressed;

	if (eventSystem->isPressed(Key::W)) // up
	{
		wPressed = true;
		phy.applyForceVertical(speed, -acceleration);
	}
	else wPressed = false;

	if (eventSystem->isPressed(Key::S)) // down
	{
		sPressed = true;
		phy.applyForceVertical(speed, acceleration);
	}
	else sPressed = false;

	if (eventSystem->isPressed(Key::A)) // left
	{
		aPressed = true;
		phy.applyForceHorizontal(speed, -acceleration);
	}
	else aPressed = false;

	if (eventSystem->isPressed(Key::D)) // right
	{
		dPressed = true;
		phy.applyForceHorizontal(speed, acceleration);
	}
	else dPressed = false;

	//phy.applyDrag();

	// applying drag vertically/horizontally if relevant keys are released
	//if (!wPressed && !sPressed) phy.applyDrag();
	//if (!aPressed && !dPressed) phy.applyDrag();
}

void MyGame::update()
{
	handleKeyEvents();
	//phy.applyDrag();

	// calling screenLimit handling before x/y coords are updated for more effective collision handling
	phy.screenLimit();

	// getting the x and y center coords of each box
	box.x = phy.getCenter().x;
	box.y = phy.getCenter().y;

	box2.x = phyobj2.getCenter().x;
	box2.y = phyobj2.getCenter().y;

	if (!phy.isColliding(phyobj2))
	{
		//phy.applyGravity(customSystem);
	}

	for (auto key : gameKeys)
	{
		if (key->isAlive && (box.x == key->pos.x && box.y == key->pos.y))
		{
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}

	if (numKeys == 0)
	{
		gameWon = true;
	}
}

void MyGame::render()
{
	// drawing the primary box
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	
	// drawing secondary box
	gfx->setDrawColor(SDL_COLOR_GREEN);
	gfx->fillRect(box2.x, box2.y, box2.h, box2.w);

	// drawing keys
	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
	{
		if (key->isAlive)
			gfx->drawCircle(key->pos, 5);
	}
}

void MyGame::renderUI()
{
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);

	if (gameWon)
	{
		std::cout << "You won: " << score;
	}
}
