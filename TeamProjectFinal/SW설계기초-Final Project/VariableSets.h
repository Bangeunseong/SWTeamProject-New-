#pragma once
#include <Windows.h>
#ifndef VARIABLESETS_H
#define VARIABLESETS_H
//-------------------------------------------
//-------------Console â ���-------------

//�ܼ� â ROW ����
#define CONSOLE_ROW 45

//�ܼ� â COLUMN ����
#define CONSOLE_COLUMN 108

//-------------------------------------------
//-------------BackGround ���------------

//���ӿ��� ����
#define BACKGROUND_ROW 90
#define BACKGROUND_COLUMN 43
#define BACKGROUND_ORIGIN_X 8
#define BACKGROUND_ORIGIN_Y 1
#define GAMEBOARD_ROW 90
#define GAMEBOARD_COLUMN 40
#define GAMEBOARD_ORIGIN_X 8
#define GAMEBOARD_ORIGIN_Y 4
#define WALL 1

//����ȭ���� �̻� ��
int UniBoard[GAMEBOARD_COLUMN + 1][GAMEBOARD_ROW + 2];

//���� ��Ʈ�� ����
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
//--------------StartMenu ���-------------

#define MODESELECTIONBOX_ROW 18 //���� ��� ���ùڽ� ���� ����
#define MODESELECTIONBOX_COLUMN 3 // ���� ��� ���ùڽ� ���� ����
int ModeSelectionBox_Origin_X = BACKGROUND_ORIGIN_X + 14; //���� ��� ���� �ڽ� �ʱ� X��ǥ
int ModeSelectionBox_Origin_Y = BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 6; //���� ��� ���� �ڽ� �ʱ� Y��ǥ

//���� ���
int GameMode = 0;

//-----------------------------------------------------------
//-------------CharacterSelectionMenu ���--------------

//ĳ���� �ڽ� Dimension
#define CHARACTERBOX_ROW 28
#define CHARACTERBOX_COLUMN 20
#define CHARACTERBOX_ORIGIN_X 6
#define CHARACTERBOX_ORIGIN_Y 12

//-------------------------------------------
//------------StageMenu ���-------------

//�������� ��ȣ
int StageNumber = 1;

//���� ���������� �Ѿ �� Duration time
#define STAGEDURATIONTIME 2.0


#define OPTIONSELECTIONBOX_ROW 18 //���� ��� ���ùڽ� ���� ����
#define OPTIONSELECTIONBOX_COLUMN 3 // ���� ��� ���ùڽ� ���� ����
int OptionSelectionBox_Origin_X = BACKGROUND_ORIGIN_X + 22; //���� ��� ���� �ڽ� �ʱ� X��ǥ
int OptionSelectionBox_Origin_Y = BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 6; //���� ��� ���� �ڽ� �ʱ� Y��ǥ

//Game Over�� ��� �ΰ�
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
//-----------------------Player ���--------------------------

//����� �Է� Ű �ƽ�Ű �ڵ�
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define BULLETLAUNCH VK_SPACE
#define SKILLACTIVE VK_CONTROL
#define QUIT VK_ESCAPE
#define SWAP VK_SHIFT

//�÷��̾� ���� ��ȣ �� ����, ������ �� ����
#define PLAYER 4
#define PLAYERCOLOR 11
#define PLAYERUSINGSKILLCOLOR 13
#define PLAYERINVINSIBLEINDICATECOLOR 14

//�÷��̾� ��ǲŸ�� ���۽ð�
double PLAYERTIMEBUFFER = 0.04;

//�÷��̾� ��ǲŸ�� ���۽ð�
double PlayerInputTime = 0;

//�÷��̾� ���� ��ġ
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

#define PLAYERMAXLEVEL 10
int PlayerLevel = 1;	//�÷��̾� ���ּ� ����
int EXP = 0;				// ȹ���� ����ġ

//�÷��̾� ���ּ�
int PlayerModelIndex;
const char *PlayerModel[3][3] = { {"HH","<HH>","<AHHA>"},{"AA","<AA>","<=AA=>"},{"TT","<TT>","<-TT->"} };

//�÷��̾� �������� �� �������� ���ӽð�, �Ѿ� �� �� ���ּ��� �浹�� �ð�
#define InvinsibleTime 1
int Invinsible = 0; double CollisionTime = 0;

//�÷��̾��� ������������
int SelectedLife = 5; int CurrentLife; int *LifeGauge;

//�÷��̾��� ��ġ
int PlayerPos = 0;

//�÷��̾��� �ӵ�
double SelectedSpeed, CurSpeed;

//�÷��̾� �Ѿ� ���� ����ü
typedef struct PlayerBullet {
	int P_BULLET_POS_X, P_BULLET_POS_Y;	//�÷��̾� �Ѿ� ��ġ
	int BulletActivation;									//�÷��̾� �Ѿ� �۵� �ε����̴�
	int CollisionEnemy;									//�÷��̾� �Ѿ��� enemy�ϰ� �浹�� �� �ε����̴�
	int CollisionWall;										//�÷��̾� �Ѿ��� wall�ϰ� �浹�Ҷ� �ε����̴�
	int inProgress;
}PlayerBullet;

//�÷��̾� �Ѿ� ����ü �迭
#define BULLETCOUNTLIMIT 100
PlayerBullet PB[BULLETCOUNTLIMIT];

int P_BULLETDAMAGE = 1;
#define PLAYERBULLETMODEL '!'
#define P_BULLETLAUNCHTIMEBUFFER 0.2
#define P_BULLETTIMEBUFFER 0.03	//�÷��̾� �Ѿ� ���� ����
#define P_BulletSpeed 1.0					//�÷��̾� �Ѿ� �ӵ�

//���� �迭ó�� �̿�
int P_BULLETCOUNTSTART = 0;					//�÷��̾� �Ѿ� ī��Ʈ ���� index
int P_BULLETCOUNTEND = -1;						//�÷��̾� �Ѿ� ī��Ʈ ���� index
double P_BulletInputTime = 0.0;
double P_BulletLaunchTime = 0.0;					//Bullet �߻� �ð�

//---------------------------------------------------------------
//----------------------Enemy ���----------------------------


double ENEMYTIMEBUFFER = 0.02;					//Enemy Invalidation Buffer Time : Invalidate after 0.02 sec

double EnemyInputTime = 0;							//Enemy Invalidation Time

#define ENEMYMOVEMENTDURATION_ver2 1.5
#define ENEMYMOVEMENTDURATION_ver1 0.3		//When Enemy needs to move stop 0.3 sec and move
double EnemyMovementTiming = 0;				//Enemy Movement start time

int Enemy_Health[3] = { 280, 360, 440 };		//Enemy Health
int StageEnemyHealth;
#define ENEMYSIZE_H 5		//Enemy Height
#define ENEMYSIZE_W 11		//Enemy Width
#define ENEMY 2					//Enemy original number
#define ENEMYDAMAGE 2	//If player collision with enemy get 2 damage
double EnemySpeed = 1.0;	//Enemy Speed


//�� ���ּ� ��ġ �� �̵�����
//�̵������� ��Ÿ���� ���
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

//�� ���ּ� �𵨸�
char EnemyModel[ENEMYSIZE_H][ENEMYSIZE_W] = 
{ {'V','^','=','^','^','=','^','^','=','^','V'},
{' ','V','^','-','^','|','^','-','^','V',' '},
{' ',' ','V','-','V','|','V','-','V',' ',' '},
{' ','-','-','V','^','|','^','V','-','-',' '},
{' ',' ',' ',' ',' ','V',' ',' ',' ',' ',' '} };
//-------------------------------------------------------------------
//-------------------------Timer ���------------------------------

//Timer �Լ� �̿�� �ʿ��� ���
LARGE_INTEGER ticksPerSec;
LARGE_INTEGER start, end, diff;

//������ pause�Ͽ������� ���� �ε�������
int GamePaused = 0;

//���� Pause Time
double PausedTime = 0;

//���� �����ð�
double PausingTime = 0;

//���� ��ü ����ð�
int TotalSec = 0;

//-------------------------------------------------------------------
//------------------------UI ���-----------------------------------

//Modified �Լ�
int Strlen(const char *src) {
	int cnt = 0;
	for (const char *p = src; *p != '-'; p++) cnt++;
	return cnt + 1;
}

//���� ����
#define BASEENEMYHEALTHFORUI 40

//���� ��� ��� �� ����� �ð�
int Min = 0, Sec = 0, MiSec = 0;

//--------------------------------------------------------------------
//-----------------------ITEM ���----------------------------------

//������ ������ ���� �ð�
#define ITEMTIMEBUFFER 0.2
double ItemInputTime = 0;
double ItemCreationLoop = 1;

//������ ȿ�� ������
#define SPEEDINCREASERATE 1.0
#define FLASHDISTANCE 6
int flashCount = 0;

//���Ӻ��峻 ������ ��� ����
int itemFLAG = 0;

// ���� Ȯ�� �� ����
int flashFLAG = 0;

//������ X, Y ��ǥ
int ITEM_POS_X, ITEM_POS_Y;

//�����۰� �÷��̾� �浹 ���� ����
int ItemCollisionDetected = 0;

int ItemNumber = 0;

//�÷��̾��� �� ��ų, ���� ��ų, ��� ���� ��ų
int CurSkill = 0, SubSkill = 0, UsingSkill = 0;

//��ų ���ӽð�, ��ų �ߵ� ���۽ð�
int SkillTime = 3; double SkillActivationTime = 0;

//�÷��̾��� ��ų �� string
char Skillstr[] = { "ITEM1" }; char SubSkillstr[] = { "ITEM2" };
char SkillSets[][101] = { "-NONE-", "-SPEED-","-SLOW-", "-INVIN-","-DASH-","-ERASE-" };

//������ ��� ������ ����Ʈ
char itemList[] = { 'S', 'L', 'I', 'D', 'E' };

//-------------------------------------------------------------
//----------------------BULLET ���--------------------------

#define BULLET 3								//Bullet ������ȣ
#define BULLETDAMAGE 1				//Bullet Damage
#define BULLETTIMEBUFFER 0.3		//Bullet ���� ���� �ð�

typedef struct Bullet {						//Bullet ��ġ ���� ���� ����ü
	int BULLET_POS_X, BULLET_POS_Y;
	int BulletActivation;
	int CollisionPlayer;
	int CollisionWall;
	int cnt;
}Bullet;						
Bullet bullet[1000];							//Bullet ����ü �迭

#define STAGEPATTERNCOUNT 6
int PatternStage1[] = { 1, 2, 3, 4, 5, 6 };
int PatternStage2[] = { 2, 3, 4, 5, 6, 7 };
int PatternStage3[] = { 5, 6, 7, 8, 9, 10 };
int PatternStageVisit[] = { 0, 0, 0, 0, 0, 0 };

#define TOTALPATTERNCOUNT 10	//�� ���� ����
#define PATTERNDURATION 0.5		//���� durationtime
#define PATTERNTIME_SPREAD 12.0//Spread ���� ���ӽð�
#define PATTERNTIME_LASER 12.0//Laser ���� ���ӽð�
#define PATTERNTIME_3WAY 12.0//3way ���� ���ӽð�
#define PATTERNTIME_SPIRAL 6.0 //Spiral ���� ���ӽð�
#define PATTERNTIME_GYRO 6.0 //Gyro ���� ���ӽð�
#define PATTERNTIME_SHOTGUN 10.0 //Shotgun ���� ���ӽð�
#define PATTERNTIME_CIRCLESPREAD 10.0	//���� Spread ���� ���ӽð�
#define PATTERNTIME_CHAOS 10.0 //Spiral ���� ���ӽð�
#define PATTERNTIME_METEOR 10.0 //Meteor ���� ���ӽð�
#define PATTERNTIME_ROAD 8.0 //Road ���� ���ӽð�


double BulletInputTime = 0;				//Bullet ��ǲ ���� �ð�
double BulletPatternStartTime = 0;	//���� ���۽ð�
double BulletPatternEndTime = 0;	//���� ����ð�
int PatternStart = 0;							//���� ���� ����
int PatternTimeEnded = 1;				//���� ���ӽð� ���� ����
int PatternNumber = 0;					//���� �ѹ�
int PatternCycle = 0;							//���� ����Ŭ
int BULLETCOUNT = 0;						//�Ѿ� ����
double BulletSpeed = 1.0;					//Bullet �ӵ�

char BulletModelPerPattern[TOTALPATTERNCOUNT] = { 'o','v','v','o','o','x','o','o','o','|' };
//---------------------------------------------------------
//----------------------Exp ���--------------------------

//������ ������ ���� �ð�
#define EXPTIMEBUFFER 0.2
double ExpInputTime = 0;
int ExpCreateTime = 10;			//������ ���� �ð� ����, Ȯ���� ���� 5�� ������ �������׽��ϴ�. 
double ExpCreationLoop = 1;		//������ ���� ����

int expFLAG = 0; // ���� �� ������ ��� ����
int levelFLAG[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18 }; // �������� �ʿ��� ����ġ ��

int EXP_POS_X, EXP_POS_Y;

#endif //!VARIABLESETS_H