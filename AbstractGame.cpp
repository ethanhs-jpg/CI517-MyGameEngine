#include "AbstractGame.h"
//#include <iostream>
using namespace std;

AbstractGame::AbstractGame() : running(true), gameTime(0.0)
{
	cout << "Abstract Game started" << endl;
	std::shared_ptr<XCube2Engine> engine = XCube2Engine::getInstance();
	
	//step 6
	gfx = engine->getGraphicsEngine();
	eventSystem = engine->getEventEngine();
	audioSystem = engine->getAudioEngine();
	customSystem = engine->getMyPhysicsSubsystem(); // custom subsystem for physics
}

AbstractGame::~AbstractGame()
{
	cout << "Abstract Game ended" << endl;
	
	//step 7
	gfx.reset();
	eventSystem.reset();
	audioSystem.reset();
	customSystem.reset(); // resetting the physics subsystem
	
	// kill engine
	XCube2Engine::quit();

	// end of program debug statements
	#ifdef __DEBUG
		debug("AbstractGame::~AbstractGame() finished");
		debug("The game finished and cleaned up successfully. Press Enter to exit");
		getchar();
	#endif 
}

void AbstractGame::updatePhysics()
{
	customSystem->update();
}

int AbstractGame::runMainLoop()
{
	#ifdef __DEBUG
		debug("Entered Main Loop");
	#endif

	gfx->clearScreen();
	render();

	while (running)
	{
		gfx->setFrameStart();
		eventSystem->pollEvents();
		if (eventSystem->isPressed(Key::ESC) || eventSystem->isPressed(Key::QUIT))
			running = false;
		
		handleKeyEvents();
		handleMouseEvents();
		
		if (!paused)
		{
			update();
			updatePhysics();
			gameTime += 0.016; // 60 times a sec
		}
		
		gfx->clearScreen();
		render();
		renderUI();
		gfx->showScreen();
		gfx->adjustFPSDelay(16); // atm hardcoded to ~60 FPS
	}

	#ifdef __DEBUG
		debug("Exited Main Loop");
	#endif
	
	return 0;
}

void AbstractGame::handleMouseEvents()
{
	if (eventSystem->isPressed(Mouse::BTN_LEFT)) onLeftMouseButton();
	if (eventSystem->isPressed(Mouse::BTN_RIGHT)) onRightMouseButton();
}

void AbstractGame::onLeftMouseButton() {}
void AbstractGame::onRightMouseButton() {}
void AbstractGame::renderUI() {}