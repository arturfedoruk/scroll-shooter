#include "EnemyShip.h"


EnemyShip::EnemyShip(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group)
    : Sprite(t), score_counter(sc_counter), enemies_slots(en_slots), index(idx), group(group) {
	setPosition(BORDER_X + rand() % (MAX_X - 2 * BORDER_X + 1),
                BORDER_Y + rand() % (MAX_Y/2 - BORDER_X + 1));
	setOrigin(Vector2f(30, 20));
	group->push_back(*this);
    
}

void EnemyShip::shoot(vector<Bullet>& group, vector<int>& slots, int damage) {
    shootingTimer++;
    if (shootingTimer == INTENSITY) {
        Bullet(getPosition(), &group, &slots, BULLET_SPEED, 0, damage, Color::Red);
        shootingTimer = 0;
    }
}

void EnemyShip::hit(Bullet bullet) {
    auto x = bullet.getPosition().x, y = bullet.getPosition().y,
        x1 = getPosition().x - hitbox_x / 2, x2 = getPosition().x + hitbox_x / 2,
        y1 = getPosition().y - hitbox_x / 2, y2 = getPosition().y + hitbox_x / 2;
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
        lives -= bullet.damage;
        bullet.destroy();
    }
}

void EnemyShip::move() {
    setPosition(getPosition().x + vx, getPosition().y + vy);;
}

void EnemyShip::destroy() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (index == (*group)[i].index) {
            (*enemies_slots)[index] = 0;
            group->erase(group->begin() + i);
            break;
        }
    }
}

void EnemyShip::update(vector<Bullet>& g) {
    move();
    for (auto& bul : g) {
        hit(bul);
    }
    if (lives <= 0) {
        destroy();
        (*score_counter)++;
    }
}

void update(vector<EnemyShip>& group, vector<Bullet>& bullet_group) {
    for (auto& enem : group) {
        enem.update(bullet_group);
    }
}