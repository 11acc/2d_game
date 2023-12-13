/*
 * File: game_tests.cpp
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Date: Dec 11 2023
 * Description: Test case functions for game functions, using GTest
 */

#include <gtest/gtest.h>
#include "game.h"
#include "ghost.h"
#include "fruit.h"

/**
 * GameTest class which creates a simulated environment to test the behaviour
 * of different functions within the game
 * We use TEST_F because we want a test environment shared among multiple test cases
 * Test environment: Player, Ghost and Fruit entities created
 */
class GameTest : public ::testing::Test {
protected:
    Game game;
    std::unique_ptr<Ghost> ghost;
    std::unique_ptr<Fruit> fruit;

protected:
    void SetUp() override {
        fruit = std::make_unique<Fruit>(sf::Vector2f(100.f, 100.f));
    }

    void simulateTime(sf::Clock clock, float seconds) {
        // We create an initial time point
        sf::Time elapsedTime = clock.restart();
        while (elapsedTime.asSeconds() < seconds) {
            // Update the ghost's movement based on the elapsed time
            game.checkObjNum();

            // Add "game ticks"
            sf::Time frameTime = clock.restart();
            elapsedTime += frameTime;
        }
    }
};
/**
 * Entity spawn tests
 */
// Test to validate fruit spawning
TEST_F(GameTest, EntitiesSpawnWithinLimits) {
    // Simulate time to trigger spawning
    simulateTime(game.getGhostSpawnClock(), game.getNextSpawnTime() + 0.1f);

    // Check if a ghost is spawned
    EXPECT_LE(game.getGhosts().size(), Game::getMaxGhosts());

    // Repeat for fruits
    simulateTime(game.getFruitSpawnClock(), game.getNextFruitSpawnTime() + 0.1f);

    EXPECT_LE(game.getFruits().size(), Game::getMaxFruits());
}


/**
 * GhostTest simulated environment creates Ghost entity with a time
 * simulation of a provided time input
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
 * 2 Ghost movement tests
 */
// Ghost Movement (1): Test to see if ghost stays within boundaries
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

// Ghost Movement (2): Test to ensure ghost changes direction
TEST_F(GhostTest, DirectionChange) {
    sf::Vector2f initialPos = ghost->getPosition();
    // Simulate 10 random movements
    for (int i = 0; i < 10; ++i) {
        simulateTime(0.1f);
        ghost->updateMovement();
    }
    sf::Vector2f finalPos = ghost->getPosition();

    // Verifies that val1 != val2
    EXPECT_NE(initialPos, finalPos);
}