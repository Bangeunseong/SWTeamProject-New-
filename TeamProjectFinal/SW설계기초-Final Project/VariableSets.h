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

//다음 스테이지로 넘어갈 때 Duration time
#define STAGEDURATIONTIME 2.0

//-------------------------------------------------------------
//-----------------------Player 상수--------------------------

//사용자 입력 키 아스키 코드
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define SPACE 0x20
#define QUIT VK_ESCAPE

//플레이어 고유 번호 및 색깔, 무적일 때 색깔
#define PLAYER 4
#define PLAYERCOLOR 3
#define PLAYERUSINGSKILLCOLOR 13
#define PLAYERINVINSIBLEINDICATECOLOR 6

//플레이어 인풋타임 버퍼시간
double PLAYERTIMEBUFFER = 0.04;

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

//게임 Pause Time
double PausedTime = 0;

//게임 정지시간
double PausingTime = 0;

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
//-----------------------ITEM 상수----------------------------------

//아이템 움직임 버퍼 시간
#define ITEMTIMEBUFFER 0.2
double ItemInputTime = 0;
double ItemCreationLoop = 1;

//아이템 효과 모음집
#define SPEEDINCREASERATE 0.5
#define FLASHDISTANCE 3
int flashCount = 0;

//게임보드내 아이템 출력 여부
int itemFLAG = 0;

// 점멸 확인 용 변수
int flashFLAG = 0;

//아이템 X, Y 좌표
int ITEM_POS_X, ITEM_POS_Y;

//아이템과 플레이어 충돌 감지 변수
int ItemCollisionDetected = 0;

int ItemNumber = 0;

//플레이어의 주 스킬, 보조 스킬, 사용 중인 스킬
int CurSkill = 0, SubSkill = 0, UsingSkill = 0;

//스킬 지속시간, 스킬 발동 시작시간
int SkillTime = 3; double SkillActivationTime = 0;

//플레이어의 스킬 셋 string
char Skillstr[] = { "MainSkill " }; char SubSkillstr[] = { "SubSkill  " };
char SkillSets[][101] = { "-NONE-", "-SPEEDUP-","-SLOW-", "-INVINSIBLE-","-DASH-","-ERASEBULLET-" };

//아이템 출력 아이콘 리스트
char itemList[] = { 'S', 'L', 'I', 'D', 'E' };

//----------------------BULLET 상수--------------------------

#define BULLET 3								//Bullet 고유번호
#define BULLETDAMAGE 1				//Bullet Damage
#define BULLETTIMEBUFFER 0.3		//Bullet 갱신 버퍼 시간

typedef struct Bullet {						//Bullet 위치 저장 공간 구조체
	int BULLET_POS_X, BULLET_POS_Y;
	int BulletActivation;
	int CollisionPlayer;
	int CollisionWall;
}Bullet;						
Bullet bullet[1000];							//Bullet 구조체 배열

#define TOTALPATTERNCOUNT 1
#define PATTERNTIME_SPREAD 10.0//Spread 패턴 지속시간

double BulletPatternStartTime = 0;	//총알 발사 시작 시간
double BulletPatternEndTime = 0;
int PatternStart = 0;							//패턴 시작 유무
int PatternNumber = 0;					//패턴 넘버
int PatternCycle = 0;							//패턴 사이클
int BULLETCOUNT = 0;						//총알 개수
double BulletSpeed = 1;					//Bullet 속도




//Bullet 인풋 시작 시간
double BulletInputTime = 0;

#endif // !VARIABLESETS_H