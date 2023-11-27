#include "AllyShip.h"

AllyShip::AllyShip(Texture& t) : Sprite(t) { setPosition(Vector2f(MAX_X / 2, MAX_Y * 3 / 4)); 
                                             setOrigin(Vector2f(30, 20)); }

void AllyShip::shoot(vector<Bullet>& group, vector<int>& slots, int damage) {
    shootingTimer++;
    if (shootingTimer == PLAYER_INTENSITY) {
        Bullet(getPosition(), &group, &slots, -BULLET_SPEED, 0, damage, Color::Green);
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
        bullet.destroy();
    }
}

void AllyShip::update(vector<Bullet> group) {
    for (auto& bul : group) {
        hit(bul);
    }
}

Background::Background(Texture& t) : Sprite(t) { setPosition(0, -2400); }

void Background::update(){
    move(0, BACKGROUND_SPEED);
    if (getPosition().y >= 0) {
        setPosition(0, -2400);
    }
}