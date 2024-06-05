//
//  MyGame.cpp
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), numKeys(10), box{ 0, 0, 50, 50 }, box2{ 0, 0, 60, 2000 }, score(0), lives(3), gameWon(false), phy({ 0,0 }, 50, 50), phyobj2({ 0,540 }, 2000,10)
{
	gfx->setVerticalSync(true);

	TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 24); // opening the font stored in the project
	gfx->useFont(font); // setting "font" as the font to use in the game

	customSystem->setGravity(2, 1); // (1)value of gravity, (2)interval of application

	// draw points on random locations
	for (int i = 0; i < numKeys; i++)
	{
		std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
		k->isAlive = true;
		k->pos = Point2(getRandom(50, 750), getRandom(50, 540)); // x, y (random range)
		gameKeys.push_back(k);
	}

	// loading sprite texture to a temporary surface variable
	SDL_Surface* temp1 = IMG_Load("assets/sprites/CatSprite.png");
	if (!temp1) // if no image is loaded
	{
		std::cout << "\nFailed to load sprite image: " << IMG_GetError();
	}
	else
	{
		// converting the temp surface into a renderable texture
		sprite1 = SDL_CreateTextureFromSurface(GraphicsEngine::getRenderer(), temp1); // added getRenderer function for this
		SDL_FreeSurface(temp1); // freeing the temp surface
		if (!sprite1) std::cout << "\nFailed to create sprite texture: " << SDL_GetError(); // final error check
	}

	// loading music and sound effects
	backgroundMusic = Mix_LoadMUS("assets/audio/8bit-spaceshooter.mp3");
	collectCoin = Mix_LoadWAV("assets/audio/coin.wav"); // TYPO: had "-" instead of "="
	Mix_Volume(-1, 24);
	Mix_VolumeMusic(24);

	// playing background music at initialisation
	Mix_PlayMusic(backgroundMusic, -1);
}

// destructor
MyGame::~MyGame() {
	// texture cleanup
	if (sprite1) SDL_DestroyTexture(sprite1);
	// sound cleanup
	Mix_FreeMusic(backgroundMusic);
	Mix_FreeChunk(collectCoin);
}

// handling gameplay events
void MyGame::handleKeyEvents()
{
	// speed and acceleration values defined here
	speed = 4;
	acceleration = 0.1f;
	dragCoefficient = 0.2f;

	//xForce = 0.0f;
	//yForce = 0.0f;
	xKeyPressed = false;
	yKeyPressed = false;

	if (eventSystem->isPressed(Key::W)) // up
	{
		//phy.applyForceVertical(speed, -acceleration);
		yKeyPressed = true;
		yForce -= acceleration;
	}
	if (eventSystem->isPressed(Key::S)) // down
	{
		//phy.applyForceVertical(speed, acceleration);
		yKeyPressed = true;
		yForce += acceleration;
	}
	if (eventSystem->isPressed(Key::A)) // left
	{
		//phy.applyForceHorizontal(speed, -acceleration);
		xKeyPressed = true;
		xForce -= acceleration;
	}
	if (eventSystem->isPressed(Key::D)) // right
	{
		//phy.applyForceHorizontal(speed, acceleration);
		xKeyPressed = true;
		xForce += acceleration;
	}

	//std::cout << keyPressed;

	// applying forces in each direction
	phy.applyForceHorizontal(speed, xForce);
	phy.applyForceVertical(speed, yForce);

	// checking if no keys are pressed for either axis
	if (!xKeyPressed)
	{
		// applying horizontal drag and resetting force
		phy.applyHorizontalDrag(dragCoefficient);
		xForce = 0.0f;
	}
	if (!yKeyPressed)
	{
		// applying vertical drag and resetting force
		phy.applyVerticalDrag(dragCoefficient);
		yForce = 0.0f;
	}
}

void MyGame::update()
{
	//Point2 previousPos = phy.getCenter();

	// calling screenLimit handling before x/y coords are updated
	phy.screenLimit(800.0, 600.0); // providing current screen dimensions
	//phy.applyDrag();

	// getting the x and y center coords of each box
	box.x = phy.getCenter().x - box.w / 2; // subtracting box width for the true centre
	box.y = phy.getCenter().y - box.h / 2; // subtracting box height for the true centre

	box2.x = phyobj2.getCenter().x;
	box2.y = phyobj2.getCenter().y;

	/*if (!phy.isColliding(phyobj2))
	{
		phy.applyGravity(customSystem);
	}*/

	if (phy.isColliding(phyobj2))
	{
		std::cout << "isColliding ";
		//phy.setCenter(previousPos);

	}

	/*for (auto &key : gameKeys)
	{
		if (box.x == key->pos.x && box.y == key->pos.y)
		{
			score += 200;
			key->isAlive = false;
			numKeys--;

			std::cout << "\n" << score;

			Mix_PlayChannel(-1, collectCoin, 0);
		}
	}*/

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 100;
			key->isAlive = false;
			numKeys--;

			std::cout << "Key collected";

			Mix_PlayChannel(-1, collectCoin, 0); // WORKING
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
	/*gfx->setDrawColor(SDL_COLOR_RED);
	gfx->fillRect(box.x, box.y, box.h, box.w);
	gfx->setDrawColor(SDL_COLOR_ORANGE);
	gfx->drawRect(box);*/

	// drawing primary box with a sprite instead
	SDL_Rect dstRect = { box.x, box.y, box.w, box.h };
	gfx->drawTexture(sprite1, &dstRect);
	
	// drawing secondary box
	gfx->setDrawColor(SDL_COLOR_GRAY);
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
	// text config and rendering for useful physics information
	std::string screenText;

	// adding values to the text output
	screenText = "xVel: " + std::to_string(phy.getVelX());
	screenText += "  yVel: " + std::to_string(phy.getVelY());
	screenText += "  xPos: " + std::to_string(phy.getCenter().x);
	screenText += "  yPos: " + std::to_string(phy.getCenter().y);

	// rendering the text to the screen
	gfx->setDrawColor(SDL_COLOR_WHITE);
	gfx->drawText(screenText, 16, 560);

	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 700 - scoreStr.length(), 25); // drawing score text on screen

	// displaying win state text on screen
	if (gameWon)
	{
		//std::cout << "You won: " << score;
		gfx->drawText("YOU WIN", 335, 400);

		
	}
}
