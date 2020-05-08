/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** World.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum CellType
{
    Wall,
    Ground,
    TypeCount
};

struct Head // only for World::generate
{
    Vector2u position;
    Vector2u direction;
};

class World
{
public:
    World(const Vector2u &_size, const Vector2f &_cellSize);
    ~World();
    const Vector2u &getSize() const;
    const CellType &getCell(const Uint32 &x, const Uint32 &y) const;
    const CellType &getCell(const Vector2u &position) const;
    const Vector2f &getOrigin() const;
    const Vector2f &getCellSize() const;
    void aff(RenderTarget &target) const;

private:
    void loadTextures();
    void create(const Vector2u &_size);
    void generate(const Vector2u &start);
    void generateExit();
    bool canPlaceGround(const Vector2u &position) const;
    bool onEdge(const Vector2u &position) const;

private:
    Vector2u size;
    CellType **tab;
    Vector2f origin;
    Vector2f cellSize;
    Texture textures[TypeCount];
};

typedef unique_ptr<World> WorldPtr;
