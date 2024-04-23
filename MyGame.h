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
    SDL_Rect box;

    Vector2i velocity;

    std::vector<std::shared_ptr<GameKey>> gameKeys;

    // gameplay
    int numKeys;
    void handleKeyEvents();
    void update();
    void render();
    void renderUI();
public:
    MyGame();
    ~MyGame();
};

