#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
using namespace sf;
using namespace std;

class Bullet : public CircleShape {
public:
    Bullet(Vector2f position, vector<Bullet>* g, int vy);
    int vy;
    void update_state();
private:
    vector<Bullet>* group;
};