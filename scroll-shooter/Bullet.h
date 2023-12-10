#pragma once
#include "config.h"
using namespace std;


class Bullet : public CircleShape {
public:
    Bullet(Vector2f position, vector<Bullet>* group, vector<int>* slots, float vy, float vx, int damage, Color color, string type);
    void move();
    float vy, vx; // �������� ����� � � �
    void update();
    int damage;
    string type;
    int index; // ������ ����
    void destroy();
    vector<int>* slots;
private:
    vector<Bullet>* group; // ������ �� �����
     // ������ ��������� ��������
    // ������ ���� ������������� ������, ����� �� ����� ���� ����� ������� �� ������� ������
    // ��� ����� �� ������ ������, ������������, ������ �� ��������������� �������
};

void update(vector<Bullet>& group);
