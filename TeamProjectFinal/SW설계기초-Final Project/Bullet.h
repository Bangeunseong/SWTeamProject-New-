#pragma once
#pragma warning(disable:4996)
#include "VariableSets.h"
#include "Enemy.h"
#include "CursorFunctions.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//Bullet Time Buffer
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime - PausingTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
}

void ClearBulletPosition() {
	for (int i = 0; i < BULLETCOUNT; i++) {
		bullet[i].BULLET_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		bullet[i].BULLET_POS_Y = GAMEBOARD_ORIGIN_Y + 5;
	}
	BULLETCOUNT = 0;
}

void BulletPostionRenewal(int bulletnumber) {
	bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2;
	bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 3;
}

int DetectCollision_BulletwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == 1)
		return 1;
	return 0;
}

void HideBullet(int bulletnumber) {
	SetCurrentCursorPos(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y);
	UniBoard[bullet[bulletnumber].BULLET_POS_Y - GAMEBOARD_ORIGIN_Y][bullet[bulletnumber].BULLET_POS_X - GAMEBOARD_ORIGIN_X] = 0;
	printf(" ");
}

void ShowBullet(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) bullet[bulletnumber].BulletActivation = 1;
	SetCurrentCursorPos(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y);
	UniBoard[bullet[bulletnumber].BULLET_POS_Y - GAMEBOARD_ORIGIN_Y][bullet[bulletnumber].BULLET_POS_X - GAMEBOARD_ORIGIN_X] = BULLET;
	printf("*");
}

//-----------------------Bullet Position Functions-------------------------
//Move bullet to West
void MoveBullet_W(int bulletnumber) {	
	HideBullet(bulletnumber);
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X -= 2;
	else { bullet[bulletnumber].BulletActivation = 0; return; }
	ShowBullet(bulletnumber);
}
//Move bullet to South West
void MoveBullet_SW(int bulletnumber) {
	HideBullet(bulletnumber);
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y + 1)) { 
		bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; return; }
	ShowBullet(bulletnumber);
}
//Move bullet to South
void MoveBullet_S(int bulletnumber) {
	HideBullet(bulletnumber);
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y + 1)) bullet[bulletnumber].BULLET_POS_Y++;
	else { bullet[bulletnumber].BulletActivation = 0; return; }
	ShowBullet(bulletnumber);
}
//Move bullet to SouthEast
void MoveBullet_SE(int bulletnumber) {
	HideBullet(bulletnumber);
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y + 1)) {
		bullet[bulletnumber].BULLET_POS_X += 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; return; }
	ShowBullet(bulletnumber);
}
//Move bullet to East
void MoveBullet_E(int bulletnumber) {
	HideBullet(bulletnumber);
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X += 2;
	else { bullet[bulletnumber].BulletActivation = 0; return; }
	ShowBullet(bulletnumber);
}
//----------------------------------------------------------------------------

void BulletLaunchTime() {
	if (!PatternStart) { 
		if (TimeCheckerEnd() > 3.0) { PatternStart = 1; BulletLaunchStartTime = TimeCheckerEnd(); }
	}
}

//Bullet Pattern
void BulletPattern_Spread() {
	int flag = 0; PatternNumber = 1;
	if (TimeCheckerEnd() < PATTERNTIME_SPREAD && TimeCheckerEnd() > BulletLaunchStartTime) BULLETCOUNT = (PatternCycle++) * 3;
	else flag = 1;
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (BULLETCOUNT <= i && !flag) BulletPostionRenewal(i);
		switch (i % 3) {
		case 0: MoveBullet_SE(i); break;
		case 1: MoveBullet_S(i); break;
		case 2: MoveBullet_SW(i); break;
		}
	}
}

//
void InvalidateBullet() {
	if (!CalculateBulletTimeBuffer()) {
		BulletLaunchTime();
		if (PatternStart) BulletPattern_Spread();
	}
}
#endif // !BULLET_H