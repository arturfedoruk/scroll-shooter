#pragma once
#include "config.h"
using namespace std;


class Asteroid : public CircleShape {
public:
    Asteroid(Vector2f position, vector<Asteroid>* group, vector<int>* slots, float vy, float vx, int damage, Color color);
    void move();
    float vy, vx; // скорости вдоль Х и У
    void update();
   
    int damage;
    int index; // индекс пули
    void destroy();
private:
    vector<Asteroid>* group; // вектор из пулек
    vector<int>* slots; // вектор занятости индексов
    // каждому камню присваивается индекс, чтобы его можно было легко удалить из массива врагов
    // для этого же храним вектор, показывающий, заняты ли соответствующие индексы
};

void update(vector<Asteroid>& group);
