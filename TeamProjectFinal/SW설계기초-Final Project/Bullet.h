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

//랜덤 패턴 넘버 지정
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
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y - 1)) bullet[bulletnumber].BULLET_POS_Y--;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to NorthWest
int MoveBullet_NW(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y - 1)) { bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y--; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to NorthEast
int MoveBullet_NE(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y - 1)) { bullet[bulletnumber].BULLET_POS_X += 2; bullet[bulletnumber].BULLET_POS_Y--; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to West
int MoveBullet_W(int bulletnumber) {
	//--------------------총알 작동 여부 검사함수----------------------
	if (!bullet[bulletnumber].BulletActivation) return 0;	//총알이 작동하고 있지 않다면 그냥 0을 반환
	//--------------------------------------------------------------------

	HideBullet(bulletnumber);		//총알을 숨긴다
	//--------------------충돌 관련 함수-------------------------
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) {		//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
		bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0;
	}
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y)) //벽에 부딪히지 않았으면 X좌표 - 2
		bullet[bulletnumber].BULLET_POS_X -= 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }	//부딪혔다면 총알 비활성화, 벽에 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	//--------------------------------------------------------------

	ShowBullet(bulletnumber); return 1;
}
//Move bullet to South West
int MoveBullet_SW(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

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
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y + 1)) bullet[bulletnumber].BULLET_POS_Y++;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to SouthEast
int MoveBullet_SE(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

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
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X += 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}

//Move bullet to x, y coordinate
int MoveBullet_Spiral(int bulletnumber, int x, int y) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + x, bullet[bulletnumber].BULLET_POS_Y - y)) { bullet[bulletnumber].BULLET_POS_X += x; bullet[bulletnumber].BULLET_POS_Y -= y; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}

//----------------------------------------------------------------------------
//---------------------Bullet LaunchTime Set Function----------------------
//When bullet launches record time and set patternnumber, start pattern
void BulletLaunchTime() {
	if (!PatternStart) {	//패턴이 시작되지 않았을 경우
		double CheckedTime = TimeCheckerEnd() - PausingTime;
		if (CheckedTime > BulletPatternEndTime + PATTERNDURATION) {		//체크한 시간이 패턴 종료시간 + durationtime보다 크면 작동
			SetRandomPatternNumber(TOTALPATTERNCOUNT);		//패턴 넘버 결정(랜덤)
			if (PatternNumber == 1 || PatternNumber == 10) BulletSpeed = 1.0;		//패턴 넘버 1번일때 bulletspeed
			else if (PatternNumber == 3 || PatternNumber == 5) BulletSpeed = 1.5;		//패턴 넘버 3, 5, 10일때 1.5 bulletspeed
			else if (PatternNumber == 2 || PatternNumber == 4) BulletSpeed = 8.0;		//패턴 넘버가 2, 4일때 8.0 bulletspeed
			else if (PatternNumber == 6) BulletSpeed = 3.0;		//패턴 넘버가 6일때 3.0 bulletspeed
			else if (PatternNumber == 7 || PatternNumber == 8) BulletSpeed = 5.0;		//패턴 넘버가 7, 8일때 5.0 bulletspeed
			else if (PatternNumber == 9) BulletSpeed = 4.0;		//패턴 넘버가 9일때 4.0 bulletspeed
			PatternStart = EnemyIsMoving = 1; PatternTimeEnded = 0; EnemyMovementTiming = BulletPatternStartTime = CheckedTime;	//패턴 시작 인디케이터 1로 갱신, 패턴 시작시간 갱신, Enemy가 움직이고 있다는 인디케이터 1로 갱신
		}
	}
	else return;
}

//------------------------------------------------------------------------
//---------------------Bullet Pattern Functions--------------------------

//Bullet Pattern Spread_Note : 좌우로 움직임(일정한 속도와 패턴으로 움직임)
int BulletPattern_Spread() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_SPREAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) BULLETCOUNT = (++PatternCycle) * 3; //패턴 지속시간일때 패턴사이클 및 bulletcount 증가
	else PatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }	//만약 총알이 사용되지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 총알 출력
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;	//총알을 남서쪽으로 이동
		case 1: flag += MoveBullet_S(i); break;		//총알을 남쪽으로 이동
		case 2: flag += MoveBullet_SW(i); break;	//총알을 남동쪽으로 이동
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }	//만약 모든 총알들이 게임판에서 사라졌을 경우 --패턴 종료시간 갱신--, 1을 반환
	return 0;
}

//Bullet Pattern Laser_Note : 좌우로 움직임(움직임 패턴 구현 필요)
int BulletPattern_Laser() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if ((CheckedTime < PATTERNTIME_LASER + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)) BULLETCOUNT = (++PatternCycle) * 3;//패턴 지속시간일때 패턴사이클 및 bulletcount 증가
	else PatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
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

//Bullet Pattern Circle Spread_Note : 게임영역 전체를 움직임(전체를 움직일 때 Enemy 속도를 충분히 낮출필요 있음, 다시 원점으로 돌아와야 함, 결국 움직임 패턴 구현 필요)
int BulletPattern_CircleSpread() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if ((CheckedTime < PATTERNTIME_CIRCLESPREAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)) { //패턴 지속시간일때 패턴사이클 및 bulletcount 증가
		if ((int)(CheckedTime - BulletPatternStartTime) % 2 == 0)
			BULLETCOUNT = (++PatternCycle) * 8;
	}
	else PatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
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
	if (CheckedTime < PATTERNTIME_3WAY + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) BULLETCOUNT = (++PatternCycle) * 3; //패턴 지속시간일때 패턴사이클 및 bulletcount 증가
	else PatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }	//만약 총알이 사용되지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 총알 출력
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;	//총알을 남서쪽으로 이동
		case 1: flag += MoveBullet_S(i); break;		//총알을 남쪽으로 이동
		case 2: flag += MoveBullet_SW(i); break;	//총알을 남동쪽으로 이동
		}
	}
	if (!flag && !EnemyIsMoving) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }	//만약 모든 총알들이 게임판에서 사라졌을 경우, 그리고 Enemy가 제자리로 돌아왔을 때 --패턴 종료시간 갱신--, 1을 반환
	return 0;
}

//BulletPattern_Chaos
int BulletPattern_Chaos() {		//이것도 마찬가지로 Enemy Movement Pattern 필요
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_CHAOS + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) { //패턴 지속시간일때 패턴사이클 및 bulletcount 증가
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
int BulletPattern_Spiral() {		//회전 패턴 삼각함수를 사용할 수 없으면 하나씩 찍는 것 말곤 방법이 없는 것 같습니다. 하나씩 다 찍었습니다.
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


//BulletPattern_Gyro -> 1칸씩 움직이는 회전 패턴 불교문양 같음
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

//BulletPattern_Shotgun -> 다이아몬드 모양으로 패턴 형성
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

//총알의 위치 갱신 함수
void InvalidateBullet() {
	if (!CalculateBulletTimeBuffer()) {
		if (!GamePaused) {		//Game이 Paused되지 않았을 때 bullet의 상태 및 위치 갱신
			BulletLaunchTime();	//패턴 시작시간 및 패턴 결정
			if (PatternStart) {
				switch (PatternNumber) {	//패턴 넘버에 따라 다른 함수 작동
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
		//총알이 버퍼시간으로 인해 움직이지 않을 때도 검사하기 위해 작성하였다
		for (int i = 0; i < BULLETCOUNT; i++) {
			if (bullet[i].BulletActivation) {
				if (DetectCollision_BulletwithPlayer(bullet[i].BULLET_POS_X, bullet[i].BULLET_POS_Y)) { //플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신
					HideBullet(i); bullet[i].BulletActivation = 0; bullet[i].CollisionPlayer = 1;	//플레이어와 충돌했다는 인디케이터 작동, 총알 비활성화, 총알 숨김
				}
			}
		}
	}
}
#endif // !BULLET_H