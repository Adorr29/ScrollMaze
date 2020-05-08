/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** Game.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "Player.hpp"

class Game
{
public:
    Game(const float &cellSize = 100, const Vector2u &wiewSize = Vector2u(3, 3)); // add seed ?
    void run();

private:
    void cameraUpdate();
    bool checkExit() const;

private:
    RenderWindow window;
    View view;
    WorldPtr world;
    PlayerPtr player;
};
