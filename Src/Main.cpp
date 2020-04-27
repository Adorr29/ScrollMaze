/*
** EPITECH PROJECT, 2020
** ScrollMaze
** File description:
** Main.cpp
*/

#include <iostream> // tmp
#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

void camera(RenderWindow &window, View &view, const World &world, const Player &player)
{
    Vector2f playerPosition =  player.getFloatPosition();

    playerPosition.x = max(playerPosition.x, world.getOrigin().x - world.getCellSize().x / (float)2 + window.getSize().x / (float)2);
    playerPosition.y = max(playerPosition.y, world.getOrigin().y - world.getCellSize().y / (float)2 + window.getSize().y / (float)2);
    playerPosition.x = min(playerPosition.x, world.getSize().x * world.getCellSize().x + world.getOrigin().x - world.getCellSize().x / (float)2 - window.getSize().x / (float)2);
    playerPosition.y = min(playerPosition.y, world.getSize().y * world.getCellSize().y + world.getOrigin().y - world.getCellSize().y / (float)2 - window.getSize().y / (float)2);

    window.setPosition(Vector2i(playerPosition - Vector2f(window.getSize()) / (float)2));
    view.setCenter(Vector2f(window.getPosition()) + Vector2f(window.getSize()) / (float)2);
    window.setView(view);
}

int main()
{
    srand(time(nullptr));

    const float cellSize = 100;
    const Vector2u windowSize(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(VideoMode(3 * cellSize, 3 * cellSize), "ScrollMaze", Style::Close);
    //RenderWindow window(VideoMode(1920, 1080), "ScrollMaze", Style::Fullscreen); // tmp
    View view(Vector2f(0, 0), Vector2f(window.getSize()));
    World world(windowSize / (Uint32)cellSize, Vector2f(cellSize, cellSize));
    Player player(world.getSize() / (Uint32)2, world);

    window.setFramerateLimit(60);
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);)
            if (event.type == Event::Closed)
                window.close();
        player.update();
        camera(window, view, world, player); //
        window.clear();
        world.aff(window);
        player.aff(window);
        window.display();
    }
    return 0;
}
