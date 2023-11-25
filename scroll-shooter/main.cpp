#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

map<string, int> KeysDown{
    pair<string, int>{"W", 0}, pair<string, int>{"A", 0}, pair<string, int>{"S", 0}, pair<string, int>{"D", 0}, pair<string, int>{"Sp", 0}
};

class AllyBullet : public CircleShape {
public:
    AllyBullet(Vector2f position, vector<AllyBullet>* g) : CircleShape(5), group(g)
    {
        setPosition(position); group->push_back(*this); setFillColor(sf::Color(100, 250, 50));
    }
    int vy = -0.1;
    void update_state() {
        if (getPosition().y < 0) {
            group->erase(group->begin());
        }
    }
private:
    vector<AllyBullet>* group;
};

vector<AllyBullet> AllyBullets;

class AllyShip : public Sprite {
public:
    AllyShip(Texture& t) : Sprite(t) { setOrigin(sf::Vector2f(30, 20)); }
    void shoot(Texture& t) {
        shootingTimer++;
        if (shootingTimer == 1000) {
            AllyBullet bullet{ getPosition(), &AllyBullets };
            shootingTimer = 0;
        }
    }
private:
    int shootingTimer = 0;

};


int main() {

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::Texture ally_ship_img;
    ally_ship_img.loadFromFile("ally_ship.png");
    sf::Texture ally_bullet_img;
    ally_bullet_img.loadFromFile("ally_bullet.png");
    AllyShip player(ally_ship_img);
    player.setPosition(sf::Vector2f(400, 400));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !KeysDown["W"])
            {
                KeysDown["W"] = 1;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && KeysDown["W"])
            {
                KeysDown["W"] = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !KeysDown["A"])
            {
                KeysDown["A"] = 1;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && KeysDown["A"])
            {
                KeysDown["A"] = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !KeysDown["S"])
            {
                KeysDown["S"] = 1;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && KeysDown["S"])
            {
                KeysDown["S"] = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !KeysDown["D"])
            {
                KeysDown["D"] = 1;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && KeysDown["D"])
            {
                KeysDown["D"] = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !KeysDown["Sp"])
            {
                KeysDown["Sp"] = 1;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && KeysDown["Sp"])
            {
                KeysDown["Sp"] = 0;
            }
        }

        player.move(0.1 * (KeysDown["D"] - KeysDown["A"]), 0.1 * (KeysDown["S"] - KeysDown["W"]));
        if (KeysDown["Sp"]) {
            player.shoot(ally_bullet_img);
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