/*
 * File: game_tests.cpp
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Date: Dec 11 2023
 * Description: Test case functions for all parts of the game, using GTest
 */

#include <gtest/gtest.h>
#include "game.h"
#include "ghost.h"
#include "fruit.h"

/**
 * GhostTest class which creates a simulated environment to test the behaviour
 * of different functions within the game
 */
class GhostTest : public ::testing::Test {
protected:
    std::unique_ptr<Ghost> ghost;
    void SetUp() override {
        ghost = std::make_unique<Ghost>(sf::Vector2f(100.f, 100.f));
    }

    void simulateTime(float seconds) {
        // We create an initial time point
        sf::Clock clock;
        sf::Time elapsedTime = clock.restart();
        while (elapsedTime.asSeconds() < seconds) {
            // Update the ghost's movement based on the elapsed time
            ghost->updateMovement();

            // Add "game ticks"
            sf::Time frameTime = clock.restart();
            elapsedTime += frameTime;
        }
    }

};

/**
 * Test to see if ghost stays within boundaries
 */
TEST_F(GhostTest, RespectBoundary) {
    const float boundaryX = Game::getSceneWidth() - Ghost::getHitbox();
    const float boundaryY = Game::getSceneHeight() - Ghost::getHitbox();

    // Set ghost near the boundary
    ghost->setPosition(sf::Vector2f(boundaryX - 1, boundaryY - 1));

    // Simulate a frame update
    simulateTime(1.0f);
    ghost->updateMovement();

    // Check if ghost is still within boundaries
    sf::Vector2f newPos = ghost->getPosition();
    EXPECT_LE(newPos.x, boundaryX);
    EXPECT_LE(newPos.y, boundaryY);
}
