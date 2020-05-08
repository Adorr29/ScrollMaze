/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** Player.cpp
*/

#include <cmath>
#include "Player.hpp"

Player::Player(const Vector2u &_position, const World &_world)
    : world(_world)
{
    position = Vector2f(_position) + Vector2f(0.5, 0.5);
    speed = 0.03;
    if (!texture.loadFromFile("Resources/Texture/Player.png"))
        return; // TODO throw
}

const Vector2f &Player::getPosition() const
{
    return position;
}

void Player::update()
{
    Vector2f direction;
    float length;

    if (Keyboard::isKeyPressed(Keyboard::Up))
        direction.y--;
    if (Keyboard::isKeyPressed(Keyboard::Down))
        direction.y++;
    if (Keyboard::isKeyPressed(Keyboard::Left))
        direction.x--;
    if (Keyboard::isKeyPressed(Keyboard::Right))
        direction.x++;

    length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

    Vector2f target = position + direction;

    Vector2f newPosition = position + direction * speed / length;
    Vector2f nPosUR = newPosition + Vector2f(0.495, -0.495);
    Vector2f nPosDR = newPosition + Vector2f(0.495, 0.495);
    Vector2f nPosUL = newPosition + Vector2f(-0.495, -0.495);
    Vector2f nPosDL = newPosition + Vector2f(-0.495, 0.495);

    if (direction.y > 0) {
        bool a = world.getCell(Vector2u(nPosDL)) == Wall;
        bool b = world.getCell(Vector2u(nPosDR)) == Wall;

        if (a || b) {
            target = Vector2f(position.x, (int)position.y + 0.5);
            if (!a)
                target = Vector2f((int)nPosDL.x + 0.5, target.y);
            else if (!b)
                target = Vector2f((int)nPosDR.x + 0.5, target.y);
        }
    }
    else if (direction.y < 0) {
        bool a = world.getCell(Vector2u(nPosUL)) == Wall;
        bool b = world.getCell(Vector2u(nPosUR)) == Wall;

        if (a || b) {
            target = Vector2f(position.x, (int)position.y + 0.5);
            if (!a)
                target = Vector2f((int)nPosUL.x + 0.5, target.y);
            else if (!b)
                target = Vector2f((int)nPosUR.x + 0.5, target.y);
        }
    }

    if (direction.x > 0) {
        bool a = world.getCell(Vector2u(nPosUR)) == Wall;
        bool b = world.getCell(Vector2u(nPosDR)) == Wall;

        if (a || b) {
            target = Vector2f((int)position.x + 0.5, position.y);
            if (!a)
                target = Vector2f(target.x, (int)nPosUR.y + 0.5);
            else if (!b)
                target = Vector2f(target.x, (int)nPosDR.y + 0.5);
        }
    }
    else if (direction.x < 0) {
        bool a = world.getCell(Vector2u(nPosUL)) == Wall;
        bool b = world.getCell(Vector2u(nPosDL)) == Wall;

        if (a || b) {
            target = Vector2f((int)position.x + 0.5, position.y);
            if (!a)
                target = Vector2f(target.x, (int)nPosUL.y + 0.5);
            else if (!b)
                target = Vector2f(target.x, (int)nPosDL.y + 0.5);
        }
    }

    moveTo(target);
}

void Player::aff(RenderTarget &target) const
{
    RectangleShape sprite(world.getCellSize());
    Vector2f spritePosition;

    spritePosition.x = position.x * world.getCellSize().x + world.getOrigin().x;
    spritePosition.y = position.y * world.getCellSize().y + world.getOrigin().y;
    sprite.setOrigin(sprite.getSize() / (float)2);
    sprite.setTexture(&texture);
    sprite.setPosition(spritePosition);
    target.draw(sprite);
}

void Player::moveTo(const Vector2f &target)
{
    Vector2f direction = target - position;
    float sqrLength = pow(direction.x, 2) + pow(direction.y, 2);

    if (pow(speed, 2) >= sqrLength)
        position = target;
    else
        position += direction * speed / sqrt(sqrLength);
}
