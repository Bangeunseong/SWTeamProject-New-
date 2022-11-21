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

//���������� �÷��� �ð�
int StageTime[] = { 60,90,120 };

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
#define SPACE 0x20
#define QUIT VK_ESCAPE

//�÷��̾� ���� ��ȣ �� ����, ������ �� ����
#define PLAYER 4
#define PLAYERCOLOR 3
#define PLAYERUSINGSKILLCOLOR 13
#define PLAYERINVINSIBLEINDICATECOLOR 6

//�÷��̾� ��ǲŸ�� ���۽ð�
double PLAYERTIMEBUFFER = 0.04;

//�÷��̾� ��ǲŸ�� ���۽ð�
double PlayerInputTime = 0;

//�÷��̾� ���� ��ġ
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

//�÷��̾� ���ּ�
char PlayerModel[6];
char PlayerUniModel[6] = { PLAYER,PLAYER,PLAYER,PLAYER,PLAYER,PLAYER };

//�÷��̾� �������� �� �������� ���ӽð�, �Ѿ� �� �� ���ּ��� �浹�� �ð�
#define InvinsibleTime 1
int Invinsible = 0; double CollisionTime = 0;

//�÷��̾��� ������������
int SelectedLife = 5; int CurrentLife; int *LifeGauge;

//�÷��̾��� ��ġ
int PlayerPos = 0;

//�÷��̾��� �ӵ�
double SelectedSpeed, CurSpeed;

//---------------------------------------------------------------
//----------------------Enemy ���----------------------------

//�� NPC ��ǲŸ�� ���� �ð�
double ENEMYTIMEBUFFER = 0.02;

//�� NPC ��ǲŸ�� ���۽ð�
double EnemyInputTime = 0;

#define ENEMYMOVEMENTDURATION 0.3
double EnemyMovementTiming = 0;

//�� ���ּ� �� �Ѿ�
#define ENEMY 2
#define ENEMYDAMAGE 2
#define ENEMYBULLET 3
double EnemySpeed = 1.0;


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

#define ENEMY_ORIGIN_POS_X GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3
#define ENEMY_ORIGIN_POS_Y GAMEBOARD_ORIGIN_Y + 1
int ENEMY_POS_X = ENEMY_ORIGIN_POS_X;
int ENEMY_POS_Y = ENEMY_ORIGIN_POS_Y;
int direction = 0;
int EnemyIsMoving = 0;

//�� NPC skillType1-[Prison] ���ú��� - �߰�
typedef struct Prison {
	int Prison_W, Prison_H;
	int RD_X, RD_Y, LU_X, LU_Y;
}Prison;
Prison P;
int EnemySkillPrisonActivation = 0;

//�� ���ּ� �𵨸�
char EnemyModel[3][5] = { {' ','^','V','^',' '},{'<','<','O','>','>'},{' ','^','V','^',' '} };
char EnemyUniModel[3][5] = { {0,ENEMY,ENEMY,ENEMY,0},{ENEMY,ENEMY,ENEMY,ENEMY,ENEMY},{0,ENEMY,ENEMY,ENEMY,0} };

//-------------------------------------------------------------------
//-------------------------Timer ���------------------------------

//Timer �Լ� �̿�� �ʿ��� ���
LARGE_INTEGER ticksPerSec;
LARGE_INTEGER start, end, diff;

//�� ������ ����
double CurrentTime = 1;

//������ pause�Ͽ������� ���� �ε�������
int GamePaused = 0;

//���� Pause Time
double PausedTime = 0;

//���� �����ð�
double PausingTime = 0;

//-------------------------------------------------------------------
//------------------------UI ���-----------------------------------

//Modified �Լ�
int Strlen(const char *src) {
	int cnt = 0;
	for (const char *p = src; *p != '-'; p++) cnt++;
	return cnt + 1;
}

//���� ����
#define MAPLENGTH 15

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
char Skillstr[] = { "MainSkill " }; char SubSkillstr[] = { "SubSkill  " };
char SkillSets[][101] = { "-NONE-", "-SPEEDUP-","-SLOW-", "-INVINSIBLE-","-DASH-","-ERASEBULLET-" };

//������ ��� ������ ����Ʈ
char itemList[] = { 'S', 'L', 'I', 'D', 'E' };

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

#define TOTALPATTERNCOUNT 10	//�� ���� ����
#define PATTERNDURATION 1.5		//���� durationtime
#define PATTERNTIME_SPREAD 10.0//Spread ���� ���ӽð�
#define PATTERNTIME_LASER 12.0//Laser ���� ���ӽð�
#define PATTERNTIME_3WAY 10.0//3way ���� ���ӽð�
#define PATTERNTIME_CIRCLESPREAD 10.0	//���� Spread ���� ���ӽð�
#define PATTERNTIME_CHAOS 15.0 //Spiral ���� ���ӽð�
#define PATTERNTIME_GYRO 10.0 //Gyro ���� ���ӽð�
#define PATTERNTIME_SHOTGUN 10.0 //Shotgun ���� ���ӽð�
#define PATTERNTIME_ROAD 10.0 //Road ���� ���ӽð�
#define PATTERNTIME_METEOR 10.0 //Meteor ���� ���ӽð�
#define PATTERNTIME_SPIRAL 10.0 //Spiral ���� ���ӽð�

double BulletInputTime = 0;				//Bullet ��ǲ ���� �ð�
double BulletPatternStartTime = 0;	//���� ���۽ð�
double BulletPatternEndTime = 0;	//���� ����ð�
int PatternStart = 0;							//���� ���� ����
int PatternTimeEnded = 1;				//���� ���ӽð� ���� ����
int PatternNumber = 0;					//���� �ѹ�
int PatternCycle = 0;							//���� ����Ŭ
int BULLETCOUNT = 0;						//�Ѿ� ����
double BulletSpeed = 1.0;					//Bullet �ӵ�

char BulletModelPerPattern[TOTALPATTERNCOUNT] = { 'o','v','o','v','o','o','x','I','o','o' };

#endif //!VARIABLESETS_H