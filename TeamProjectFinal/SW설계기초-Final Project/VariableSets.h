#pragma once
#include <Windows.h>
#ifndef VARIABLESETS_H
#define VARIABLESETS_H
//-------------------------------------------
//-------------Console 창 상수-------------

//콘솔 창 ROW 길이
#define CONSOLE_ROW 45

//콘솔 창 COLUMN 길이
#define CONSOLE_COLUMN 108

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
#define WALL 1

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

//다음 스테이지로 넘어갈 때 Duration time
#define STAGEDURATIONTIME 2.0


#define OPTIONSELECTIONBOX_ROW 18 //게임 모드 선택박스 가로 길이
#define OPTIONSELECTIONBOX_COLUMN 3 // 게임 모드 선택박스 세로 길이
int OptionSelectionBox_Origin_X = BACKGROUND_ORIGIN_X + 22; //게임 모드 선택 박스 초기 X좌표
int OptionSelectionBox_Origin_Y = BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 6; //게임 모드 선택 박스 초기 Y좌표

//Game Over시 출력 로고
char GameOverLogo[][5][5] = {
	{{0,1,1,1,1},{1,0,0,0,0},{1,0,1,1,1},{1,0,0,0,1},{0,1,1,1,1}},
{{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,1},{0,0,0,0,1}},
{{1,1,1,1,1},{1,0,1,0,1},{1,0,1,0,1},{1,0,1,0,1},{1,0,1,0,1}},
{{0,1,1,1,0},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,0},{0,1,1,1,1}},
{{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}},
{{1,0,0,0,1},{1,0,0,0,1},{0,1,0,1,0},{0,1,0,1,0},{0,0,1,0,0}},
{{0,1,1,1,0},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,0},{0,1,1,1,1}},
{{1,0,0,0,1},{1,0,0,1,0},{1,0,1,0,0},{1,1,0,0,0},{1,1,0,0,0}}
};

//-------------------------------------------------------------
//-----------------------Player 상수--------------------------

//사용자 입력 키 아스키 코드
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define BULLETLAUNCH VK_SPACE
#define SKILLACTIVE VK_CONTROL
#define QUIT VK_ESCAPE
#define SWAP VK_SHIFT

//플레이어 고유 번호 및 색깔, 무적일 때 색깔
#define PLAYER 4
#define PLAYERCOLOR 11
#define PLAYERUSINGSKILLCOLOR 13
#define PLAYERINVINSIBLEINDICATECOLOR 14

//플레이어 인풋타임 버퍼시간
double PLAYERTIMEBUFFER = 0.04;

//플레이어 인풋타임 시작시간
double PlayerInputTime = 0;

//플레이어 시작 위치
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

#define PLAYERMAXLEVEL 10
int PlayerLevel = 1;	//플레이어 우주선 레벨
int EXP = 0;				// 획득한 경험치

//플레이어 우주선
int PlayerModelIndex;
const char *PlayerModel[3][3] = { {"HH","<HH>","<AHHA>"},{"AA","<AA>","<=AA=>"},{"TT","<TT>","<-TT->"} };

//플레이어 무적상태 및 무적상태 지속시간, 총알 및 적 우주선과 충돌한 시간
#define InvinsibleTime 1
int Invinsible = 0; double CollisionTime = 0;

//플레이어의 라이프게이지
int SelectedLife = 5; int CurrentLife; int *LifeGauge;

//플레이어의 속도
double SelectedSpeed, CurSpeed;

//플레이어 주 무기
int PlayerWeapon = 0;

//플레이어 총알 관리 구조체
typedef struct PlayerBullet {
	int P_BULLET_POS_X, P_BULLET_POS_Y;	//플레이어 총알 위치
	int BulletActivation;									//플레이어 총알 작동 인디케이더
	int BulletDamage;
	char BulletModel;
	int CollisionEnemy;									//플레이어 총알이 enemy하고 충돌할 때 인디케이더
	int CollisionWall;										//플레이어 총알이 wall하고 충돌할때 인디케이더
	int CollisionNpc;										//플레이어 총알이 npc하고 충돌할때 인디케이더
	int inProgress;
}PlayerBullet;

//플레이어 총알 구조체 배열
#define PLAYERBULLET 5
#define BULLETCOUNTLIMIT 100
PlayerBullet PB[BULLETCOUNTLIMIT];

const char PLAYERBULLETMODEL[] = { '!','o','*' };
double P_BULLETLAUNCHTIMEBUFFER = 0.2;
#define P_BULLETTIMEBUFFER 0.03	//플레이어 총알 갱신 버퍼
double P_BulletSpeed = 1.0;					//플레이어 총알 속도

//원형 배열처럼 이용
int P_BULLETCOUNTSTART = 0;					//플레이어 총알 카운트 시작 index
int P_BULLETCOUNTEND = -1;						//플레이어 총알 카운트 종료 index
double P_BulletInputTime = 0.0;
double P_BulletLaunchTime = 0.0;					//Bullet 발사 시간

//---------------------------------------------------------------
//----------------------Enemy 상수----------------------------


double ENEMYTIMEBUFFER = 0.02;					//Enemy Invalidation Buffer Time : Invalidate after 0.02 sec

double EnemyInputTime = 0;							//Enemy Invalidation Time

#define ENEMYMOVEMENTDURATION_ver2 1.5
#define ENEMYMOVEMENTDURATION_ver1 0.3		//When Enemy needs to move stop 0.3 sec and move
double EnemyMovementTiming = 0;				//Enemy Movement start time

int Enemy_Health[3] = { 300, 450, 600 };		//Enemy Health
int StageEnemyHealth;
#define ENEMYSIZE_H 5		//Enemy Height
#define ENEMYSIZE_W 11		//Enemy Width
#define ENEMY 2					//Enemy original number
#define ENEMYDAMAGE 2	//If player collision with enemy get 2 damage
double EnemySpeed = 1.0;	//Enemy Speed


//적 우주선 위치 및 이동방향
//이동방향을 나타내는 상수
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4
#define DIRECTION_LEFTUP 5
#define DIRECTION_LEFTDOWN 7
#define DIRECTION_RIGHTUP 6
#define DIRECTION_RIGHTDOWN 8

#define ENEMY_ORIGIN_POS_X GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - ENEMYSIZE_W / 2
#define ENEMY_ORIGIN_POS_Y GAMEBOARD_ORIGIN_Y + 1
int ENEMY_POS_X = ENEMY_ORIGIN_POS_X;
int ENEMY_POS_Y = ENEMY_ORIGIN_POS_Y;
int direction = 0;
int EnemyIsMoving = 0;

typedef struct Prison {	//Enemy Skill Prison template
	int Prison_W, Prison_H;
	int RD_X, RD_Y, LU_X, LU_Y;
}Prison;
Prison P;	//Prison template P
int EnemySkillPrisonActivation = 0;	//SkillPrison Activation indicator

//적 우주선 모델링
char EnemyModel[ENEMYSIZE_H][ENEMYSIZE_W] = 
{ {'V','^','=','^','^','=','^','^','=','^','V'},
{' ','V','^','-','^','|','^','-','^','V',' '},
{' ',' ','V','-','V','|','V','-','V',' ',' '},
{' ','-','-','V','^','|','^','V','-','-',' '},
{' ',' ',' ',' ',' ','V',' ',' ',' ',' ',' '} };

//-------------------------------------------------------------------
//-------------------------Npc 상수------------------------------

double NPCTIMEBUFFER = 0.02;					//Npc Invalidation Buffer Time : Invalidate after 0.02 sec

double NpcInputTime = 0;							//Npc Invalidation Time

#define NPCDAMAGE 2	//If player collision with npc get 2 damage
#define NPCSIZE_H 2		//Npc Height
#define NPCSIZE_W 5		//Npc Width
#define NPC_COUNT 5	//Npc Count
#define NPCPATTERNCOUNT 3
#define NPC_PATTERNTIME_STAIRS 10.0//Stairs 패턴 지속시간
#define NPC_PATTERNTIME_HEADBUTT 10.0//HeadButt 패턴 지속시간
#define NPC_PATTERNTIME_SWEEPDOWN 10.0//SweepDown 패턴 지속시간

typedef struct Npc {						//Npc 위치 저장 공간 구조체
	int NPC_POS_X, NPC_POS_Y;
	int NpcActivation;
	int CollisionPlayer;
	int CollisionWall;
	int CollisionPbullet;
	int life;
	int cnt;
}Npc;

Npc npc[NPC_COUNT];

int Npc_Health[3] = { 4, 8, 12 };			//Npc Health
double NpcSpeed = 0.3;						//Npc Speed
double NpcPatternStartTime = 0;				//패턴 시작시간
double NpcPatternEndTime = 0;				//패턴 종료시간
double NpcMovementTiming = 0;				//Npc Movement start time

int NpcPatternStart = 0;					//패턴 시작 유무
int NpcPatternTimeEnded = 1;				//패턴 지속시간 종료 유무
int NpcPatternNumber = 0;					//패턴 넘버
int NpcPatternCycle = 0;					//패턴 사이클
int NpcSweepDownChecker = 0;				//SweepDown패턴 체커
int NpcDirection = 0;
int NpcIsMoving = 0;
int NpcKillCount = 0;
int NpcKilledOver = 0;
int NPCCOUNT = 0;							//npc 개수

char NpcModel[NPC_COUNT][NPCSIZE_H][NPCSIZE_W] = {
	{{'-', '=','T', '=', '-'},
	{' ','l', 'V', 'l', ' '}},
	{{'V', '-','-', '-', 'V'},
	{' ','v', 'o', 'v', ' '}},
	{{'-', 'I','U', 'I', '-'},
	{' ','(', 'v', ')', ' '}},
	{{'-', 'w','T', 'w', '-'},
	{' ','!', 'l', '!', ' '}},
	{{'~', 'X',' ', 'X', '~'},
	{' ','Y', 'x', 'Y', ' '}}
};

//-------------------------------------------------------------------
//-------------------------Timer 상수------------------------------

//Timer 함수 이용시 필요한 상수
LARGE_INTEGER ticksPerSec;
LARGE_INTEGER start, end, diff;

//게임을 pause하였는지에 대한 인디케이터
int GamePaused = 0;

//게임 Pause Time
double PausedTime = 0;

//게임 정지시간
double PausingTime = 0;

//게임 전체 진행시간
int TotalSec = 0;

//-------------------------------------------------------------------
//------------------------UI 상수-----------------------------------

//Modified 함수
int Strlen(const char *src) {
	int cnt = 0;
	for (const char *p = src; *p != '-'; p++) cnt++;
	return cnt + 1;
}

//맵의 길이
#define BASEENEMYHEALTHFORUI 40

//무한 모드 사용 시 출력할 시간
int Min = 0, Sec = 0, MiSec = 0;

//--------------------------------------------------------------------
//-----------------------ITEM 상수----------------------------------

//아이템 움직임 버퍼 시간
#define ITEMTIMEBUFFER 0.2
double ItemInputTime = 0;
double ItemCreationLoop = 1;

//아이템 효과 모음집
#define SPEEDINCREASERATE 1.0
#define FLASHDISTANCE 6
int flashCount = 0;

//게임보드내 아이템 출력 여부
int itemFLAG = 0;

// 점멸 확인 용 변수
int flashFLAG = 0;

//아이템 X, Y 좌표
int ITEM_POS_X, ITEM_POS_Y;

//아이템과 플레이어 충돌 감지 변수
int ItemCollisionDetected = 0;

//아이템 번호
int ItemNumber = 0;

//플레이어의 주 스킬, 보조 스킬, 사용 중인 스킬
int CurSkill = 0, SubSkill = 0, UsingSkill = 0;

//스킬 지속시간, 스킬 발동 시작시간
int SkillTime = 3; double SkillActivationTime = 0;

//플레이어의 스킬 셋 string
char Skillstr[] = { "ITEM1" }; char SubSkillstr[] = { "ITEM2" };
char SkillSets[][101] = { "-NONE-", "-SPEED-","-SLOW-", "-INVIN-","-DASH-","-ERASE-" };

//아이템 출력 아이콘 리스트
char itemList[] = { 'S', 'L', 'I', 'D', 'E' };

//-------------------------------------------------------------
//----------------------BULLET 상수--------------------------

#define BULLET 3								//Bullet 고유번호
#define BULLETDAMAGE 1				//Bullet Damage
#define BULLETTIMEBUFFER 0.3		//Bullet 갱신 버퍼 시간

typedef struct Bullet {						//Bullet 위치 저장 공간 구조체
	int BULLET_POS_X, BULLET_POS_Y;
	int BulletActivation;
	int CollisionPlayer;
	int CollisionWall;
	int cnt;
}Bullet;						
Bullet bullet[1000];							//Bullet 구조체 배열

#define STAGEPATTERNCOUNT 6
int PatternStage1[] = { 1, 2, 3, 4, 5, 6 };
int PatternStage2[] = { 2, 3, 4, 6, 7, 8 };
int PatternStage3[] = { 5, 6, 7, 8, 9, 10 };
int PatternStageVisit[] = { 0, 0, 0, 0, 0, 0 };

#define TOTALPATTERNCOUNT 10	//총 패턴 갯수
#define PATTERNDURATION 0.5		//패턴 durationtime
#define PATTERNTIME_SPREAD 12.0//Spread 패턴 지속시간
#define PATTERNTIME_LASER 12.0//Laser 패턴 지속시간
#define PATTERNTIME_3WAY 12.0//3way 패턴 지속시간
#define PATTERNTIME_SPIRAL 6.0 //Spiral 패턴 지속시간
#define PATTERNTIME_GYRO 6.0 //Gyro 패턴 지속시간
#define PATTERNTIME_SHOTGUN 10.0 //Shotgun 패턴 지속시간
#define PATTERNTIME_CIRCLESPREAD 10.0	//원형 Spread 패턴 지속시간
#define PATTERNTIME_CHAOS 10.0 //Spiral 패턴 지속시간
#define PATTERNTIME_METEOR 10.0 //Meteor 패턴 지속시간
#define PATTERNTIME_ROAD 8.0 //Road 패턴 지속시간


double BulletInputTime = 0;				//Bullet 인풋 시작 시간
double BulletPatternStartTime = 0;	//패턴 시작시간
double BulletPatternEndTime = 0;	//패턴 종료시간
int PatternStart = 0;							//패턴 시작 유무
int PatternTimeEnded = 1;				//패턴 지속시간 종료 유무
int PatternNumber = 0;					//패턴 넘버
int PatternCycle = 0;							//패턴 사이클
int BULLETCOUNT = 0;						//총알 개수
double BulletSpeed = 1.0;					//Bullet 속도

char BulletModelPerPattern[TOTALPATTERNCOUNT] = { 'o','v','v','o','o','x','o','o','o','|' };
//---------------------------------------------------------
//----------------------Exp 상수--------------------------

typedef struct EXPList {
	int EXP_POS_X, EXP_POS_Y;
	double ExpCreationTime;
	int ExpActivation;
}EXPList;

#define MAXEXPCREATE 20
EXPList exp[MAXEXPCREATE];
int EXPCOUNTSTART = 0;
int EXPCOUNTEND = -1;

double ExpDurationTime = 5;			//아이템 생성 시간 간격, 확인을 위해 5초 단위로 생성시켰습니다. 

int expFLAG = 0; // 게임 내 아이템 출력 여부
int levelFLAG[] = { 4, 8, 12, 16, 20, 24, 28, 32, 36  }; // 레벨업에 필요한 경험치 양

//----------------------------------------------------------
//------------------WeaponItem 상수---------------------

typedef struct WeaponList {
	int WEAPON_POS_X, WEAPON_POS_Y;
	double WeaponCreationTime;
	int WeaponNumber;
	int WeaponActivation;
}WeaponList;

#define MAXWEAPONCREATE 10
WeaponList weapon[MAXWEAPONCREATE];
int WEAPONCOUNTSTART = 0;
int WEAPONCOUNTEND = -1;

double WeaponDurationTime = 5.0;

const char WeaponItemModel[] = { 'D', 'H', 'S' };	//첫번째는 기본 총(구분을 위해 넣었습니다.)

//-------------------------------------------------------------
//----------------------SCORE 상수--------------------------

int TotalScore = 0;
int StageClearBonusScore = 0;
double ScorePrintDurationTime = 2;

typedef struct ScoreInfo {						//Score 위치 저장 공간 구조체
	char name[20];
	int score;
}ScoreInfo;
ScoreInfo PlayerInfo[10];

#endif //!VARIABLESETS_H