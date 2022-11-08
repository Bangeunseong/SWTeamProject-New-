#pragma once
#include "BackGround.h"
#ifndef ENEMYINFO_H
#define ENEMYINFO_H

//�� ���ּ� �� �Ѿ�
#define ENEMY 2
#define ENEMYDAMAGE 2
#define ENEMYBULLET 3

//�� ���ּ� ��ġ �� �̵�����
int ENEMY_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int ENEMY_POS_Y = GAMEBOARD_ORIGIN_Y + 1;
int direction = 0;

//�� ���ּ� �𵨸�
char EnemyModel[3][5] = { {' ','^','V','^',' '},{'<','<','O','>','>'},{' ','^','V','^',' '} };
char EnemyUniModel[3][5] = { {0,ENEMY,ENEMY,ENEMY,0},{ENEMY,ENEMY,ENEMY,ENEMY,ENEMY},{0,ENEMY,ENEMY,ENEMY,0} };

#endif // !ENEMYINFO_H
