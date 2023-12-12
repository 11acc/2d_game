/*
 * File: game.cpp
 * Author: Alejandro Gutierrez Acosta [11acc], Katherine Duque, Rama Mallela
 * Contributing Author: Alessandra Gorla
 * Date: Dec 11 2023
 * Description: Game class to deal with initialization and controller of PacMan game
 */
#include "game.h"

const float Game::SCENE_WIDTH = 1920.0f;
const float Game::SCENE_HEIGHT = 1280.0f;
const float Game::PLAYER_START_X = 960.0f;
const float Game::PLAYER_START_Y = 640.0f;
const float Game::RADIUS = 40.0f;
const int Game::MAX_GHOSTS = 10;
const int Game::MAX_FRUITS = 3;
const float Game::COLLISION_THRESHOLD = 80;
const float Game::BASE_P_SPEED = 5.0f;
const float Game::BOOSTED_P_SPEED = 8.0f;

Game::Game() : score(0) {
    initWindow();
    initBackground();
    initScore();
    initPlayer();
    nextSpawnTime = randSpawnDelay(0);
}

/**
 * Window initializer.
 */
int Game::initWindow() {
    window.create(sf::VideoMode(SCENE_WIDTH, SCENE_HEIGHT), "PacMan Lite");
    window.setFramerateLimit(120);
    return 0;
}
/**
 * Background initializer.
 */
int Game::initBackground() {
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        return 1;
    }
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT));
    return 0;
}
/**
 * Score initializer
 * @return 0 if successfully initialized, 1 otherwise
 */
int Game::initScore() {
    if (!font.loadFromFile("resources/CyberpunkWaifus.ttf")) {
        return 1;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(42);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    return 0;
}
/**
 * PacMan initializer
 * @return 0 if successfully initialized, 1 otherwise
 */
int Game::initPlayer() {
    player.setRadius(RADIUS);
    player.setOrigin(RADIUS, RADIUS);
    player.setPosition(PLAYER_START_X, PLAYER_START_Y);
    if (!playerTexture.loadFromFile("resources/pacman.png")) {
        return 1;
    }
    player.setTexture(&playerTexture);
    return 0;
}


/**
 * Dealing with events on window.
 */
void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}
/**
 * Function to update the position of the player
 */
void Game::update() {
    float x = player.getPosition().x;
    float y = player.getPosition().y;
    float player_speed = pSpeed();
    player.setPosition(x, y);

    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y > RADIUS) {
        player.move(0, -player_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y < SCENE_HEIGHT - RADIUS) {
        player.move(0, player_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > RADIUS) {
        player.move(-player_speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x < SCENE_WIDTH - RADIUS) {
        player.move(player_speed, 0);
    }
}


/**
 * Random spawn delay for ghost creation
 */
float Game::randSpawnDelay(int type) {
    std::random_device rd;
    std::mt19937 eng(rd());
    if (type == 0) { // For Ghosts, shorter spawn delay
        std::uniform_real_distribution<> distr(0.0, 1.5); // Range is 0.0 to 2.0 seconds
        return distr(eng);
    } else { // For Fruits, longer spawn delay
        std::uniform_real_distribution<> distr(5.0, 9.0);
        return distr(eng);
    }
}
/**
 * Check if there are MAX_* (for a given object) in game, if there are less
 * make new ones
 */
void Game::checkObjNum() {
    auto playerPosition = player.getPosition();

    if (ghostSpawnClock.getElapsedTime().asSeconds() >= nextSpawnTime && ghosts.size() < MAX_GHOSTS) {
        ghosts.emplace_back(playerPosition);
        ghostSpawnClock.restart();
        nextSpawnTime = randSpawnDelay(0); // Set next spawn delay
    }
    // Check if it's time to spawn a new fruit
    if (fruitSpawnClock.getElapsedTime().asSeconds() >= nextFruitSpawnTime && fruits.size() < MAX_FRUITS) {
        fruits.emplace_back(playerPosition);
        fruitSpawnClock.restart();
        nextFruitSpawnTime = randSpawnDelay(1); // Using existing method
    }
}


/**
 * Check if player is colliding with ghost
 */
void Game::checkCollisions() {
    auto playerPos = player.getPosition();
    auto it = ghosts.begin();
    while (it != ghosts.end()) {
        auto ghostPos = it->getGhost().getPosition();
        float distance = std::sqrt(std::pow(playerPos.x - ghostPos.x, 2) +
                                   std::pow(playerPos.y - ghostPos.y, 2));

        // distance to consider a collision
        if (distance < COLLISION_THRESHOLD) {
            // Base score for destroying a ghost
            score += 5;

            // Bonus points based on ghost's life expectancy
            float ghostAge = it->ghostLifeExpectancy();
            // Subtract the ghost's age in seconds from 5 to a minimum of 1 ptn
            int bonusPoints = std::max(5 - static_cast<int>(ghostAge), 1);
            score += bonusPoints;

            // Remove ghost
            it = ghosts.erase(it);
        } else {
            ++it;
        }
    }
}
/**
 * Check if player is colliding with fruit
 */
void Game::checkFruitCollisions() {
    auto playerPos = player.getPosition();
    auto it = fruits.begin();
    while (it != fruits.end()) {
        auto fruitPos = it->getFruit().getPosition();
        float distance = std::sqrt(std::pow(playerPos.x - fruitPos.x, 2) + std::pow(playerPos.y - fruitPos.y, 2));

        if (distance < player.getRadius() + it->getFruit().getRadius()) {
            // Give the speed boost, which ends 3 seconds from now
            speedBoostEndTime = speedClock.getElapsedTime() + sf::seconds(3);

            it = fruits.erase(it);
        } else {
            ++it;
        }
    }
}
/**
 * Modify player speed and remove speed boost if needed
 * @return a float value representing player speed
 */
float Game::pSpeed() {
    if (speedClock.getElapsedTime() < speedBoostEndTime) {
        return BOOSTED_P_SPEED;
    }
    return BASE_P_SPEED;
}



/**
 * Render elements in the window
 */
void Game::render() {
    window.clear(sf::Color::White);
    window.draw(background);
    window.draw(player);
    for (auto& ghost : ghosts) {
        ghost.updateMovement();
        window.draw(ghost.getGhost());
    }
    for (const auto& fruit : fruits) {
        window.draw(fruit.getFruit());
    }
    scoreText.setString("Score: " + std::to_string(score) + " pts");
    window.draw(scoreText);

    window.display();
}
/**
 * Main function to deal with events, update the player and render the updated scene on the window.
 */
int Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        checkObjNum();
        checkCollisions();
        checkFruitCollisions();
        render();
    }
    return 0;
}