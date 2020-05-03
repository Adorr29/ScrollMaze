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

#include <iostream> // tmp
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
    if (length <= 0)
        return;
    direction.x *= speed / length;
    direction.y *= speed / length;

    Vector2f newPosition = position + direction;
    Vector2f nPosUR = newPosition + Vector2f(0.45, -0.45);
    Vector2f nPosDR = newPosition + Vector2f(0.45, 0.45);
    Vector2f nPosUL = newPosition + Vector2f(-0.45, -0.45);
    Vector2f nPosDL = newPosition + Vector2f(-0.45, 0.45);

    if (direction.y > 0) {
        bool a = world.getCell(Vector2u(nPosDL)) == Wall;
        bool b = world.getCell(Vector2u(nPosDR)) == Wall;

        if (a || b) {
            position.y = (int)position.y + 0.5;
            direction.y = 0;
            /*if (!a)
                direction.x = -1;
            else if (!b)
            direction.x = 1;*/
        }
    }
    else if (direction.y < 0) {
        bool a = world.getCell(Vector2u(nPosUL)) == Wall;
        bool b = world.getCell(Vector2u(nPosUR)) == Wall;

        if (a || b) {
            position.y = (int)position.y + 0.5;
            direction.y = 0;
            /*if (!a)
                direction.x = -1;
            else if (!b)
            direction.x = 1;*/
        }
    }
    if (direction.x > 0) {
        bool a = world.getCell(Vector2u(nPosUR)) == Wall;
        bool b = world.getCell(Vector2u(nPosDR)) == Wall;

        if (a || b) {
            position.x = (int)position.x + 0.5;
            direction.x = 0;
            /*if (direction.y == 0) {
                if (!a)
                    direction.y = -1;
                else if (!b)
                    direction.y = 1;
                    }*/
        }
    }
    else if (direction.x < 0) {
        bool a = world.getCell(Vector2u(nPosUL)) == Wall;
        bool b = world.getCell(Vector2u(nPosDL)) == Wall;

        if (a || b) {
            position.x = (int)position.x + 0.5;
            direction.x = 0;
            /*if (direction.y == 0) {
                if (!a)
                    direction.y = -1;
                else if (!b)
                    direction.y = 1;
                    }*/
        }
    }

    /*if (world.getCell(Vector2u(newPosition)) == Wall)
      return;*/


    length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (length <= 0)
        return;
    direction.x *= speed / length;
    direction.y *= speed / length;

    position += direction;

    /*if (direction.x == 0 && direction.y == 0)
        return;

    Vector2f newFloatPosition = floatPosition + direction;
    Vector2f nFPosUR = newFloatPosition + Vector2f(world.getCellSize().x, -world.getCellSize().y) / (float)2;
    Vector2f nFPosDR = newFloatPosition + Vector2f(world.getCellSize().x, world.getCellSize().y) / (float)2;
    Vector2f nFPosUL = newFloatPosition + Vector2f(-world.getCellSize().x, -world.getCellSize().y) / (float)2;
    Vector2f nFPosDL = newFloatPosition + Vector2f(-world.getCellSize().x, world.getCellSize().y) / (float)2;

    if (direction.y > 0) {
        bool a = world.getCell(convert(nFPosDL, world)) == Wall;
        bool b = world.getCell(convert(nFPosDR, world)) == Wall;

        if (a || b) {
            direction.y = 0;
            if (direction.x == 0) {
                if (!a)
                    direction.x = -1;
                else if (!b)
                    direction.x = 1;
            }
        }
    }
    else if (direction.y < 0) {
        bool a = world.getCell(convert(nFPosUL, world)) == Wall;
        bool b = world.getCell(convert(nFPosUR, world)) == Wall;

        if (a || b) {
            direction.y = 0;
            if (direction.x == 0) {
                if (!a)
                    direction.x = -1;
                else if (!b)
                    direction.x = 1;
            }
        }
    }
    if (direction.x > 0) {
        bool a = world.getCell(convert(nFPosUR, world)) == Wall;
        bool b = world.getCell(convert(nFPosDR, world)) == Wall;

        if (a || b) {
            direction.x = 0;
            if (direction.y == 0) {
                if (!a)
                    direction.y = -1;
                else if (!b)
                    direction.y = 1;
            }
        }
    }
    else if (direction.x < 0) {
        bool a = world.getCell(convert(nFPosUL, world)) == Wall;
        bool b = world.getCell(convert(nFPosDL, world)) == Wall;

        if (a || b) {
            direction.x = 0;
            if (direction.y == 0) {
                if (!a)
                    direction.y = -1;
                else if (!b)
                    direction.y = 1;
            }
        }
    }

    length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (length <= 0)
        return;
    direction.x *= speed / length;
    direction.y *= speed / length;
    floatPosition += direction;*/


    //cerr << "position : " << getPosition().x << " " << getPosition().y << endl; // tmp
    //cerr << "newPosition : " << newPosition.x << " " << newPosition.y << endl; // tmp

    /*if (world.getCell(newPosition) == Wall)
      return;*/

    /*floatPosition.x += direction.x * speed;
    floatPosition.y += direction.y * speed;

    Vector2f newFloatPos = Vector2f(newPosition.x * world.getCellSize().x, newPosition.y * world.getCellSize().y) + world.getOrigin();
    Vector2f posUR = newFloatPos + Vector2f(world.getCellSize().x, -world.getCellSize().y) / (float)2;
    Vector2f posDR = newFloatPos + Vector2f(world.getCellSize().x, world.getCellSize().y) / (float)2;
    Vector2f posUL = newFloatPos + Vector2f(-world.getCellSize().x, -world.getCellSize().y) / (float)2;
    Vector2f posDL = newFloatPos + Vector2f(-world.getCellSize().x, world.getCellSize().y) / (float)2;*/

    /*if (world.getCell(newPosition) == Wall) {
        if (direction.y > 0) {
            if (newPosition.y * world.getCellSize().y + world.getOrigin().y - floatPosition.y < world.getCellSize().y)
                floatPosition.y = getPosition().y * world.getCellSize().y + world.getOrigin().y;
        }
        else if (direction.y < 0) {
            if (floatPosition.y - (newPosition.y * world.getCellSize().y + world.getOrigin().y) < world.getCellSize().y)
                floatPosition.y = getPosition().y * world.getCellSize().y + world.getOrigin().y;
        }

        if (direction.x > 0) {
            if (newPosition.x * world.getCellSize().x + world.getOrigin().x - floatPosition.x < world.getCellSize().x)
                floatPosition.x = getPosition().x * world.getCellSize().x + world.getOrigin().x;
        }
        else if (direction.x < 0) {
            if (floatPosition.x - (newPosition.x * world.getCellSize().x + world.getOrigin().x) < world.getCellSize().x)
                floatPosition.x = getPosition().x * world.getCellSize().x + world.getOrigin().x;
        }
        }*/
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
