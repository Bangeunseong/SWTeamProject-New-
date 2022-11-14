#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Enemy.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//Bullet Time Buffer
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime - PausingTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
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

void ClearBulletPosition() {
	for (int i = 0; i < BULLETCOUNT; i++) {
		HideBullet(i);
		bullet[i].BULLET_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		bullet[i].BULLET_POS_Y = GAMEBOARD_ORIGIN_Y + 5;
		bullet[i].BulletActivation = bullet[i].CollisionPlayer = bullet[i].CollisionWall = 0;
	}
	PatternCycle = 0;
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

int DetectCollision_BulletwithPlayer(int x, int y) {
	if (PLAYER_POS_Y == y) {
		for (int i = 0; i < 6; i++) if (PLAYER_POS_X + i == x) return 1;
	}
	return 0;
}

//-----------------------Bullet Position Functions-------------------------
//Move bullet to West
int MoveBullet_W(int bulletnumber) {	
	if (bullet[bulletnumber].CollisionPlayer || bullet[bulletnumber].CollisionWall) return 0;//총알이 벽이나 플레이어에 부딪혔으면 0을 리턴하며 종료
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }//총알이 초기 세팅이라면 총알의 위치 Enemy가 있는 위치로 초기화, Bullet이 작동하는지 알려주는 인디케이터 1로 갱신
	HideBullet(bulletnumber);//총알을 숨긴다
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X -= 2;//벽에 부딪히지 않았으면 X좌표 - 2
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }//부딪혔다면 총알 비활성화, 벽에 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South West
int MoveBullet_SW(int bulletnumber) {
	if (bullet[bulletnumber].CollisionPlayer || bullet[bulletnumber].CollisionWall) return 0;
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y + 1)) { 
		bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South
int MoveBullet_S(int bulletnumber) {
	if (bullet[bulletnumber].CollisionPlayer || bullet[bulletnumber].CollisionWall) return 0;
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y + 1)) bullet[bulletnumber].BULLET_POS_Y++;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to SouthEast
int MoveBullet_SE(int bulletnumber) {
	if (bullet[bulletnumber].CollisionPlayer || bullet[bulletnumber].CollisionWall) return 0;
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y + 1)) {
		bullet[bulletnumber].BULLET_POS_X += 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to East
int MoveBullet_E(int bulletnumber) {
	if (bullet[bulletnumber].CollisionPlayer || bullet[bulletnumber].CollisionWall) return 0;
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X += 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//----------------------------------------------------------------------------

void BulletLaunchTime() {
	if (!PatternStart) { 
		if (TimeCheckerEnd() > 3.0) { PatternStart = 1; PatternNumber = 1; BulletLaunchStartTime = TimeCheckerEnd(); }
	}
}

//Bullet Pattern
int BulletPattern_Spread() {
	int flag = 0; 
	if (TimeCheckerEnd() < PATTERNTIME_SPREAD + BulletLaunchStartTime && TimeCheckerEnd() > BulletLaunchStartTime) BULLETCOUNT = (++PatternCycle) * 3;
	for (int i = 0; i < 3 * PatternCycle; i++) {
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;
		case 1: flag += MoveBullet_S(i); break;
		case 2: flag += MoveBullet_SW(i); break;
		}
	}
	if (!flag) { PatternNumber = 0; PatternStart = 0; return 1; } return 0;
}

//
void InvalidateBullet() {
	if (!CalculateBulletTimeBuffer()) {
		BulletLaunchTime();
		if (PatternStart) if (BulletPattern_Spread()) ClearBulletPosition();
	}
}
#endif // !BULLET_H