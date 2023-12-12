/*
 * File: fruit.cpp
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Date: Dec 11 2023
 * Description: Fruit class to deal with initialization and behaviour of fruits inside game
 */

#include "fruit.h"
#include "game.h"

const float Fruit::HITBOX = 30.0f;
const float Fruit::MIN_SPAWN_DISTANCE = 150.0f;
const float Fruit::MAX_SPAWN_DISTANCE_X = Game::getSceneWidth() - 20.0f;
const float Fruit::MAX_SPAWN_DISTANCE_Y = Game::getSceneHeight() - 20.0f;
// Defining this here too so that it doesn't despawn when generating new ghosts
sf::Texture Fruit::cherryTexture;
sf::Texture Fruit::melonTexture;
sf::Texture Fruit::berryTexture;

/**
 * Fruit constructor
 */
Fruit::Fruit(const sf::Vector2f& playerPosition) {
    loadTextures();
    assignRandomTexture();
    sf::Vector2f spawnPosition = randSpawn(playerPosition);
    initFruit(spawnPosition);
}
/**
 * Load textures if they haven't been loaded already
 */
int Fruit::loadTextures() {
    if (cherryTexture.getSize().x == 0) {
        cherryTexture.loadFromFile("resources/cherry.png");
        return 0;
    }
    if (melonTexture.getSize().x == 0) {
        melonTexture.loadFromFile("resources/melon.png");
        return 0;
    }
    if (berryTexture.getSize().x == 0) {
        berryTexture.loadFromFile("resources/berry.png");
        return 0;
    }
    return 1;
}
/**
 * Random texture for a fruit
 */
void Fruit::assignRandomTexture() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 2);

    int textureChoice = distr(eng);
    if (textureChoice == 0) {
        fruit.setTexture(&cherryTexture);
    } else if (textureChoice == 1) {
        fruit.setTexture(&melonTexture);
    } else if (textureChoice == 2) {
        fruit.setTexture(&berryTexture);
    }
}


/**
 * Fruit initializer
 */
int Fruit::initFruit(const sf::Vector2f& spawnPosition) {
    fruit.setRadius(HITBOX);
    fruit.setOrigin(HITBOX, HITBOX);
    loadTextures();
    assignRandomTexture();
    fruit.setPosition(spawnPosition);
    return 0;
}
/**
 * Generate a random spawn position for a fruit
 * @return the spawn position
 */
sf::Vector2f Fruit::randSpawn(const sf::Vector2f& playerPosition) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<> distrX(20.0f, MAX_SPAWN_DISTANCE_X);
    std::uniform_real_distribution<> distrY(20.0f, MAX_SPAWN_DISTANCE_Y);

    sf::Vector2f spawnPosition;
    float distance;
    do {
        spawnPosition = sf::Vector2f(distrX(eng), distrY(eng));
        distance = std::sqrt(std::pow(spawnPosition.x - playerPosition.x, 2) +
                             std::pow(spawnPosition.y - playerPosition.y, 2));
    } while (distance < Fruit::MIN_SPAWN_DISTANCE);

    return spawnPosition;
}