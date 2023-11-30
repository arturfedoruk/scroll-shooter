#pragma once
#include "config.h"
using namespace std;


class Asteroid : public CircleShape {
public:
    Asteroid(Vector2f position, vector<Asteroid>* group, vector<int>* slots, float vy, float vx, int damage, Color color);
    void move();
    float vy, vx; // �������� ����� � � �
    void update();
   
    int damage;
    int index; // ������ ����
    void destroy();
private:
    vector<Asteroid>* group; // ������ �� �����
    vector<int>* slots; // ������ ��������� ��������
    // ������� ����� ������������� ������, ����� ��� ����� ���� ����� ������� �� ������� ������
    // ��� ����� �� ������ ������, ������������, ������ �� ��������������� �������
};

void update(vector<Asteroid>& group);
