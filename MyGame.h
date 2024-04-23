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
        SDL_Rect box, box2; // (1)xcoord, (2)ycoord, (3)width, (4)height
        PhysicsObject phy, phyobj2;

        //Vector2i velocity;

        std::vector<std::shared_ptr<GameKey>> gameKeys;

        // gameplay
        int score, numKeys, lives;
        bool gameWon;

        void handleKeyEvents();
        void update();
        void render();
        void renderUI();

    public:
        MyGame();
        ~MyGame();
};

