#pragma once
#include "Bullet.h"

class EnemyShip : public Sprite {
public:
    EnemyShip(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group);
    void shoot(vector<Bullet>& group, vector<int>& slots, int damage);
    int lives = ENEMY_LIVES;
    void destroy(vector<Bullet>& g, vector<int>& slots);
    void hit(Bullet bullet);
    void move();
    void update(vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots);
    int* score_counter; // ссылка на счетчик счета игрока
    int vx = 0, vy = 0; // скорость вдоль Х и У
private:
    vector<EnemyShip>* group; // вектор противников
    vector<int>* enemies_slots; // вектор занятости индексов
    int index; // индекс каждого вражеского корабля
    int shootingTimer = 0; // таймер перед выстрелом
    int hitbox_x = 100;
    int hitbox_y = 20; // хитбокс
    // каждому вражескому кораблю присваивается индекс, чтобы его можно было легко удалить из массива врагов
    // для этого же храним вектор, показывающий, заняты ли соответствующие индексы
};

void update(vector<EnemyShip>& group, vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots);

class LineEnemy : public EnemyShip {
public:
    LineEnemy(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group, int r);
    void update(vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots);
private:
    int r;
    int x0, y0;
};

class CircleEnemy : public EnemyShip {
public:
    CircleEnemy(Texture& t, int* sc_counter, vector<int>* en_slots, int idx, vector<EnemyShip>* group, int r);
    void update(vector<Bullet>& enemy_bullet_group, vector<Bullet>& ally_bullet_group, vector<int>& slots);
private:
    int r;
    int x0, y0;
    float phi;
};

// LineEnemy и CircleEnemy почему-то не работают....
