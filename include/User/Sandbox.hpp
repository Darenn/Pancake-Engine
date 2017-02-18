//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_SANDBOX_HPP
#define PANCAKE_SANDBOX_HPP

#include <GameLogic.hpp>
#include <User/Ground.hpp>
#include <User/Box.hpp>
#include <User/Coin.hpp>
#include <User/Player.hpp>

namespace PancakeEngine {

    class Sandbox : public Scene {
    public:
        Sandbox() : Scene("Sandbox") {
            AssetsManager::createSpriteSheet("player1", "../resources/players/player1.png", 70, 100);
            AssetsManager::createSpriteSheet("player2", "../resources/players/player2.png", 70, 100);
            AssetsManager::createSpriteSheet("player3", "../resources/players/player3.png", 70, 100);
            AssetsManager::createSpriteSheet("player4", "../resources/players/player4.png", 70, 100);
            AssetsManager::createSpriteSheet("player5", "../resources/players/player5.png", 70, 100);
            AssetsManager::createSpriteSheet("tiles", "../resources/tiles/tiles.png", 70, 70);
            AssetsManager::createSpriteSheet("items", "../resources/items.png", 70, 70);

            addGameObject<Ground>().transform.setPosition(sf::Vector2f(0, 50));

            addGameObject<Box>();
            addGameObject<Box>();
            addGameObject<Box>();

            for (int i = 1; i <= 10; ++i) addGameObject<Coin>().transform.setPosition(sf::Vector2f(-75*i-50, -20));

            addGameObject<Player1>();
            addGameObject<Player2>();
            addGameObject<Player3>();
            addGameObject<Player4>();
            addGameObject<Player5>();
        }
    };
}

#endif //PANCAKE_SANDBOX_HPP