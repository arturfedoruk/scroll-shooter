#pragma once
#include "config.h"
using namespace std;


class Bullet : public CircleShape {
public:
    Bullet(Vector2f position, vector<Bullet>* group, vector<int>* slots, float vy, float vx, int damage, Color color);
    void move();
    float vy;
    float vx;
    void update();
    int damage;
    int index;
    void destroy();
private:
    vector<Bullet>* group;
    vector<int>* slots;
};

void update(vector<Bullet>& group);
