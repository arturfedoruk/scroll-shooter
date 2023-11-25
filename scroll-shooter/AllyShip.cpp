#include "AllyShip.h"

AllyShip::AllyShip(Texture& t) : Sprite(t) { setOrigin(sf::Vector2f(30, 20)); }

void AllyShip::shoot(vector<Bullet>& group) {
    shootingTimer++;
    if (shootingTimer == 1000) {
        Bullet bullet{ getPosition(), &group, -1 };
        shootingTimer = 0;
    }
}