/*
 * File: ghost.h
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Date: Dec 11 2023
 * Description: Ghost class header.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

class Ghost {
public:
    explicit Ghost(const sf::Vector2f& playerPosition);
    const sf::CircleShape& getGhost() const { return ghost; }

    void updateMovement();
    // returns how long the ghost has lived
    float ghostLifeExpectancy() const {
        return spawnClock.getElapsedTime().asSeconds();
    }

private:
    static const float HITBOX;
    static const float MIN_SPAWN_DISTANCE;
    static const float MAX_SPAWN_DISTANCE_X;
    static const float MAX_SPAWN_DISTANCE_Y;

    static sf::Texture blueTexture;
    static sf::Texture orangeTexture;
    static sf::Texture pinkTexture;
    static sf::Texture redTexture;
    sf::CircleShape ghost;
    sf::Clock spawnClock;
    sf::Vector2f direction;
    sf::Clock movementClock;
    float movementInterval;

    int loadTextures();
    void assignRandomTexture();
    int initGhost(const sf::Vector2f& spawnPosition);
    static sf::Vector2f randSpawn(const sf::Vector2f& playerPosition);
    void decideNextMovement();
};