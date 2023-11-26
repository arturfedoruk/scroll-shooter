#pragma once
#include "Bullet.h"

int Rannum(int min, int max);

class EnemyShip : public Sprite {
public:
    EnemyShip(Texture& t, int* sc_counter, int* en_counter, vector<EnemyShip>* group);
    void shoot(vector<Bullet>& group, int damage);
    int lives = ENEMY_LIVES;
    void hit(Bullet bullet);
    void move();
    void update(vector<Bullet> group);
private:
    vector<EnemyShip>* group;
    int* score_counter;
    int* enemies_counter;
    int shootingTimer = 0;
    int hitbox_x = 100;
    int hitbox_y = 20;
    int vx=0, vy=0;

};
