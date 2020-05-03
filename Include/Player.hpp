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
    const Vector2f &getPosition() const;
    const Vector2u &getSize() const;
    void update();
    void aff(RenderTarget &target) const;

private:
    const World &world;
    Vector2f position;
    float speed;
    Texture texture;
};
