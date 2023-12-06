#pragma once
#include "Bullet.h"
#include "config.h"
#include "Asteroid.h"

class AllyShip : public Sprite {
public:
    AllyShip(Texture& t);
    void shoot(vector<Bullet>& group, vector<int>& slots, int damage);
    void move(const Vector2f& offset);
    void move(float	offsetX, float offsetY);
    int lives = ALLY_LIVES;
    int shield = 0;
    int doubleshot = 0;
    void hit(Bullet bullet);
    void hit2(Asteroid bullet);
    void update(vector<Bullet> group);
    void update2(vector<Asteroid> group);
private:
    int shootingTimer = 0; // עאילונ סענוכüבû
    int hitbox_x = 56;
    int hitbox_y = 16;

};

class Background : public Sprite {
public:
    Background(Texture& t);
    void update();
};
