/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** Player.hpp
*/

#pragma once

#include "World.hpp"

class Player
{
public:
    Player(const Vector2u &_position, const World &_world);
    const Vector2u &getPosition() const;
    const Vector2f &getFloatPosition() const;
    const Vector2u &getSize() const;
    void update();
    void aff(RenderTarget &target) const;

private:
    const World &world;
    Vector2u position;
    Vector2f floatPosition;
    Texture texture;
};
