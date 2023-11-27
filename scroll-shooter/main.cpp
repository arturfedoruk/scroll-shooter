#include "config.h"
#include "Bullet.h"
#include "AllyShip.h"
#include "EnemyShip.h"

map<string, int> KeysDown{
    pair<string, int>{"W", 0}, pair<string, int>{"A", 0}, pair<string, int>{"S", 0}, pair<string, int>{"D", 0}, pair<string, int>{"Sp", 0}
};//словарь нажатых клавиш

vector<Bullet> AllyBulletGroup;
vector<Bullet> EnemyBulletGroup;
vector<EnemyShip> EnemyShipGroup;
// группы союзных, вражеских пуль и вражеских кораблей

int spawn_timer = 0; // таймер спавна врагов
int score = 0; // счетчик сщета
vector<int> enemies_slots;
vector<int> bullets_slots; // массивы занятости индексов

int main() {
    srand(time(NULL)); // генерация рандома

    RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "scroll-shooter");
    window.setVerticalSyncEnabled(true); // создали окно

    Texture ally_ship_img;
    ally_ship_img.loadFromFile("images/ally_ship.png");
    Texture enemy_ship_img;
    enemy_ship_img.loadFromFile("images/enemy_ship.png");
    Texture line_enemy_img;
    line_enemy_img.loadFromFile("images/line_enemy.png");
    Texture circle_enemy_img;
    circle_enemy_img.loadFromFile("circle_enemy.png");
    Texture background_img;
    background_img.loadFromFile("images/back.png");
    //текстурочьки
    
    Background background(background_img);
    AllyShip player(ally_ship_img);
    // фон и игрок

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies_slots.push_back(0);
    }
    for (int i = 0; i < 200; i++) {
        bullets_slots.push_back(0);
    }
    // заполняем массивы индексов

    Font font;
    font.loadFromFile("arial.ttf");
    Text bar;
    bar.setFont(font);
    bar.setString("Lives: " + to_string(player.lives) + ", Score: " + to_string(score));
    bar.setCharacterSize(24);
    bar.setColor(Color::Yellow);
    // надпись

    while (window.isOpen())
    {
        sf::Event event;
        // считываем событие
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
        // на основе ввода пользователя перемещаем игрока

        player.update(EnemyBulletGroup);
        bar.setString("Lives: " + to_string(player.lives) + "\nScore: " + to_string(score));
        if (player.lives <= 0) {
            window.close();
        }// обновление состояния игрока

        background.update();

        if (KeysDown["Sp"]) {
            player.shoot(AllyBulletGroup, bullets_slots, BULLET_DAMAGE);
        } // если пробел, то стреляем

        update(EnemyShipGroup, AllyBulletGroup);
        update(AllyBulletGroup); update(EnemyBulletGroup);
        // обносление состояния пулек и врагов

        spawn_timer++;
        if (spawn_timer == SPAWN_TIME) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (!enemies_slots[i]) {

                    /*int who = rand() % 5;
                    if(who == 1){
                        LineEnemy(line_enemy_img, &score, &enemies_slots, i, &EnemyShipGroup, rand() % 20 + 10);
                    }
                    else if (who == 2) {
                        CircleEnemy(circle_enemy_img, &score, &enemies_slots, i, &EnemyShipGroup, rand() % 20 + 10);
                    }
                    else {
                        EnemyShip(enemy_ship_img, &score, &enemies_slots, i, &EnemyShipGroup);
                    } случайно выбираем тип заспавненного врага */

                    EnemyShip(enemy_ship_img, &score, &enemies_slots, i, &EnemyShipGroup);
                    enemies_slots[i] = 1;
                    break; // занимаем свободный индекс
                }
            }
            spawn_timer = 0;
        }// спавн противников

        for (auto& enem : EnemyShipGroup) {
            enem.shoot(EnemyBulletGroup, bullets_slots, BULLET_DAMAGE);
        }//враги стреляют

        window.clear();

        window.draw(background);
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
        // всё отрисовываем

        window.display();
    }

    return 0;
}