//
//  AbstractGame.h
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master

// =========================================
// Utilises xcube engine to execute the game
// Offers functionalities like game loops, game controls (play/pause), and state management
// Game demo can be developed as a subclass of this abstract class to inherit its functionalities
// =========================================

#include <stdio.h>
#include "XCube2d.h"


class AbstractGame {
private:
    /* Main loop control */
    // adding handlers
    void handleMouseEvents();

    void updatePhysics(); // calling function for updating physics

    protected:
        AbstractGame();
        virtual ~AbstractGame();

        // get pointers
        std::shared_ptr<GraphicsEngine> gfx;
        std::shared_ptr<EventEngine> eventSystem;
        std::shared_ptr<AudioEngine> audioSystem;
        // getting custom subsystem pointer
        std::shared_ptr<MyPhysicsSubsystem> customSystem;

        /* Main loop control */
        bool running;
        bool paused;
        double gameTime;

        // virtual functions are base class member functions that can be redefined in a derived class to achieve polymorphism
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void renderUI() = 0; // virtual function for rendering UI text

        // define input handlers
        virtual void handleKeyEvents() = 0;
        virtual void onLeftMouseButton();
        virtual void onRightMouseButton();

        // define game controls
        void pause() { paused = true; }
        void resume() { paused = false; }

    public:
        int runMainLoop();
};

