#include "config.h"
#include "Bullet.h"
#include "AllyShip.h"
#include "EnemyShip.h"


map<string, int> KeysDown{
    pair<string, int>{"W", 0}, pair<string, int>{"A", 0}, pair<string, int>{"S", 0}, pair<string, int>{"D", 0}, pair<string, int>{"Sp", 0}
};

vector<Bullet> AllyBulletGroup;
vector<Bullet> EnemyBulletGroup;
vector<EnemyShip> EnemyShipGroup;

int spawn_timer = 0;
int enemies_counter = 0;
int score = 0;

int main() {

    srand(time(NULL));
    RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "scroll-shooter");
    Texture ally_ship_img;
    ally_ship_img.loadFromFile("images/ally_ship.png");
    Texture enemy_ship_img;
    enemy_ship_img.loadFromFile("images/enemy_ship.png");
        
    AllyShip player(ally_ship_img);

    Font font;
    font.loadFromFile("arial.ttf");
    Text bar;
    bar.setFont(font);
    bar.setString("Lives: " + to_string(player.lives) + ", Score: " + to_string(score));
    bar.setCharacterSize(24);
    bar.setColor(Color::Yellow);

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

        player.move(PLAYER_SPEED * (KeysDown["D"] - KeysDown["A"]), PLAYER_SPEED * (KeysDown["S"] - KeysDown["W"]));
        player.update(EnemyBulletGroup);
        bar.setString("Lives: " + to_string(player.lives) + ", Score: " + to_string(score));
        if (player.lives <= 0) {
            window.close();
        }

        if (KeysDown["Sp"]) {
            player.shoot(AllyBulletGroup, BULLET_DAMAGE);
        }

        for (auto& enem : EnemyShipGroup) {
            enem.update(AllyBulletGroup);
        }
        for (auto& bul : AllyBulletGroup) {
            bul.update();
        }
        for (auto& bul : EnemyBulletGroup) {
            bul.update();
        }

        spawn_timer++;
        if (spawn_timer == SPAWN_TIME && enemies_counter < 3) {
            EnemyShip(enemy_ship_img, &score, &enemies_counter, &EnemyShipGroup);
            enemies_counter++;
            spawn_timer = 0;
        }

        for (auto& enem : EnemyShipGroup) {
            enem.shoot(EnemyBulletGroup, BULLET_DAMAGE);
        }

        window.clear();

        window.draw(player);
        for (auto& enem : EnemyShipGroup) {
            window.draw(enem);
        }
        for (auto& bul : AllyBulletGroup) {
            window.draw(bul);
        }
        for (auto& bul : EnemyBulletGroup) {
            window.draw(bul);
        }
        window.draw(bar);

        window.display();
    }

    return 0;
}