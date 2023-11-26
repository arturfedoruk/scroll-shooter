#pragma once
#include "config.h"
using namespace std;

class Bullet : public CircleShape {
public:
    Bullet(Vector2f position, vector<Bullet>* g, float vy, int damage, Color color);
    void move();
    float vy;
    void update();
    int damage;
private:
    vector<Bullet>* group;
};