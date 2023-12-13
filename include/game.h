/*
 * File: game.h
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Contributing Author: Alessandra Gorla
 * Date: Dec 11 2023
 * Description: Game class header.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include "ghost.h"
#include "fruit.h"

class Game {
    friend class GameTest;

public:
    Game();
    int run();
    static float getSceneWidth() { return SCENE_WIDTH; }
    static float getSceneHeight() { return SCENE_HEIGHT; }
    static float getMaxGhosts() { return MAX_GHOSTS; }
    static float getMaxFruits() { return MAX_FRUITS; }

    std::vector<Ghost> getGhosts() { return ghosts; }
    sf::Clock getGhostSpawnClock() { return ghostSpawnClock; }
    float getNextSpawnTime() { return nextSpawnTime; }

    std::vector<Fruit> getFruits() { return fruits; }
    sf::Clock getFruitSpawnClock() { return fruitSpawnClock; }
    float getNextFruitSpawnTime() { return nextFruitSpawnTime; }


private:
    static const float SCENE_WIDTH;
    static const float SCENE_HEIGHT;
    static const float PLAYER_START_X;
    static const float PLAYER_START_Y;
    static const float RADIUS;
    static const int MAX_GHOSTS;
    static const int MAX_FRUITS;
    static const float COLLISION_THRESHOLD;
    static const float BASE_P_SPEED;
    static const float BOOSTED_P_SPEED;

    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture backgroundTexture;

    sf::Clock gameClock;
    sf::Time totalTime;
    sf::Text countdownText;
    sf::Text finalScoreText;

    sf::Font font;
    sf::Text scoreText;
    sf::Texture playerTexture;
    sf::CircleShape player;
    sf::Time speedBoostEndTime;
    sf::Clock speedClock;
    sf::Text speedBoostText;
    std::vector<Ghost> ghosts;
    sf::Clock ghostSpawnClock;
    std::vector<Fruit> fruits;
    sf::Clock fruitSpawnClock;

    int initWindow();
    int initBackground();
    int initScore();
    int initPlayer();
    void processInput();
    int displaySpeedText();
    int score;
    float nextSpawnTime;
    float nextFruitSpawnTime{};
    bool gameEnded;

    void update();
    int clockRender();
    int finalScoreRender();
    float randSpawnDelay(int type);
    void checkObjNum();
    void checkCollisions();
    void checkFruitCollisions();
    float pSpeed();

    void render();
};