#include "Bullet.h"

Bullet::Bullet(Vector2f position, vector<Bullet>* g, float vy, int damage, Color color)
    : CircleShape(5), group(g), vy(vy), damage(damage){
    setPosition(position); setFillColor(color); 
    group->push_back(*this);
}

void Bullet::move() {
    setPosition(getPosition().x, getPosition().y + vy);
}

void Bullet::update() {
    move();
    if (getPosition().y < 0 || getPosition().y > 1.2 * MAX_Y) {
        group->erase(group->begin());
    }
}
