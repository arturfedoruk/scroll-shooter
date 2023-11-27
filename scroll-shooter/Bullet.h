#pragma once
#include "config.h"
using namespace std;


class Bullet : public CircleShape {
public:
    Bullet(Vector2f position, vector<Bullet>* group, vector<int>* slots, float vy, float vx, int damage, Color color);
    void move();
    float vy, vx; // скорости вдоль Х и У
    void update();
    int damage;
    int index; // индекс пули
    void destroy();
private:
    vector<Bullet>* group; // вектор из пулек
    vector<int>* slots; // вектор занятости индексов
    // каждой пуле присваивается индекс, чтобы ее можно было легко удалить из массива врагов
    // для этого же храним вектор, показывающий, заняты ли соответствующие индексы
};

void update(vector<Bullet>& group);
