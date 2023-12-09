#include "AllyShip.h"

AllyShip::AllyShip(Texture& t) : Sprite(t) { setPosition(Vector2f(MAX_X / 2, MAX_Y * 3 / 4)); 
                                             setOrigin(Vector2f(30, 20)); }

void AllyShip::shoot(vector<Bullet>& group, vector<int>& slots, int damage) {
    shootingTimer++; // таймер пальбы
    if (shootingTimer == PLAYER_INTENSITY) {
        Bullet(getPosition(), &group, &slots, -BULLET_SPEED, 0, damage, Color::Green, "ubivec");
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
    // проверка, чтобы не улететь за экран
}

void AllyShip::move(float offsetX, float offsetY) {
    // аж две функции прописал, какой я молодец
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
    // проверка столкновения с пулькой
    auto x = bullet.getPosition().x, y = bullet.getPosition().y,
        x1 = getPosition().x - hitbox_x / 2, x2 = getPosition().x + hitbox_x / 2,
        y1 = getPosition().y - hitbox_x / 2, y2 = getPosition().y + hitbox_x / 2;
    
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2 && ( bullet.type == "ubivec" || bullet.type == "hitler")) {
        lives -= bullet.damage;
        bullet.destroy();
    } 
    /*if (x1 <= x && x <= x2 && y1 <= y && y <= y2 && bullet.type == "hitler") {
        lives += HEALING;
        bullet.destroy();
    }*/
}

void AllyShip::update(vector<Bullet> group) {
    // обновление состояния
    for (auto& bul : group) {
        hit(bul);
    }
}

void AllyShip::hit(Asteroid bullet) {
    // проверка столкновения с астероидом (костыыль)
    auto x = bullet.getPosition().x, y = bullet.getPosition().y,
        x1 = getPosition().x - hitbox_x, x2 = getPosition().x + hitbox_x,
        y1 = getPosition().y - hitbox_x, y2 = getPosition().y + hitbox_x;
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
        lives -= bullet.damage;
        bullet.destroy();
    }
}

void AllyShip::update(vector<Asteroid> group) {
    // обновление состояния (вариант для астероидов) (костыыль)
    for (auto& bul : group) {
        hit(bul);
    }
}

Background::Background(Texture& t) : Sprite(t) { setPosition(0, -2400); }

void Background::update(){
    // прокручивает зацикленный фон
    setPosition(0, getPosition().y + BACKGROUND_SPEED);
    if (getPosition().y >= 0) {
        setPosition(0, -2400);
    }
}