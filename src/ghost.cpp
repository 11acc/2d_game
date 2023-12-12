/*
 * File: game.cpp
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Date: Dec 11 2023
 * Description: Ghost class to deal with initialization and behaviour of ghost inside game
 */

#include "ghost.h"
#include "game.h"

const float Ghost::HITBOX = 40.0f;
const float Ghost::MIN_SPAWN_DISTANCE = 150.0f;
const float Ghost::MAX_SPAWN_DISTANCE_X = Game::getSceneWidth() - 20.0f;
const float Ghost::MAX_SPAWN_DISTANCE_Y = Game::getSceneHeight() - 20.0f;
// Defining this here too so that it doesn't despawn when generating new ghosts
sf::Texture Ghost::blueTexture;
sf::Texture Ghost::orangeTexture;
sf::Texture Ghost::pinkTexture;
sf::Texture Ghost::redTexture;

/**
 * Ghost constructor
 */
Ghost::Ghost(const sf::Vector2f& playerPosition) {
    loadTextures();
    assignRandomTexture();
    sf::Vector2f spawnPosition = randSpawn(playerPosition);
    decideNextMovement();
    initGhost(spawnPosition);
}
/**
 * Load textures if they haven't been loaded already
 */
int Ghost::loadTextures() {
    if (blueTexture.getSize().x == 0) {
        blueTexture.loadFromFile("resources/blue.png");
        return 0;
    }
    if (orangeTexture.getSize().x == 0) {
        orangeTexture.loadFromFile("resources/orange.png");
        return 0;
    }
    if (pinkTexture.getSize().x == 0) {
        pinkTexture.loadFromFile("resources/pink.png");
        return 0;
    }
    if (redTexture.getSize().x == 0) {
        redTexture.loadFromFile("resources/red.png");
        return 0;
    }
    return 1;
}
/**
 * Random texture for a ghost
 */
void Ghost::assignRandomTexture() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 3);

    int textureChoice = distr(eng);
    if (textureChoice == 0) {
        ghost.setTexture(&blueTexture);
    } else if (textureChoice == 1) {
        ghost.setTexture(&orangeTexture);
    } else if (textureChoice == 2) {
        ghost.setTexture(&pinkTexture);
    } else if (textureChoice == 3) {
        ghost.setTexture(&redTexture);
    }
}


/**
 * Ghost initializer
 */
int Ghost::initGhost(const sf::Vector2f& spawnPosition) {
    ghost.setRadius(HITBOX);
    ghost.setOrigin(HITBOX, HITBOX);
    loadTextures();
    assignRandomTexture();
    ghost.setPosition(spawnPosition);
    return 0;
}

/**
 * Generate a random spawn position for a ghost
 * @return the spawn position
 */
sf::Vector2f Ghost::randSpawn(const sf::Vector2f& playerPosition) {
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
    } while (distance < Ghost::MIN_SPAWN_DISTANCE);

    return spawnPosition;
}


/**
 * Randomly generate movements for ghosts
 */
void Ghost::decideNextMovement() {
    std::random_device rd;
    std::mt19937 eng(rd());
    // Random option of 4 directions
    std::uniform_real_distribution<> distr(0, 4);
    // 0.5s - 1.5s movement interval random
    std::uniform_real_distribution<> timeDistr(0.5, 0.9);

    int dir = static_cast<int>(distr(eng));
    if (dir == 0) { // Up
        direction = sf::Vector2f(0, -1);
    } else if (dir == 1) { // Down
        direction = sf::Vector2f(0, 1);
    } else if (dir == 2) { // Left
        direction = sf::Vector2f(-1, 0);
    } else if (dir == 3) { // Right
        direction = sf::Vector2f(1, 0);
    }
    movementInterval = timeDistr(eng);
    movementClock.restart();
}
/**
 * Update the movement like the player but for ghosts
 */
void Ghost::updateMovement() {
    // Decide next movement if the interval has passed
    if (movementClock.getElapsedTime().asSeconds() >= movementInterval) {
        decideNextMovement();
    }

    // Move ghost in the decided direction
    sf::Vector2f newPos = ghost.getPosition() + direction;

    // Apply boundary restrictions
    newPos.x = std::max(newPos.x, HITBOX);
    newPos.x = std::min(newPos.x, Game::getSceneWidth() - HITBOX);
    newPos.y = std::max(newPos.y, HITBOX);
    newPos.y = std::min(newPos.y, Game::getSceneHeight() - HITBOX);

    ghost.setPosition(newPos);
}

/**
 * Set a custom position for a ghost
 * @test_function
 */
void Ghost::setPosition(const sf::Vector2f& position) {
    ghost.setPosition(position);
}
/**
 * Get the position of a ghost
 * @test_function
 */
sf::Vector2f Ghost::getPosition() {
    return ghost.getPosition();
}