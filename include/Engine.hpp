//
// Created by Darenn on 24/01/2017.
//

#ifndef PANCAKE_ENGINE_HPP
#define PANCAKE_ENGINE_HPP


#include "SceneManager.hpp"
#include "Graphics/Window.hpp"
#include "PhysicsEngine.hpp"
#include "Time.hpp"

namespace PancakeEngine {

    class Engine {

    public:
        const double SECONDS_PER_UPDATE = 1.0/100.0;

        Engine();

        void run();

        SceneManager sceneManager;
        Window window;
        PhysicsEngine physicsEngine;
        Time time;

    private:

        /*
         * Update the engine (physics and logic) with a constant time.
         */
        void update();
    };

}

#endif //PANCAKE_ENGINE_HPP
