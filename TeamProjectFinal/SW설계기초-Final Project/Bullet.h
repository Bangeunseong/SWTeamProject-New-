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

//랜덤 패턴 넘버 지정
int SetRandomPatternNumber(int max) { PatternNumber = rand() % max + 1; }

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
	PatternStart = 0;
	PatternCycle = 0;
	PatternNumber = 0;
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
	for (int i = 0; i < 6; i++) {
		if (y == PLAYER_POS_Y && x == PLAYER_POS_X + i) return 1;
	}
	return 0;
}

//-----------------------Bullet Position Functions-------------------------
//Move bullet to West
int MoveBullet_W(int bulletnumber) {
	//--------------------총알 작동 여부 검사함수(총알 초기화도 같이 함)----------------------
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { //총알이 초기 세팅이라면 총알의 위치 Enemy가 있는 위치로 초기화, Bullet이 작동하는지 알려주는 인디케이터 1로 갱신
		BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; 
	}
	if (!bullet[bulletnumber].BulletActivation) return 0;	//총알이 작동하고 있지 않다면 그냥 0을 반환
	//----------------------------------------------------------------------------------------------

	HideBullet(bulletnumber);		//총알을 숨긴다
	//--------------------충돌 관련 함수-------------------------
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) {		//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
		bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1;
	}
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y)) //벽에 부딪히지 않았으면 X좌표 - 2
		bullet[bulletnumber].BULLET_POS_X -= 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }	//부딪혔다면 총알 비활성화, 벽에 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	//--------------------------------------------------------------

	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South West
int MoveBullet_SW(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y + 1)) { 
		bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South
int MoveBullet_S(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y + 1)) bullet[bulletnumber].BULLET_POS_Y++;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to SouthEast
int MoveBullet_SE(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y + 1)) {
		bullet[bulletnumber].BULLET_POS_X += 2; bullet[bulletnumber].BULLET_POS_Y++;
	}
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to East
int MoveBullet_E(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation && !bullet[bulletnumber].CollisionPlayer && !bullet[bulletnumber].CollisionWall) { BulletPostionRenewal(bulletnumber); bullet[bulletnumber].BulletActivation = 1; }
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X += 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//----------------------------------------------------------------------------

void BulletLaunchTime() {	//아직 불안정하므로 수정이 필요함!!
	if (!PatternStart) { 
		double CheckedTime = TimeCheckerEnd() - PausingTime;
		if (CheckedTime > 3.0 && CheckedTime < 13.0) { SetRandomPatternNumber(TOTALPATTERNCOUNT); PatternStart = 1; BulletLaunchStartTime = CheckedTime; }
		else if (CheckedTime > 13.0 && CheckedTime < 23.0) { SetRandomPatternNumber(TOTALPATTERNCOUNT); PatternStart = 1; BulletLaunchStartTime = CheckedTime; }
	}
	else return;
}

//Bullet Pattern
int BulletPattern_Spread() {
	int flag = 0; 
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_SPREAD + BulletLaunchStartTime && CheckedTime > BulletLaunchStartTime) BULLETCOUNT = (++PatternCycle) * 3;
	for (int i = 0; i < 3 * PatternCycle; i++) {
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;
		case 1: flag += MoveBullet_S(i); break;
		case 2: flag += MoveBullet_SW(i); break;
		}
		
	}
	if (!flag) return 1;
	return 0;
}

//
void InvalidateBullet() {
	if (!CalculateBulletTimeBuffer()) {
		BulletLaunchTime();
		if (PatternStart) {
			switch (PatternNumber) {
			case 1: if (BulletPattern_Spread()) ClearBulletPosition(); break;
			default: break;
			}
		}
		else return;
	}
	else {
		//총알이 버퍼시간으로 인해 움직이지 않을 때도 검사하기 위해 작성하였다
		for (int i = 0; i < BULLETCOUNT; i++) {
			if (DetectCollision_BulletwithPlayer(bullet[i].BULLET_POS_X, bullet[i].BULLET_POS_Y)) { //플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신
				HideBullet(i); bullet[i].BulletActivation = 0; bullet[i].CollisionPlayer = 1; 
			}
		}
	}
}
#endif // !BULLET_H