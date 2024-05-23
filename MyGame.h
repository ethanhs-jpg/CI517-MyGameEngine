#pragma once
//
//  MyGame.h
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

// =========================
// Represents the demo class
// Showcases the functionality of the custom game subsystem
// Inherits from AbstractGame to integrate with xcube
// =========================

#include <stdio.h>

#include "AbstractGame.h"

struct GameKey {
    Point2 pos;
    bool isAlive;
};


class MyGame : public AbstractGame
{
    private:
        Rect box, box2; // (1)xcoord, (2)ycoord, (3)width, (4)height
        PhysicsObject phy, phyobj2;

        // loading audio in for use in the game demo
        Mix_Music* backgroundMusic = NULL;
        Mix_Chunk* collectCoin = NULL;

        SDL_Texture* sprite1 = NULL;

        std::vector<std::shared_ptr<GameKey>> gameKeys;

        // gameplay
        int score, numKeys, lives;
        bool gameWon;

        void handleKeyEvents();
        void update();
        void render();
        void renderUI();

        // custom speed, acceleration, forces, and drag coefficient values
        int speed = 5;
        float acceleration = 2.0f;
        float xForce = 0.0f;
        float yForce = 0.0f;
        float dragCoefficient = 0.05f;
        // boolean checks for key presses for each axis
        bool xKeyPressed;
        bool yKeyPressed;

    public:
        MyGame();
        ~MyGame();
};

