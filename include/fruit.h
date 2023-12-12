/*
 * File: ghost.h
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Date: Dec 11 2023
 * Description: Fruit class header.
 */

#pragma once
#include <SFML/Graphics.hpp>

class Fruit {
public:
    explicit Fruit(const sf::Vector2f& playerPosition);
    const sf::CircleShape& getFruit() const { return fruit; }

private:
    static const float HITBOX;
    static const float MIN_SPAWN_DISTANCE;
    static const float MAX_SPAWN_DISTANCE_X;
    static const float MAX_SPAWN_DISTANCE_Y;

    static sf::Texture cherryTexture;
    static sf::Texture melonTexture;
    static sf::Texture berryTexture;
    sf::CircleShape fruit;

    int loadTextures();
    void assignRandomTexture();
    int initFruit(const sf::Vector2f& spawnPosition);
    static sf::Vector2f randSpawn(const sf::Vector2f& playerPosition);
};