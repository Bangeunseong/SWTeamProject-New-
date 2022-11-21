#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//Bullet Time Buffer
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime - PausingTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
}

//���� ���� �ѹ� ����
void SetRandomPatternNumber(int max) { PatternNumber = rand() % max + 1; }

void HideBullet(int bulletnumber) {
	SetCurrentCursorPos(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y);
	UniBoard[bullet[bulletnumber].BULLET_POS_Y - GAMEBOARD_ORIGIN_Y][bullet[bulletnumber].BULLET_POS_X - GAMEBOARD_ORIGIN_X] = 0;
	printf(" ");
}

void ShowBullet(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) bullet[bulletnumber].BulletActivation = 1;
	SetCurrentCursorPos(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y);
	UniBoard[bullet[bulletnumber].BULLET_POS_Y - GAMEBOARD_ORIGIN_Y][bullet[bulletnumber].BULLET_POS_X - GAMEBOARD_ORIGIN_X] = BULLET;
	printf("%c", BulletModelPerPattern[PatternNumber - 1]);
}

void ClearBulletPosition() {
	for (int i = 0; i < BULLETCOUNT; i++) {
		HideBullet(i);
		bullet[i].cnt = 0;
		bullet[i].BULLET_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		bullet[i].BULLET_POS_Y = GAMEBOARD_ORIGIN_Y + 5;
		bullet[i].BulletActivation = bullet[i].CollisionPlayer = bullet[i].CollisionWall = 0;
	}
	PatternStart = 0;
	PatternCycle = 0;
	PatternNumber = 0;
	PatternTimeEnded = 1;
	BULLETCOUNT = 0;
	BulletSpeed = 1.0;
}

void BulletPostionRenewal(int bulletnumber) {
	if (PatternNumber == 1) {
		bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2;
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 3;
	}
	else if (PatternNumber == 2 || PatternNumber == 4 || PatternNumber == 7) {
		if (bulletnumber % 3 == 0) { bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 1; }
		else if (bulletnumber % 3 == 1) { bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2; }
		else { bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 3; }
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 3;
	}
	else if (PatternNumber == 3 || PatternNumber == 5 || PatternNumber == 10) {
		bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2;
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 1;
	}
	else if (PatternNumber == 6) {
		bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2;
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 1;
	}
	else if (PatternNumber == 8) {
		bullet[bulletnumber].BULLET_POS_X = GAMEBOARD_ORIGIN_X + 1 + (bulletnumber % (GAMEBOARD_ROW - 1));
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 1 + ((bulletnumber % 20));
	}
	else if (PatternNumber == 9) {
		bullet[bulletnumber].BULLET_POS_X = GAMEBOARD_ORIGIN_X + 1 + (rand() % (GAMEBOARD_ROW - 1));
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 1;
	}
}

int DetectCollision_BulletwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == WALL)
		return 1;
	return 0;
}

int DetectCollision_BulletwithPlayer(int x, int y) {
	if (y == PLAYER_POS_Y) {
		for (int i = 0; i < 6; i++) {
			if (y == PLAYER_POS_Y && x == PLAYER_POS_X + i) return 1;
		}
	}
	return 0;
}

//-----------------------Bullet Position Functions-------------------------
//Move bullet to North
int MoveBullet_N(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y - 1)) bullet[bulletnumber].BULLET_POS_Y--;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to NorthWest
int MoveBullet_NW(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y - 1)) { bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y--; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to NorthEast
int MoveBullet_NE(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y - 1)) { bullet[bulletnumber].BULLET_POS_X += 2; bullet[bulletnumber].BULLET_POS_Y--; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to West
int MoveBullet_W(int bulletnumber) {
	//--------------------�Ѿ� �۵� ���� �˻��Լ�----------------------
	if (!bullet[bulletnumber].BulletActivation) return 0;	//�Ѿ��� �۵��ϰ� ���� �ʴٸ� �׳� 0�� ��ȯ
	//--------------------------------------------------------------------

	HideBullet(bulletnumber);		//�Ѿ��� �����
	//--------------------�浹 ���� �Լ�-------------------------
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) {		//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
		bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0;
	}
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y)) //���� �ε����� �ʾ����� X��ǥ - 2
		bullet[bulletnumber].BULLET_POS_X -= 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }	//�ε����ٸ� �Ѿ� ��Ȱ��ȭ, ���� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	//--------------------------------------------------------------

	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South West
int MoveBullet_SW(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y + 1)) {
		bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South
int MoveBullet_S(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y + 1)) bullet[bulletnumber].BULLET_POS_Y++;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to SouthEast
int MoveBullet_SE(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y + 1)) {
		bullet[bulletnumber].BULLET_POS_X += 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to East
int MoveBullet_E(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X += 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}

//Move bullet to x, y coordinate
int MoveBullet_Spiral(int bulletnumber, int x, int y) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + x, bullet[bulletnumber].BULLET_POS_Y - y)) { bullet[bulletnumber].BULLET_POS_X += x; bullet[bulletnumber].BULLET_POS_Y -= y; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}

//----------------------------------------------------------------------------
//---------------------Bullet LaunchTime Set Function----------------------
//When bullet launches record time and set patternnumber, start pattern
void BulletLaunchTime() {
	if (!PatternStart) {	//������ ���۵��� �ʾ��� ���
		double CheckedTime = TimeCheckerEnd() - PausingTime;
		if (CheckedTime > BulletPatternEndTime + PATTERNDURATION) {		//üũ�� �ð��� ���� ����ð� + durationtime���� ũ�� �۵�
			SetRandomPatternNumber(TOTALPATTERNCOUNT);		//���� �ѹ� ����(����)
			if (PatternNumber == 1 || PatternNumber == 10) BulletSpeed = 1.0;		//���� �ѹ� 1���϶� bulletspeed
			else if (PatternNumber == 3 || PatternNumber == 5) BulletSpeed = 1.5;		//���� �ѹ� 3, 5, 10�϶� 1.5 bulletspeed
			else if (PatternNumber == 2 || PatternNumber == 4) BulletSpeed = 8.0;		//���� �ѹ��� 2, 4�϶� 8.0 bulletspeed
			else if (PatternNumber == 6) BulletSpeed = 3.0;		//���� �ѹ��� 6�϶� 3.0 bulletspeed
			else if (PatternNumber == 7 || PatternNumber == 8) BulletSpeed = 5.0;		//���� �ѹ��� 7, 8�϶� 5.0 bulletspeed
			else if (PatternNumber == 9) BulletSpeed = 4.0;		//���� �ѹ��� 9�϶� 4.0 bulletspeed
			PatternStart = EnemyIsMoving = 1; PatternTimeEnded = 0; EnemyMovementTiming = BulletPatternStartTime = CheckedTime;	//���� ���� �ε������� 1�� ����, ���� ���۽ð� ����, Enemy�� �����̰� �ִٴ� �ε������� 1�� ����
		}
	}
	else return;
}

//------------------------------------------------------------------------
//---------------------Bullet Pattern Functions--------------------------

//Bullet Pattern Spread_Note : �¿�� ������(������ �ӵ��� �������� ������)
int BulletPattern_Spread() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_SPREAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) BULLETCOUNT = (++PatternCycle) * 3; //���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
	else PatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }	//���� �Ѿ��� ������ ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� �Ѿ� ���
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;	//�Ѿ��� ���������� �̵�
		case 1: flag += MoveBullet_S(i); break;		//�Ѿ��� �������� �̵�
		case 2: flag += MoveBullet_SW(i); break;	//�Ѿ��� ���������� �̵�
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }	//���� ��� �Ѿ˵��� �����ǿ��� ������� ��� --���� ����ð� ����--, 1�� ��ȯ
	return 0;
}

//Bullet Pattern Laser_Note : �¿�� ������(������ ���� ���� �ʿ�)
int BulletPattern_Laser() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if ((CheckedTime < PATTERNTIME_LASER + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)) BULLETCOUNT = (++PatternCycle) * 3;//���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
	else PatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }
		switch (i % 3) {
		case 0: flag += MoveBullet_S(i); break;
		case 1: flag += MoveBullet_S(i); break;
		case 2: flag += MoveBullet_S(i); break;
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Bullet Pattern Circle Spread_Note : ���ӿ��� ��ü�� ������(��ü�� ������ �� Enemy �ӵ��� ����� �����ʿ� ����, �ٽ� �������� ���ƿ;� ��, �ᱹ ������ ���� ���� �ʿ�)
int BulletPattern_CircleSpread() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if ((CheckedTime < PATTERNTIME_CIRCLESPREAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)) { //���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
		if ((int)(CheckedTime - BulletPatternStartTime) % 2 == 0)
			BULLETCOUNT = (++PatternCycle) * 8;
	}
	else PatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 8 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }
		switch (i % 8) {
		case 0: flag += MoveBullet_N(i); break;
		case 1: flag += MoveBullet_NW(i); break;
		case 2: flag += MoveBullet_NE(i); break;
		case 3: flag += MoveBullet_E(i); break;
		case 4: flag += MoveBullet_W(i); break;
		case 5: flag += MoveBullet_SW(i); break;
		case 6: flag += MoveBullet_SE(i); break;
		case 7: flag += MoveBullet_S(i); break;
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Bullet Pattern 3way
int BulletPattern_3way() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_3WAY + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) BULLETCOUNT = (++PatternCycle) * 3; //���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
	else PatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }	//���� �Ѿ��� ������ ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� �Ѿ� ���
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;	//�Ѿ��� ���������� �̵�
		case 1: flag += MoveBullet_S(i); break;		//�Ѿ��� �������� �̵�
		case 2: flag += MoveBullet_SW(i); break;	//�Ѿ��� ���������� �̵�
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }	//���� ��� �Ѿ˵��� �����ǿ��� ������� ���, �׸��� Enemy�� ���ڸ��� ���ƿ��� �� --���� ����ð� ����--, 1�� ��ȯ
	return 0;
}

//BulletPattern_Chaos
int BulletPattern_Chaos() {		//�̰͵� ���������� Enemy Movement Pattern �ʿ�
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_CHAOS + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) { //���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
		if ((int)(CheckedTime - BulletPatternStartTime) % 2 == 0)
			++PatternCycle;
	}
	else PatternTimeEnded = 1;
	for (int i = 0; i < PatternCycle * 8; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); BULLETCOUNT++; }
		switch (i % 8) {
		case 0: 
			if((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_N(i);
			else flag += MoveBullet_NW(i);
			break;
		case 1: 
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_NW(i);
			else flag += MoveBullet_W(i);
			break;
		case 2: 
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_W(i);
			else flag += MoveBullet_SW(i);
			break;
		case 3: 
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_SW(i);
			else flag += MoveBullet_S(i);
			break;
		case 4: 
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_S(i);
			else flag += MoveBullet_SE(i);
			break;
		case 5: 
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_SE(i);
			else flag += MoveBullet_E(i);
			break; 
		case 6: 
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_E(i);
			else flag += MoveBullet_NE(i);
			break;
		case 7:
			if ((BULLETCOUNT / 8) % 2 == 0) flag += MoveBullet_NE(i);
			else flag += MoveBullet_N(i);
			break;
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//BulletPattern_Spiral
int BulletPattern_Spiral() {		//ȸ�� ���� �ﰢ�Լ��� ����� �� ������ �ϳ��� ��� �� ���� ����� ���� �� �����ϴ�. �ϳ��� �� ������ϴ�.
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_SPIRAL + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) { if (ENEMY_POS_Y == GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - 1) ++PatternCycle; }
	else PatternTimeEnded = 1;
	for (int i = 0; i < PatternCycle * 8; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].cnt = 0; bullet[i].BulletActivation = 1; ShowBullet(i); }
		switch (i % 8) {
		case 0:
			if (bullet[i].cnt == 0) { flag += MoveBullet_N(i); bullet[i].cnt++; }
			else if (bullet[i].cnt == 1) { flag += MoveBullet_Spiral(i, 2, 2); }
			else if (bullet[i].cnt == 2) { flag += MoveBullet_Spiral(i, 3, 2); }
			else if (bullet[i].cnt == 3) { flag += MoveBullet_Spiral(i, 3, 1); }
			else if (bullet[i].cnt == 4) { flag += MoveBullet_Spiral(i, 5, 1); }
			else if (bullet[i].cnt == 5) { flag += MoveBullet_Spiral(i, 7, 1); }
			else if (bullet[i].cnt == 6) { flag += MoveBullet_Spiral(i, 6, 0); }
			else if (bullet[i].cnt == 7) { flag += MoveBullet_Spiral(i, 5, -1); }
			else if (bullet[i].cnt == 8) { flag += MoveBullet_Spiral(i, 3, -1); }
			else if (bullet[i].cnt == 9) { flag += MoveBullet_Spiral(i, 4, -2); }
			else if (bullet[i].cnt == 10) { flag += MoveBullet_Spiral(i, 4, -3); }
			else if (bullet[i].cnt == 11) { flag += MoveBullet_Spiral(i, 1, -3); }
			break;
		case 1:
			if (bullet[i].cnt == 0) { flag += MoveBullet_S(i); }
			else if (bullet[i].cnt == 1) { flag += MoveBullet_Spiral(i, -2, -2); }
			else if (bullet[i].cnt == 2) { flag += MoveBullet_Spiral(i, -3, -2); }
			else if (bullet[i].cnt == 3) { flag += MoveBullet_Spiral(i, -3, -1); }
			else if (bullet[i].cnt == 4) { flag += MoveBullet_Spiral(i, -5, -1); }
			else if (bullet[i].cnt == 5) { flag += MoveBullet_Spiral(i, -7, -1); }
			else if (bullet[i].cnt == 6) { flag += MoveBullet_Spiral(i, -6, 0); }
			else if (bullet[i].cnt == 7) { flag += MoveBullet_Spiral(i, -5, 1); }
			else if (bullet[i].cnt == 8) { flag += MoveBullet_Spiral(i, -3, 1); }
			else if (bullet[i].cnt == 9) { flag += MoveBullet_Spiral(i, -4, 2); }
			else if (bullet[i].cnt == 10) { flag += MoveBullet_Spiral(i, -4, 2); }
			else if (bullet[i].cnt == 11) { flag += MoveBullet_Spiral(i, -1, 3); }
			break;
		case 2:
			if (bullet[i].cnt == 0) { flag += MoveBullet_W(i); }
			else if (bullet[i].cnt == 1) { flag += MoveBullet_Spiral(i, -4, 1); }
			else if (bullet[i].cnt == 2) { flag += MoveBullet_Spiral(i, -4, 1); }
			else if (bullet[i].cnt == 3) { flag += MoveBullet_Spiral(i, -5, 2); }
			else if (bullet[i].cnt == 4) { flag += MoveBullet_Spiral(i, -3, 3); }
			else if (bullet[i].cnt == 5) { flag += MoveBullet_Spiral(i, -2, 3); }
			else if (bullet[i].cnt == 6) {flag += MoveBullet_Spiral(i, 0, 3);}
			else if (bullet[i].cnt == 7) {flag += MoveBullet_Spiral(i, 3, 3);}
			else if (bullet[i].cnt == 8) {flag += MoveBullet_Spiral(i, 4, 2);}
			else if (bullet[i].cnt == 9) {flag += MoveBullet_Spiral(i, 6, 1);}
			break;
		case 3:
			if (bullet[i].cnt == 0) {flag += MoveBullet_E(i);}
			else if (bullet[i].cnt == 1) {flag += MoveBullet_Spiral(i, 4, -1);}
			else if (bullet[i].cnt == 2) {flag += MoveBullet_Spiral(i, 4, -1);}
			else if (bullet[i].cnt == 3) {flag += MoveBullet_Spiral(i, 5, -2);}
			else if (bullet[i].cnt == 4) {flag += MoveBullet_Spiral(i, 3, -3);}
			else if (bullet[i].cnt == 5) { flag += MoveBullet_Spiral(i, 2, -3); }
			else if (bullet[i].cnt == 6) {	flag += MoveBullet_Spiral(i, 0, -3);}
			else if (bullet[i].cnt == 7) {flag += MoveBullet_Spiral(i, -3, -3);}
			else if (bullet[i].cnt == 8) {	flag += MoveBullet_Spiral(i, -4, -2);}
			else if (bullet[i].cnt == 9) {flag += MoveBullet_Spiral(i, -6, -1);}
			break;
		case 4:
			if (bullet[i].cnt == 0) {flag += MoveBullet_NE(i);}
			else if (bullet[i].cnt == 1) {flag += MoveBullet_Spiral(i, 4, 1);}
			else if (bullet[i].cnt == 2) {flag += MoveBullet_Spiral(i, 5, 0);}
			else if (bullet[i].cnt == 3) { flag += MoveBullet_Spiral(i, 6, -1); }
			else if (bullet[i].cnt == 4) {flag += MoveBullet_Spiral(i, 5, -1);}
			else if (bullet[i].cnt == 5) {flag += MoveBullet_Spiral(i, 6, -2);}
			else if (bullet[i].cnt == 6) {	flag += MoveBullet_Spiral(i, 4, -3);}
			else if (bullet[i].cnt == 7) {flag += MoveBullet_Spiral(i, 3, -3);}
			else if (bullet[i].cnt == 8) {flag += MoveBullet_Spiral(i, 1, -4);}
			else if (bullet[i].cnt == 9) {flag += MoveBullet_Spiral(i, -1, -3);}
			else if (bullet[i].cnt == 10) { flag += MoveBullet_Spiral(i, -2, -3); }
			break;
		case 5:
			if (bullet[i].cnt == 0) {flag += MoveBullet_SW(i);}
			else if (bullet[i].cnt == 1) { flag += MoveBullet_Spiral(i, -4, -1); }
			else if (bullet[i].cnt == 2) {flag += MoveBullet_Spiral(i, -5, 0);}
			else if (bullet[i].cnt == 3) {flag += MoveBullet_Spiral(i, -6, 1);}
			else if (bullet[i].cnt == 4) {flag += MoveBullet_Spiral(i, -5, 1);}
			else if (bullet[i].cnt == 5) {flag += MoveBullet_Spiral(i, -6, 2);}
			else if (bullet[i].cnt == 6) {flag += MoveBullet_Spiral(i, -4, 3);}
			else if (bullet[i].cnt == 7) {	flag += MoveBullet_Spiral(i, -3, 3);}
			else if (bullet[i].cnt == 8) {flag += MoveBullet_Spiral(i, -1, 4);}
			else if (bullet[i].cnt == 9) {flag += MoveBullet_Spiral(i, 1, 3);}
			else if (bullet[i].cnt == 10) {flag += MoveBullet_Spiral(i, 2, 3);}
			break;
		case 6:
			if (bullet[i].cnt == 0) {flag += MoveBullet_NW(i);}
			else if (bullet[i].cnt == 1) {	flag += MoveBullet_Spiral(i, -1, 2);}
			else if (bullet[i].cnt == 2) {flag += MoveBullet_Spiral(i, -1, 3);}
			else if (bullet[i].cnt == 3) {flag += MoveBullet_Spiral(i, 1, 3);}
			else if (bullet[i].cnt == 4) { flag += MoveBullet_Spiral(i, 2, 2); }
			else if (bullet[i].cnt == 5) {flag += MoveBullet_Spiral(i, 4, 2);}
			else if (bullet[i].cnt == 6) {flag += MoveBullet_Spiral(i, 6, 2);}
			else if (bullet[i].cnt == 7) {flag += MoveBullet_Spiral(i, 7, 1);}
			else if (bullet[i].cnt == 8) {flag += MoveBullet_Spiral(i, 8, 0);}
			else if (bullet[i].cnt == 9) {flag += MoveBullet_Spiral(i, 7, -1);}
			else if (bullet[i].cnt == 10) {flag += MoveBullet_Spiral(i, 6, -2);}
			else if (bullet[i].cnt == 11) {flag += MoveBullet_Spiral(i, 4, -2);}
			else if (bullet[i].cnt == 12) {flag += MoveBullet_Spiral(i, 3, -3);}
			else if (bullet[i].cnt == 13) {flag += MoveBullet_Spiral(i, 2, -3);}
			break;
		case 7:
			if (bullet[i].cnt == 0) {flag += MoveBullet_SE(i);}
			else if (bullet[i].cnt == 1) {flag += MoveBullet_Spiral(i, 1, -2);}
			else if (bullet[i].cnt == 2) {	flag += MoveBullet_Spiral(i, 1, -3);}
			else if (bullet[i].cnt == 3) {flag += MoveBullet_Spiral(i, -1, -3);}
			else if (bullet[i].cnt == 4) {flag += MoveBullet_Spiral(i, -2, -2);}
			else if (bullet[i].cnt == 5) { flag += MoveBullet_Spiral(i, -4, -2); }
			else if (bullet[i].cnt == 6) {flag += MoveBullet_Spiral(i, -6, -2);}
			else if (bullet[i].cnt == 7) {flag += MoveBullet_Spiral(i, -7, -1);}
			else if (bullet[i].cnt == 8) {flag += MoveBullet_Spiral(i, -8, 0);}
			else if (bullet[i].cnt == 9) {	flag += MoveBullet_Spiral(i, -7, 1);}
			else if (bullet[i].cnt == 10) {flag += MoveBullet_Spiral(i, -6, 2);}
			else if (bullet[i].cnt == 11) {flag += MoveBullet_Spiral(i, -4, 2);}
			else if (bullet[i].cnt == 12) {flag += MoveBullet_Spiral(i, -3, 3);}
			else if (bullet[i].cnt == 13) { flag += MoveBullet_Spiral(i, -2, 3); }
			break;
		}
		bullet[i].cnt++;
	}
	if (!flag) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}


//BulletPattern_Gyro -> 1ĭ�� �����̴� ȸ�� ���� �ұ����� ����
int BulletPattern_Gyro() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_GYRO + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) { if (ENEMY_POS_Y == GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - 1) ++PatternCycle; }
	else { PatternTimeEnded = 1; }
	for (int i = 0; i < PatternCycle * 8; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); BULLETCOUNT++; }
		switch (i % 8) {
		case 0:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_SE(i);
			else flag += MoveBullet_S(i);
			break;
		case 1:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_S(i);
			else flag += MoveBullet_SW(i);
			break;
		case 2:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_SW(i);
			else flag += MoveBullet_W(i);
			break;
		case 3:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_W(i);
			else flag += MoveBullet_NW(i);
			break;
		case 4:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_NW(i);
			else flag += MoveBullet_N(i);
			break;
		case 5:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_N(i);
			else flag += MoveBullet_NE(i);
			break;
		case 6:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_NE(i);
			else flag += MoveBullet_E(i);
			break;
		case 7:
			if ((BULLETCOUNT / 8 + BULLETCOUNT % 8) % 6 < 3) flag += MoveBullet_E(i);
			else flag += MoveBullet_SE(i);
			break;
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//BulletPattern_Shotgun -> ���̾Ƹ�� ������� ���� ����
int BulletPattern_Shotgun() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_SHOTGUN + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) ++PatternCycle;
	else PatternTimeEnded = 1;
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); BULLETCOUNT++; }
		if (bullet[i].BULLET_POS_Y < 10) {
			switch (i % 3) {
			case 0: flag += MoveBullet_S(i); break;
			case 1: flag += MoveBullet_S(i); break;
			case 2: flag += MoveBullet_S(i); break;
			}
		}
		else if (bullet[i].BULLET_POS_Y < 25) {
			switch (i % 3) {
			case 0: flag += MoveBullet_SE(i); break;
			case 1: flag += MoveBullet_S(i); break;
			case 2: flag += MoveBullet_SW(i); break;
			}
		}
		else {
			switch (i % 3) {
			case 0: flag += MoveBullet_SW(i); break;
			case 1: flag += MoveBullet_S(i); break;
			case 2: flag += MoveBullet_SE(i); break;
			}
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Bullet Pattern Road -> 
int BulletPattern_Road() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if ((CheckedTime < PATTERNTIME_ROAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)) ++PatternCycle;
	else PatternTimeEnded = 1;
	for (int i = 0; i < 5 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); BULLETCOUNT++; }
		switch (i % 5) {
		case 0: flag += MoveBullet_S(i); break;
		case 1: flag += MoveBullet_S(i); break;
		case 2: flag += MoveBullet_S(i); break;
		case 3: flag += MoveBullet_S(i); break;
		case 4: flag += MoveBullet_S(i); break;
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//BulletPattern_Meteor
int BulletPattern_Meteor() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if ((CheckedTime < PATTERNTIME_METEOR + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)) ++PatternCycle;
	else PatternTimeEnded = 1;
	for (int i = 0; i < 2 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); BULLETCOUNT++; }
		switch (i % 2) {
		case 0: flag += MoveBullet_S(i); break;
		case 1: flag += MoveBullet_S(i); break;
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//----------------------------------------------------------------
//-------------------Bullet Invalidate Func.----------------------

//�Ѿ��� ��ġ ���� �Լ�
void InvalidateBullet() {
	if (!CalculateBulletTimeBuffer()) {
		if (!GamePaused) {		//Game�� Paused���� �ʾ��� �� bullet�� ���� �� ��ġ ����
			BulletLaunchTime();	//���� ���۽ð� �� ���� ����
			if (PatternStart) {
				switch (PatternNumber) {	//���� �ѹ��� ���� �ٸ� �Լ� �۵�
				case 1: if (BulletPattern_Spread()) ClearBulletPosition(); break;
				case 2: if (BulletPattern_Laser()) ClearBulletPosition(); break;
				case 3: if (BulletPattern_CircleSpread()) ClearBulletPosition(); break;
				case 4: if (BulletPattern_3way()) ClearBulletPosition(); break;
				case 5: if (BulletPattern_Chaos()) ClearBulletPosition(); break;
				case 6: if (BulletPattern_Gyro()) ClearBulletPosition(); break;
				case 7: if (BulletPattern_Shotgun()) ClearBulletPosition(); break;
				case 8: if (BulletPattern_Road()) ClearBulletPosition(); break;
				case 9: if (BulletPattern_Meteor()) ClearBulletPosition(); break;
				case 10: if (BulletPattern_Spiral()) ClearBulletPosition(); break;
				default: break;
				}
			}
			else return;
		}
	}
	else {
		//�Ѿ��� ���۽ð����� ���� �������� ���� ���� �˻��ϱ� ���� �ۼ��Ͽ���
		for (int i = 0; i < BULLETCOUNT; i++) {
			if (bullet[i].BulletActivation) {
				if (DetectCollision_BulletwithPlayer(bullet[i].BULLET_POS_X, bullet[i].BULLET_POS_Y)) { //�÷��̾�� �ε������� �Ѿ� ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ����
					HideBullet(i); bullet[i].BulletActivation = 0; bullet[i].CollisionPlayer = 1;	//�÷��̾�� �浹�ߴٴ� �ε������� �۵�, �Ѿ� ��Ȱ��ȭ, �Ѿ� ����
				}
			}
		}
	}
}
#endif // !BULLET_H