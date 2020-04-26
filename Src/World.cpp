/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** World.cpp
*/

#include "World.hpp"

World::World(const Vector2u &_size)
{
    Vector2u exit;

    create(_size);
    exit = Vector2u(rand() % (size.x - 2) + 1, rand() % (size.y - 2) + 1);
    if (rand() % 2)
        exit.x = rand() % 2 ? 0 : size.x - 1;
    else
        exit.y = rand() % 2 ? 0 : size.y - 1;
    generate(size / (Uint32)2, exit);
    loadTextures();
}

World::~World()
{
    for (Uint32 i = 0; i < size.x; i++)
        delete [] tab[i];
    delete [] tab;
}

const Vector2u &World::getSize() const
{
    return size;
}

const Vector2f &World::getCellSize() const
{
    return cellSize;
}

void World::setCellSize(const Vector2f &_cellSize)
{
    cellSize = _cellSize;
}

void World::aff(RenderTarget &target) const
{
    RectangleShape sprite(cellSize);

    sprite.setOrigin(cellSize / (float)2);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++) {
            sprite.setTexture(&textures[tab[i][j]]);
            sprite.setPosition(i * cellSize.x, j * cellSize.y);
            target.draw(sprite);
        }
}

void World::loadTextures()
{
    if (!textures[0].loadFromFile("Resources/Texture/Wall.png"))
        return; // TODO throw
    if (!textures[1].loadFromFile("Resources/Texture/Ground.png"))
        return; // TODO throw
}

void World::create(const Vector2u &_size)
{
    size = _size;
    tab = new CellType* [size.x];
    for (Uint32 i = 0; i < size.x; i++)
        tab[i] = new CellType [size.y];
}

void World::generate(const Vector2u &entry, const Vector2u &exit)
{
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            tab[i][j] = Wall;
    tab[entry.x][entry.y] = Ground;
    tab[exit.x][exit.y] = Ground;


    //vector<>
    // TODO
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            ;
}
