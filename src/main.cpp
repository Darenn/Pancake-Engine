#include <Engine.hpp>
#include <User/Sandbox.hpp>
#include <Parser/SceneFactory.hpp>
#include <User/Items/Rock.hpp>
#include <User/Ladder.hpp>
#include <User/Items/Transporter.hpp>
#include <User/Items/Trampoline.hpp>
#include <User/Items/Water.hpp>
#include <User/GameControllerSoloObject.hpp>
#include <User/CheckPointObject.hpp>
#include <User/Laser.hpp>
#include <User/DeathZone.hpp>
#include <User/enemy.hpp>
#include <User/LaserButton.hpp>

using namespace PancakeEngine;

int main() {
    AssetsManager::createSpriteSheet("player1", "../resources/players/player1.png", 70, 100);
    AssetsManager::createSpriteSheet("player2", "../resources/players/player2.png", 70, 100);
    AssetsManager::createSpriteSheet("player3", "../resources/players/player3.png", 70, 100);
    AssetsManager::createSpriteSheet("player4", "../resources/players/player4.png", 70, 100);
    AssetsManager::createSpriteSheet("player5", "../resources/players/player5.png", 70, 100);
    AssetsManager::createSpriteSheet("tiles", "../resources/tiles/tiles.png", 70, 70);
    AssetsManager::createSpriteSheet("miscs", "../resources/tiles/miscs.png", 70, 70);
    AssetsManager::createSpriteSheet("items", "../resources/items.png", 70, 70);
    AssetsManager::createSpriteSheet("slimeGreen", "../resources/enemies/slimeGreen.png", 57, 34);

    Engine * app = new Engine();
    const char* filename = "../resources/maps/arena.tmx";
    //app->sceneManager.loadScene(new Sandbox());
    SceneFactory sf;
    SceneFactory::addPrefab<Coin>("Coin");
    SceneFactory::addPrefab<Player1>("Player");
    SceneFactory::addPrefab<Player1>("Player1");
    SceneFactory::addPrefab<Player2>("Player2");
    SceneFactory::addPrefab<Player3>("Player3");
    SceneFactory::addPrefab<Player4>("Player4");
    SceneFactory::addPrefab<Player5>("Player5");
    SceneFactory::addPrefab<Box>("Box");
    SceneFactory::addPrefab<Rock>("Rock");
    SceneFactory::addPrefab<SmallRock>("SmallRock");
    SceneFactory::addPrefab<Ladder>("Ladder");
    SceneFactory::addPrefab<Water>("Water");
    SceneFactory::addPrefab<Laser>("Laser");
    SceneFactory::addPrefab<DeathZone>("DeathZone");
    SceneFactory::addPrefab<Transporter1>("Transporter1");
    SceneFactory::addPrefab<Transporter2>("Transporter2");
    SceneFactory::addPrefab<Transporter3>("Transporter3");
    SceneFactory::addPrefab<Trampoline>("Trampoline");
    SceneFactory::addPrefab<CheckPointObject1>("CheckPoint1");
    SceneFactory::addPrefab<CheckPointObject2>("CheckPoint2");
    SceneFactory::addPrefab<CheckPointObject3>("CheckPoint3");
    SceneFactory::addPrefab<CheckPointObject4>("CheckPoint4");
    SceneFactory::addPrefab<LaserButton>("LaserButton");
    SceneFactory::addPrefab<enemy>("slimeGreen");

    Scene* sc = sf.loadAllSceneObject(filename);
    // Add GUI
    AssetsManager::createSpriteSheet("heart", "../resources/heart.png", 53, 45);
    AssetsManager::createSpriteSheet("hud", "../resources/hud.png", 47, 47);
    unsigned height = sf::VideoMode::getDesktopMode().height / 2 + 50;
    unsigned width = sf::VideoMode::getDesktopMode().width / 2;
    sc->addGameObjectToGui<PlayerGUI1>().transform.setPosition(sf::Vector2f(width * 0 + 50, 50));
    sc->addGameObjectToGui<PlayerGUI2>().transform.setPosition(sf::Vector2f(width * 1 + 50, 50));
    sc->addGameObjectToGui<PlayerGUI3>().transform.setPosition(sf::Vector2f(width * 0 + 50, height));
    sc->addGameObjectToGui<PlayerGUI4>().transform.setPosition(sf::Vector2f(width * 1 + 50, height));
    sc->addGameObject<GameControllerSoloObject>(1);

    SceneManager::loadScene(sc);

    InputManager::createButton("player1_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Z}));
    InputManager::createButton("player1_fire", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
    InputManager::createButton("player1_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::D}));
    InputManager::createButton("player1_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Q}));
    InputManager::createButton("player1_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::S}));

    InputManager::createButton("player2_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Up}));
    InputManager::createButton("player2_fire", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::RControl}));
    InputManager::createButton("player2_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Right}));
    InputManager::createButton("player2_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Left}));
    InputManager::createButton("player2_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Down}));

    InputManager::createButton("player3_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_fire", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("player4_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_fire", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("player5_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_fire", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);

    app->run();
    delete app;

    return EXIT_SUCCESS;
}
