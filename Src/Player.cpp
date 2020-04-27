/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(const Vector2u &_position, const World &_world)
    : world(_world)
{
    floatPosition.x = _position.x * world.getCellSize().x + world.getOrigin().x;
    floatPosition.y = _position.y * world.getCellSize().y + world.getOrigin().y;
    if (!texture.loadFromFile("Resources/Texture/Player.png"))
        return; // TODO throw
}

Vector2u Player::getPosition() const
{
    return Vector2u(floatPosition + Vector2f(0.5, 0.5));
}

const Vector2f &Player::getFloatPosition() const
{
    return floatPosition;
}

void Player::update()
{
    //floatPosition = Vector2f(position.x * world.getCellSize().x, position.y * world.getCellSize().y); // TODO move (in update ?)


    if (Keyboard::isKeyPressed(Keyboard::Up))
        floatPosition.y -= 5;
    if (Keyboard::isKeyPressed(Keyboard::Down))
        floatPosition.y += 5;
    if (Keyboard::isKeyPressed(Keyboard::Left))
        floatPosition.x -= 5;
    if (Keyboard::isKeyPressed(Keyboard::Right))
        floatPosition.x += 5;
}

void Player::aff(RenderTarget &target) const
{
    RectangleShape sprite(world.getCellSize());

    sprite.setOrigin(world.getCellSize() / (float)2);
    sprite.setTexture(&texture);
    sprite.setPosition(floatPosition);
    target.draw(sprite);
}
