#pragma once
#include <Windows.h>
#ifndef VARIABLESETS_H
#define VARIABLESETS_H
//-------------------------------------------
//-------------BackGround 상수------------

//게임영역 정의
#define BACKGROUND_ROW 90
#define BACKGROUND_COLUMN 43
#define BACKGROUND_ORIGIN_X 8
#define BACKGROUND_ORIGIN_Y 1
#define GAMEBOARD_ROW 90
#define GAMEBOARD_COLUMN 40
#define GAMEBOARD_ORIGIN_X 8
#define GAMEBOARD_ORIGIN_Y 4

//게임화면의 이산 모델
int UniBoard[GAMEBOARD_COLUMN + 1][GAMEBOARD_ROW + 2];

//게임 인트로 제목
char IntroModel[][5][5] = {
	{{0,0,1,0,0},{0,1,0,1,0},{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1}},
	{{0,1,1,1,1},{1,0,0,0,0},{0,1,1,1,0},{0,0,0,0,1},{1,1,1,1,0}},
	{{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
	{{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1}},
	{{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}},
	{{1,0,0,0,1},{1,1,0,0,1},{1,0,1,0,1},{1,0,0,1,1},{1,0,0,0,1}},
	{{0,0,1,0,0},{0,1,0,1,0},{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1}},
	{{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}},
	{{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}}
};

//--------------------------------------------
//--------------StartMenu 상수-------------

#define MODESELECTIONBOX_ROW 18 //게임 모드 선택박스 가로 길이
#define MODESELECTIONBOX_COLUMN 3 // 게임 모드 선택박스 세로 길이
int ModeSelectionBox_Origin_X = BACKGROUND_ORIGIN_X + 14; //게임 모드 선택 박스 초기 X좌표
int ModeSelectionBox_Origin_Y = BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 6; //게임 모드 선택 박스 초기 Y좌표

//게임 모드
int GameMode = 0;

//-----------------------------------------------------------
//-------------CharacterSelectionMenu 상수--------------

//캐릭터 박스 Dimension
#define CHARACTERBOX_ROW 28
#define CHARACTERBOX_COLUMN 20
#define CHARACTERBOX_ORIGIN_X 6
#define CHARACTERBOX_ORIGIN_Y 12

//-------------------------------------------
//------------StageMenu 상수-------------

//스테이지 번호
int StageNumber = 1;

//스테이지별 플레이 시간
int StageTime[] = { 60,90,120 };

//-------------------------------------------------------------
//-----------------------Player 상수--------------------------

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

//플레이어 인풋타임 버퍼시간
double PLAYERTIMEBUFFER = 0.035;

//플레이어 인풋타임 시작시간
double PlayerInputTime = 0;

//플레이어 시작 위치
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

//플레이어 우주선
char PlayerModel[6];
char PlayerUniModel[6] = { PLAYER,PLAYER,PLAYER,PLAYER,PLAYER,PLAYER };

//플레이어 무적상태 및 무적상태 지속시간, 총알 및 적 우주선과 충돌한 시간
#define InvinsibleTime 1
int Invinsible = 0; double CollisionTime = 0;

//플레이어의 라이프게이지
int SelectedLife = 5; int CurrentLife; int *LifeGauge;

//플레이어의 위치
int PlayerPos = 0;

//플레이어의 속도
double SelectedSpeed, CurSpeed;

//플레이어의 주 스킬, 보조 스킬, 사용 중인 스킬
int CurSkill = 0, SubSkill = 0, UsingSkill = 0, SkillTime = 3; double SkillActivationTime = 0;

//플레이어의 스킬 셋 string
char Skillstr[] = { "MainSkill " }; char SubSkillstr[] = { "SubSkill  " };
char SkillSets[][101] = { "-NONE-", "-DASH-","-SLOW-", "-INVINSIBLE-" };
//---------------------------------------------------------------
//----------------------Enemy 상수----------------------------

//적 NPC 인풋타임 버퍼 시간
double ENEMYTIMEBUFFER = 0.02;

//적 NPC 인풋타임 시작시간
double EnemyInputTime = 0;

//적 우주선 및 총알
#define ENEMY 2
#define ENEMYDAMAGE 2
#define ENEMYBULLET 3

//적 우주선 위치 및 이동방향
int ENEMY_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int ENEMY_POS_Y = GAMEBOARD_ORIGIN_Y + 1;
int direction = 0;

//적 우주선 모델링
char EnemyModel[3][5] = { {' ','^','V','^',' '},{'<','<','O','>','>'},{' ','^','V','^',' '} };
char EnemyUniModel[3][5] = { {0,ENEMY,ENEMY,ENEMY,0},{ENEMY,ENEMY,ENEMY,ENEMY,ENEMY},{0,ENEMY,ENEMY,ENEMY,0} };

//-------------------------------------------------------------------
//-------------------------Timer 상수------------------------------

//Timer 함수 이용시 필요한 상수
LARGE_INTEGER ticksPerSec;
LARGE_INTEGER start, end, diff;

//초 단위로 저장
double CurrentTime = 1;

//-------------------------------------------------------------------
//------------------------UI 상수-----------------------------------

//Modified 함수
int Strlen(const char *src) {
	int cnt = 0;
	for (const char *p = src; *p != '-'; p++) cnt++;
	return cnt + 1;
}

//맵의 길이
#define MAPLENGTH 15

//--------------------------------------------------------------------

#endif // !VARIABLESETS_H
