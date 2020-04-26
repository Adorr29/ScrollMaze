/*
** EPITECH PROJECT, 2020
** ScrollMaze
** File description:
** Main.cpp
*/

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

int main()
{
    srand(time(nullptr));

    const float cellSize = 100;
    const Vector2u windowSize(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(VideoMode(3 * cellSize, 3 * cellSize), "ScrollMaze", Style::Close);
    View view(Vector2f(0, 0), Vector2f(window.getSize()));
    World world(windowSize / (Uint32)cellSize);
    Player player(world.getSize() / (Uint32)2, world);

    world.setCellSize(Vector2f(cellSize, cellSize));
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);)
            if (event.type == Event::Closed)
                window.close();
        player.update();
        view.setCenter(player.getFloatPosition());
        window.setPosition(Vector2i(view.getCenter()) - Vector2i(view.getSize()) / 2);
        window.setView(view);
        window.clear();
        world.aff(window);
        player.aff(window);
        window.display();
    }
    return 0;
}
