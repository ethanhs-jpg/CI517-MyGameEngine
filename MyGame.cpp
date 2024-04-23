//
//  MyGame.cpp
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), numKeys(5), box{ 20, 20, 60, 60 }, box2{ 0, 0, 60, 2000 }, score(0), lives(3), gameWon(false), phy({ 0,0 }, 10, 100), phyobj2({ 0,540 }, 2000,10)
{
	gfx->setVerticalSync(true);

	// calling custom subsystem function(s)
	//customSystem->otherFunction();
	// TEST calling physics functions
	/*customSystem->gravity();
	customSystem->movement();
	customSystem->collisionHandling();
	customSystem->wallCollision();*/

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
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) // up
	{
		phy.applyForceVertical(15);
	}
	if (eventSystem->isPressed(Key::S)) // down
	{
		phy.applyForceVertical(-speed);
	}
	if (eventSystem->isPressed(Key::A)) // left
	{
		phy.applyForceHorizontal(speed);
	}
	if (eventSystem->isPressed(Key::D)) // right
	{
		phy.applyForceHorizontal(-speed);
	}
}

void MyGame::update()
{
	// getting the x and y center coords of each box
	box.x = phy.getCenter().x;
	box.y = phy.getCenter().y;

	box2.x = phyobj2.getCenter().x;
	box2.y = phyobj2.getCenter().y;

	if (!phy.isColliding(phyobj2))
	{
		phy.applyGravity(customSystem);
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
