#pragma once
#include "Bullet.h"
#include "config.h"

class AllyShip : public Sprite {
public:
    AllyShip(Texture& t);
    void shoot(vector<Bullet>& group, int damage);
    void move(const Vector2f& offset);
    void move(float	offsetX, float offsetY);
    int lives = ALLY_LIVES;
    void hit(Bullet bullet);
    void update(vector<Bullet> group);
private:
    int save=0;
    int shootingTimer = 0;
    int hitbox_x = 56;
    int hitbox_y = 16;

};
