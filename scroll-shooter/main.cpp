#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "AllyShip.h"
#include "config.h"

map<string, int> KeysDown{
    pair<string, int>{"W", 0}, pair<string, int>{"A", 0}, pair<string, int>{"S", 0}, pair<string, int>{"D", 0}, pair<string, int>{"Sp", 0}
};

vector<Bullet> AllyBullets;

int main() {

    sf::RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "scroll-shooter");
    sf::Texture ally_ship_img;
    ally_ship_img.loadFromFile("ally_ship.png");
    AllyShip player(ally_ship_img);
    player.setPosition(sf::Vector2f(MAX_X / 2, MAX_Y * 3 / 4));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !KeysDown["W"])
                KeysDown["W"] = 1;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && KeysDown["W"])
                KeysDown["W"] = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !KeysDown["A"])
                KeysDown["A"] = 1;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && KeysDown["A"])
                KeysDown["A"] = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !KeysDown["S"])
                KeysDown["S"] = 1;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && KeysDown["S"])
                KeysDown["S"] = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !KeysDown["D"])
                KeysDown["D"] = 1;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && KeysDown["D"])
                KeysDown["D"] = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !KeysDown["Sp"])
                KeysDown["Sp"] = 1;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && KeysDown["Sp"])
                KeysDown["Sp"] = 0;
        }

        player.move(0.1 * (KeysDown["D"] - KeysDown["A"]), 0.1 * (KeysDown["S"] - KeysDown["W"]));
        if (KeysDown["Sp"]) {
            player.shoot(AllyBullets, BULLET_DAMAGE);
        }

        for (auto& bul : AllyBullets) {
            bul.move(0, -1);
            bul.update_state();
        }

        window.clear();

        window.draw(player);
        for (auto& bul : AllyBullets) {
            window.draw(bul);
        }

        window.display();
    }

    return 0;
}