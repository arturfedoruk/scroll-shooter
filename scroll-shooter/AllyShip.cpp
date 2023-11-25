#include "AllyShip.h"

AllyShip::AllyShip(Texture& t) : Sprite(t) { setOrigin(sf::Vector2f(30, 20)); }

void AllyShip::shoot(vector<Bullet>& group, int damage) {
    shootingTimer++;
    if (shootingTimer == 1000) {
        Bullet bullet{ getPosition(), &group, -1, damage };
        shootingTimer = 0;
    }
}

void AllyShip::move(const Vector2f& offset) {
    setPosition(getPosition() + offset);
    if (getPosition().x > MAX_X - BORDER_X) {
        setPosition(MAX_X - BORDER_X, getPosition().y);
    }
    if (getPosition().x < BORDER_X) {
        setPosition(BORDER_X, getPosition().y);
    }
    if (getPosition().y > MAX_Y - BORDER_Y) {
        setPosition(getPosition().x, MAX_Y - BORDER_Y);
    }
    if (getPosition().y < MAX_Y / 2) {
        setPosition(getPosition().x, MAX_Y / 2);
    }
}

void AllyShip::move(float offsetX, float offsetY) {
    setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    if (getPosition().x > MAX_X - BORDER_X) {
        setPosition(MAX_X - BORDER_X, getPosition().y);
    }
    if (getPosition().x < BORDER_X) {
        setPosition(BORDER_X, getPosition().y);
    }
    if (getPosition().y > MAX_Y - BORDER_Y) {
        setPosition(getPosition().x, MAX_Y - BORDER_Y);
    }
    if (getPosition().y < MAX_Y / 2) {
        setPosition(getPosition().x, MAX_Y / 2);
    }
}

void AllyShip::hit(Bullet bullet) {
    auto x = bullet.getPosition().x, y = bullet.getPosition().y,
        x1 = getPosition().x - hitbox_x / 2, x2 = getPosition().x + hitbox_x / 2,
        y1 = getPosition().y - hitbox_x / 2, y2 = getPosition().y + hitbox_x / 2;
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
        lives -= bullet.damage;
    }
}