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

class World
{
public:
    World(const Vector2u &_size);
    ~World();
    const Vector2u &getSize() const;
    const Vector2f &getCellSize() const;
    void setCellSize(const Vector2f &_cellSize);
    void aff(RenderTarget &target) const;

private:
    void loadTextures();
    void create(const Vector2u &_size);
    void generate(const Vector2u &entry, const Vector2u &exit);

private:
    Vector2u size;
    CellType **tab;
    Vector2f cellSize;
    Texture textures[TypeCount];
};
