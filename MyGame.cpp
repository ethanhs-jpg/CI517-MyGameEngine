//
//  MyGame.cpp
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), numKeys(15), box{ 20, 20, 300, 300 }
{
	gfx->setVerticalSync(true);

	// calling custom subsystem function(s)
	customSystem->otherFunction();
	// TEST calling physics functions
	customSystem->gravity();
	customSystem->movement();
	customSystem->collisionHandling();
	customSystem->wallCollision();

	// draw points on random locations
	for (int i = 0; i < numKeys; i++)
	{
		std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
		k->isAlive = true;
		k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
		gameKeys.push_back(k);
	}
}
MyGame::~MyGame() {

}

void MyGame::handleKeyEvents()
{

}

void MyGame::update()
{

}

void MyGame::render()
{
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	gfx->setDrawColor(SDL_COLOR_BLUE);

	gfx->fillRect(12, 2, 30, 30);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
	{
		if (key->isAlive)
			gfx->drawCircle(key->pos, 5);
	}
}

void MyGame::renderUI()
{

}
