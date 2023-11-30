#include "Asteroid.h"

Asteroid::Asteroid(Vector2f position, vector<Asteroid>* group, vector<int>* slts, float vy, float vx, int damage, Color color)
    : CircleShape(5), group(group), slots(slts), vy(vy), vx(vx), damage(damage) {
    setPosition(position); setFillColor(color);
    group->push_back(*this);
    for (int i = 0; i < 400; i++) {
        if (!(*slots)[i]) {
            (*slots)[i] = 1;
            index = i;
            break;
        }
    }//занимает свободный индекс
}

void Asteroid::move() {
    setPosition(getPosition().x + vx, getPosition().y + vy);
}

void Asteroid::destroy() {
    for (int i = 0; i < group->size(); i++) {
        if (index == (*group)[i].index) {
            (*slots)[i] = 0;
            group->erase(group->begin() + i);
            break;
        }
    }
}

void Asteroid::update() {
    //обновление состояния
    move();
    if (getPosition().y < 0 || getPosition().y > 1.2 * MAX_Y) {
        destroy();
    }
}

void update(vector<Asteroid>& group) {
    // штоб по многу раз не переписывать
    for (auto& bul : group) {
        bul.update();
    }
}

