#pragma warning(disable : 4996)
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
using namespace sf;
using namespace std; 

// � ���� 30 ����� � �������
#define MAX_X 700
#define MAX_Y 720
#define BORDER_X 36
#define BORDER_Y 36 // ������� ���� � �������
#define BACKGROUND_SPEED 4 // �������� ��������� ����

#define PLAYER_SPEED 10
#define ENEMY_SPEED 5

#define ALLY_LIVES 5
#define ENEMY_LIVES 2

#define PLAYER_INTENSITY 15
#define INTENSITY 30 // ����� ����� ����� ����������

#define BULLET_DAMAGE 1
#define BULLET_SPEED 20

#define SPAWN_TIME 120 // ����� ����� ����� ������ ���������� ����������
#define MAX_ENEMIES 5


