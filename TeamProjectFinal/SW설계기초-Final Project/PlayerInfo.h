#pragma once
#include "BackGround.h"
#ifndef PLAYERINFO_H
#define PLAYERINFO_H

//����� �Է� Ű �ƽ�Ű �ڵ�
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define SPACE 0x20
#define QUIT 0x1A

//�÷��̾� ���� ��ȣ �� ����, ������ �� ����
#define PLAYER 4
#define PLAYERCOLOR 3
#define PLAYERUSINGSKILLCOLOR 13
#define PLAYERINVINSIBLEINDICATECOLOR 6

//�÷��̾� ���� ��ġ
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

//�÷��̾� ���ּ�
char PlayerModel[6];
char PlayerUniModel[6] = { PLAYER,PLAYER,PLAYER,PLAYER,PLAYER,PLAYER };

//�÷��̾� �������� �� �������� ���ӽð�, �Ѿ� �� �� ���ּ��� �浹�� �ð�
int Invinsible = 0; int InvinsibleTime = 1; double CollisionTime = 0;

//�÷��̾��� ������������
int SelectedLife = 5; int CurrentLife; int *LifeGauge;

//�÷��̾��� ��ġ
int PlayerPos = 0;

//�÷��̾��� �ӵ�
int SelectedSpeed, CurSpeed;

//�÷��̾��� �� ��ų, ���� ��ų, ��� ���� ��ų
int CurSkill = 1, SubSkill = 2, UsingSkill = 0, SkillTime = 3; double SkillActivationTime = 0;

//�÷��̾��� ��ų �� string
char Skillstr[] = { "Skill1 -" }; char SubSkillstr[] = { "Skill2 -" };
char SkillSets[][101] = { "NONE-", "DASH-","SLOW-", "INVINSIBLE-" };

#endif // !PLAYERINFO_H