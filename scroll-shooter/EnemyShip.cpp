#include "EnemyShip.h"


EnemyShip::EnemyShip(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group)
    : Sprite(t), score_counter(sc_counter), enemies_slots(en_slots), index(idx), group(group) {
	setPosition(BORDER_X + rand() % (MAX_X - 2 * BORDER_X + 1),
                BORDER_Y + rand() % (MAX_Y/2 - BORDER_X + 1)); // случайное положение на поле
	setOrigin(Vector2f(30, 20));
	group->push_back(*this);
    
}





void EnemyShip::shoot(vector<Bullet>& group, vector<int>& slots, int damage) {
    shootingTimer++; // таймер пальбы
    if (shootingTimer == INTENSITY) {
        Bullet(getPosition(), &group, &slots, BULLET_SPEED, BULLET_DAMAGE, damage, Color::Red, "ubivec");
        shootingTimer = 0;
    }
}

void EnemyShip::hit(Bullet bullet) {
    // проверяет столкновение с пулей
    auto x = bullet.getPosition().x, y = bullet.getPosition().y,
        x1 = getPosition().x - hitbox_x / 2, x2 = getPosition().x + hitbox_x / 2,
        y1 = getPosition().y - hitbox_x / 2, y2 = getPosition().y + hitbox_x / 2;
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2 && bullet.type == "ubivec") {
        lives -= bullet.damage;
        bullet.destroy();
    }
}

void EnemyShip::move() {
    setPosition(getPosition().x + vx, getPosition().y + vy);;
}

void EnemyShip::destroy(vector<Bullet>& enemy_bullet_group, vector<int>& slots) {
    int type_of_death = rand() % 8;
    if (type_of_death == 3) {
        Bullet(getPosition(), &enemy_bullet_group, &slots, FALL_SPEED, 0, -HEALING, Color::Magenta, "hitler");
    }
    if (type_of_death == 4) {
        Bullet(getPosition(), &enemy_bullet_group, &slots, FALL_SPEED, 0, 0, Color::Cyan, "duble");
    }
    if (type_of_death == 5) {
        Bullet(getPosition(), &enemy_bullet_group, &slots, FALL_SPEED, 0, 0, Color::Yellow, "shit");
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (index == (*group)[i].index) {
            (*enemies_slots)[index] = 0;
            group->erase(group->begin() + i);
            break;
        }
    }//удаляем из массива врагов
}

void EnemyShip::update(vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots) {
    // обновление состояния
    move();
    for (auto& bul : ally_bullet_group) {
        hit(bul);
    }
    if (lives <= 0) {
        destroy(enemy_bullet_group, slots);
        (*score_counter)++;
    }
}

void update(vector<EnemyShip>& group, vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots) {
    for (auto& enem : group) {
        enem.update(enemy_bullet_group, ally_bullet_group, slots);
    }
}

/*LineEnemy::LineEnemy(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group, int r)
                  : EnemyShip(t, sc_counter, en_slots, idx, group), r(r) {
    vx = ENEMY_SPEED; vy = ENEMY_SPEED;
    x0 = BORDER_X + rand() % (MAX_X - 2 * BORDER_X - r + 1);
    y0 = BORDER_Y + rand() % (MAX_Y / 2 - BORDER_X - r + 1);
    setPosition(x0,y0);
    setOrigin(Vector2f(30, 20));
    group->push_back(*this);
};

void LineEnemy::update(vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots) {
    // обновление состояния
    move();
    for (auto& bul : ally_bullet_group) {
        hit(bul);
    }
    if (lives <= 0) {
        destroy(enemy_bullet_group, slots);
        (*score_counter)++;
    }
    if (getPosition().y < y0 - r || getPosition().y > y0 + r) {
        vx *= -1; vy *= -1;
    }
}


CircleEnemy::CircleEnemy(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group, int r)
    : EnemyShip(t, sc_counter, en_slots, idx, group), r(r), phi(0) {
    vx = ENEMY_SPEED; vy = 0;
    x0 = BORDER_X + rand() % (MAX_X - 2 * BORDER_X - r + 1);
    y0 = BORDER_Y + rand() % (MAX_Y / 2 - BORDER_X - r + 1);
    setPosition(x0, y0);
    setOrigin(Vector2f(30, 20));
    group->push_back(*this);
};

void CircleEnemy::update(vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots) {
    // обновление состояния
    move();
    for (auto& bul : ally_bullet_group) {
        hit(bul);
    }
    if (lives <= 0) {
        destroy(enemy_bullet_group, slots);
        (*score_counter)++;
    }
    if (getPosition().y < y0 - r || getPosition().y > y0 + r) {
        vx *= -1; vy *= -1;
    }
    phi += 0.1;
    vx = ENEMY_SPEED * cos(phi);
    vy = ENEMY_SPEED * sin(phi);
}
*/

