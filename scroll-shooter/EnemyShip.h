#pragma once
#include "Bullet.h"

int Rannum(int min, int max);

class EnemyShip : public Sprite {
public:
    EnemyShip(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group);
    void shoot(vector<Bullet>& group, int damage);
    int lives = ENEMY_LIVES;
    void hit(Bullet bullet);
    void move();
    void update(vector<Bullet> group);
private:
    vector<EnemyShip>* group;
    int* score_counter;
    vector<int>* enemies_slots;
    int index;
    int shootingTimer = 0;
    int hitbox_x = 100;
    int hitbox_y = 20;
    int vx=0, vy=0;

};
