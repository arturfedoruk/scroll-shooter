#pragma once
#include "Bullet.h"
#include "config.h"

class AllyShip : public Sprite {
public:
    AllyShip(Texture& t);
    void shoot(vector<Bullet>& group);
private:
    int shootingTimer = 0;

};
