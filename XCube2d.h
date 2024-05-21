//
//  XCube2d.h
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

// ================================
// Entry point for the xcube engine
// Initialises game engine instance and handles startup of subsystems
// Any new, custom subsystems need to be integrated into it
// ================================

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
// including provided subsystems
#include "GraphicsEngine.h"
#include "EventEngine.h"
#include "AudioEngine.h"
// including custom physics subsystem
#include "MyPhysicsSubsystem.h"

const int _ENGINE_VERSION_MAJOR = 0;
const int _ENGINE_VERSION_MINOR = 1;

class XCube2Engine {
private:
    static std::shared_ptr<XCube2Engine> instance;

    // declaring shared pointers of provided subsystems
    std::shared_ptr<GraphicsEngine> gfxInstance;
    std::shared_ptr<EventEngine> eventInstance;
    std::shared_ptr<AudioEngine> audioInstance;
    // declaring shared pointer of custom subsystem
    std::shared_ptr<MyPhysicsSubsystem> customInstance;

    //   std::shared_ptr<MyEngineSystem> myEngineSystemInstance;

    XCube2Engine();
public:
    /**
    * @return the instance of game engine
    * @exception throws EngineException if init of any submodules failed
    */
    static std::shared_ptr<XCube2Engine> getInstance();
    ~XCube2Engine();

    // getting shared instances of provided subsystems
    std::shared_ptr<GraphicsEngine> getGraphicsEngine() { return gfxInstance; }
    std::shared_ptr<EventEngine> getEventEngine() { return eventInstance; }
    std::shared_ptr<AudioEngine> getAudioEngine() { return audioInstance; }
    // getting shared instance of custom subsystem
    std::shared_ptr<MyPhysicsSubsystem> getMyPhysicsSubsystem() { return customInstance; }

    /**
    * Quits the engine, closes all the subsystems
    *
    * All subsequent calls to any of subsystems will have undefined behaviour
    */
    static void quit();


};

typedef XCube2Engine XEngine;
