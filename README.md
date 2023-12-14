# 2D-game

![Static Badge](https://img.shields.io/badge/version-1.0-blue)

Some kind of pacman... type of thing... lol

PacMan inspired game where the player eats ghosts instead of fleeing from them, the occasional fruits also pop up and give a speed boost. Each ghost when killed (by collision with the player) grants a flat 5 points, with an additional 1-5 points depending on how soon they're killed once they spawn.

## Dependencies

We use the [SFML library](https://www.sfml-dev.org/index.php) for visual gameplay. [GTest](https://github.com/google/googletest) in order to test case a range of functions for entity behaviour and spawning.

## Compile and run
Once dependencies are set, you can compile the project with `cmake` in CLion and run it directly. Or, with the command line:

```bash
# Clone this repository
$ git clone https://github.com/11acc/2d_game.git

# To run game (Windows)
$ g++ ./src/main.cpp ./src/game.cpp ./src/ghost.cpp ./src/fruit.cpp -o main -I./include -IC:/SFML-2.6.1/include -LC:/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
$ ./main

# To run GTest test cases
$ g++ src/game_tests.cpp src/game.cpp src/ghost.cpp src/fruit.cpp -o game_tests -I/path/to/gtest/include -L/path/to/gtest/lib -lgtest -lgtest_main -pthread -IC:/SFML-2.6.1/include -LC:/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
$ ./game_tests

# To run coverage testing (TBD)
$ g++
$ .
```

## Testing and coverage

Specifics on test cases in Wiki.

TBD

## Contributing/License

Fork it, modify it, push it, eat it, summon a duck god with it. Whatever resonable day-to-day activity you prefer ( •ᴗ•)b
