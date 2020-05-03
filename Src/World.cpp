/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** World.cpp
*/

#include "World.hpp"

World::World(const Vector2u &_size, const Vector2f &_cellSize)
    : cellSize(_cellSize)
{
    const Vector2f windowSize(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);

    create(_size);
    origin.x = (windowSize.x - size.x * cellSize.x) / 2.0;
    origin.y = (windowSize.y - size.y * cellSize.y) / 2.0;
    generate(size / (Uint32)2);
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

const CellType &World::getCell(const Uint32 &x, const Uint32 &y) const
{
    return tab[x][y];
}

const CellType &World::getCell(const Vector2u &position) const
{
    return getCell(position.x, position.y);
}

const Vector2f &World::getOrigin() const
{
    return origin;
}

const Vector2f &World::getCellSize() const
{
    return cellSize;
}

void World::aff(RenderTarget &target) const
{
    RectangleShape sprite(cellSize);

    //sprite.setOrigin(sprite.getSize() / (float)2);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++) {
            sprite.setTexture(&textures[tab[i][j]]);
            sprite.setPosition(i * cellSize.x + origin.x, j * cellSize.y + origin.y);
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

void World::generate(const Vector2u &start)
{
    const vector<Vector2u> allDirectionList = {Vector2u(0, -1), Vector2u(0, 1), Vector2u(-1, 0), Vector2u(1, 0)};
    vector<Head> headList;

    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            tab[i][j] = Wall;
    tab[start.x][start.y] = Ground;

    for (const Vector2u &direction : allDirectionList)
        headList.push_back({start, direction});

    while (!headList.empty()) {
        const size_t headIndex = rand() % headList.size();
        Head head = headList[headIndex];

        headList.erase(headList.begin() + headIndex);
        while (true) {
            vector<Vector2u> directionList = allDirectionList;
            const Vector2u reverseDirection(-head.direction.x, -head.direction.y);
            size_t directionIndex;

            head.position += head.direction;
            remove(directionList.begin(), directionList.end(), reverseDirection);
            if (!canPlaceGround(head.position))
                break;
            tab[head.position.x][head.position.y] = Ground;

            directionIndex = rand() % directionList.size();
            head.direction = directionList[directionIndex];
            directionList.erase(directionList.begin() + directionIndex);
            for (const Vector2u &direction : directionList)
                headList.push_back({head.position, direction});
        }
    }
    generateExit();
}

void World::generateExit()
{
    vector<Vector2u> exitPossibilityList;
    Vector2u exitPosition;

    for (size_t i = 1; i < size.x - 2; i++) {
        if (tab[i][1] == Ground)
            exitPossibilityList.push_back(Vector2u(i, 0));
        if (tab[i][size.y - 2] == Ground)
            exitPossibilityList.push_back(Vector2u(i, size.y - 1));
    }
    for (size_t j = 1; j < size.y - 2; j++) {
        if (tab[1][j] == Ground)
            exitPossibilityList.push_back(Vector2u(0, j));
        if (tab[size.x - 2][j] == Ground)
            exitPossibilityList.push_back(Vector2u(size.x - 1, j));
    }
    exitPosition = exitPossibilityList[rand() % exitPossibilityList.size()];
    tab[exitPosition.x][exitPosition.y] = Ground;
}

bool World::canPlaceGround(const Vector2u &position) const
{
    const vector<Vector2u> allDirectionList = {Vector2u(0, -1), Vector2u(0, 1), Vector2u(-1, 0), Vector2u(1, 0)};
    bool oneGround = false;

    if (onEdge(position))
        return false;
    for (const Vector2u &direction : allDirectionList) {
        const Vector2u newPosition = position + direction;

        if (getCell(newPosition) == Ground) {
            if (oneGround)
                return false;
            else
                oneGround = true;
        }
    }
    return oneGround;
}

bool World::onEdge(const Vector2u &position) const
{
    return position.x == 0 || position.y == 0 || position.x >= size.x - 1 || position.y >= size.y - 1;
}
