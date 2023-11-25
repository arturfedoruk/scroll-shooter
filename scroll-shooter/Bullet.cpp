#include "Bullet.h"

Bullet::Bullet(Vector2f position, vector<Bullet>* g, int vy) : CircleShape(5), group(g), vy(vy){
    setPosition(position); group->push_back(*this); setFillColor(sf::Color(100, 250, 50));
}

void Bullet::update_state() {
    if (getPosition().y < 0) {
        group->erase(group->begin());
    }
}