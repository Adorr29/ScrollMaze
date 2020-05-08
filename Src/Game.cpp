/*
** EPITECH PROJECT, 2019
** ScrollMaze
** File description:
** Game.cpp
*/

#include "Game.hpp"

Game::Game(const float &cellSize, const Vector2u &wiewSize)
{
    const Vector2u windowSize(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);

    window.create(VideoMode(wiewSize.x * cellSize, wiewSize.y * cellSize), "ScrollMaze", Style::Close);
    window.setFramerateLimit(60);

    view.setSize(Vector2f(window.getSize()));

    srand(time(nullptr)); // add seed ?

    world = make_unique<World>(windowSize / (Uint32)cellSize, Vector2f(cellSize, cellSize));

    player = make_unique<Player>(world->getSize() / (Uint32)2, *world);
}

void Game::run()
{
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);)
            if (event.type == Event::Closed)
                window.close();
        player->update();
        if (checkExit())
            window.close();
        cameraUpdate();
        window.clear();
        world->aff(window);
        player->aff(window);
        window.display();
    }
}

void Game::cameraUpdate()
{
    Vector2f playerPosition;

    playerPosition.x = player->getPosition().x * world->getCellSize().x + world->getOrigin().x;
    playerPosition.y = player->getPosition().y * world->getCellSize().y + world->getOrigin().y;

    playerPosition.x = max(playerPosition.x, world->getOrigin().x + window.getSize().x / (float)2);
    playerPosition.y = max(playerPosition.y, world->getOrigin().y + window.getSize().y / (float)2);
    playerPosition.x = min(playerPosition.x, world->getSize().x * world->getCellSize().x + world->getOrigin().x - window.getSize().x / (float)2);
    playerPosition.y = min(playerPosition.y, world->getSize().y * world->getCellSize().y + world->getOrigin().y - window.getSize().y / (float)2);

    window.setPosition(Vector2i(playerPosition - Vector2f(window.getSize()) / (float)2));
    view.setCenter(Vector2f(window.getPosition()) + Vector2f(window.getSize()) / (float)2);
    window.setView(view);
}

bool Game::checkExit() const
{
    if (player->getPosition().x <= 0.1)
        return true;
    if (player->getPosition().y <= 0.1)
        return true;
    if (player->getPosition().x >= world->getSize().x - 1 + 0.9)
        return true;
    if (player->getPosition().y >= world->getSize().y - 1 + 0.9)
        return true;
    return false;
}
