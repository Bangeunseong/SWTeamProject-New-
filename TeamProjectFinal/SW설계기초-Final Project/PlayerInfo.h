#pragma once
#include "BackGround.h"
#ifndef PLAYERINFO_H
#define PLAYERINFO_H

//사용자 입력 키 아스키 코드
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define SPACE 0x20
#define QUIT 0x1A

//플레이어 고유 번호 및 색깔, 무적일 때 색깔
#define PLAYER 4
#define PLAYERCOLOR 3
#define PLAYERUSINGSKILLCOLOR 13
#define PLAYERINVINSIBLEINDICATECOLOR 6

//플레이어 시작 위치
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

//플레이어 우주선
char PlayerModel[6];
char PlayerUniModel[6] = { PLAYER,PLAYER,PLAYER,PLAYER,PLAYER,PLAYER };

//플레이어 무적상태 및 무적상태 지속시간, 총알 및 적 우주선과 충돌한 시간
int Invinsible = 0; int InvinsibleTime = 1; double CollisionTime = 0;

//플레이어의 라이프게이지
int SelectedLife = 5; int CurrentLife; int *LifeGauge;

//플레이어의 위치
int PlayerPos = 0;

//플레이어의 속도
int SelectedSpeed, CurSpeed;

//플레이어의 주 스킬, 보조 스킬, 사용 중인 스킬
int CurSkill = 1, SubSkill = 2, UsingSkill = 0, SkillTime = 3; double SkillActivationTime = 0;

//플레이어의 스킬 셋 string
char Skillstr[] = { "Skill1 -" }; char SubSkillstr[] = { "Skill2 -" };
char SkillSets[][101] = { "NONE-", "DASH-","SLOW-", "INVINSIBLE-" };

#endif // !PLAYERINFO_H