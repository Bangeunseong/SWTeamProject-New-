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
	printf("%c", BulletModelPerPattern[PatternNumber - 1]);
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
	BulletSpeed = 2;
}

void BulletPostionRenewal(int bulletnumber) {
	if (PatternNumber == 1) {
		bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2;
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 3;
	}
	else if (PatternNumber == 2 || PatternNumber == 4) {
		if (bulletnumber % 3 == 0) { bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 1; }
		else if (bulletnumber % 3 == 1) { bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2; }
		else { bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 3; }
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 3;
	}
	else if (PatternNumber == 3) {
		bullet[bulletnumber].BULLET_POS_X = ENEMY_POS_X + 2;
		bullet[bulletnumber].BULLET_POS_Y = ENEMY_POS_Y + 1;
	}
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
//Move bullet to North
int MoveBullet_N(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y - 1)) bullet[bulletnumber].BULLET_POS_Y--;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to NorthWest
int MoveBullet_NW(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X - 2, bullet[bulletnumber].BULLET_POS_Y - 1)) { bullet[bulletnumber].BULLET_POS_X -= 2; bullet[bulletnumber].BULLET_POS_Y--; }
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to NorthEast
int MoveBullet_NE(int bulletnumber) {
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
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
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y + 1)) bullet[bulletnumber].BULLET_POS_Y++;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//Move bullet to SouthEast
int MoveBullet_SE(int bulletnumber) {
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
	if (!bullet[bulletnumber].BulletActivation) return 0;

	HideBullet(bulletnumber);
	if (DetectCollision_BulletwithPlayer(bullet[bulletnumber].BULLET_POS_X, bullet[bulletnumber].BULLET_POS_Y)) { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionPlayer = 1; }//플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_BulletwithWall(bullet[bulletnumber].BULLET_POS_X + 2, bullet[bulletnumber].BULLET_POS_Y)) bullet[bulletnumber].BULLET_POS_X += 2;
	else { bullet[bulletnumber].BulletActivation = 0; bullet[bulletnumber].CollisionWall = 1; return 0; }
	ShowBullet(bulletnumber); return 1;
}
//----------------------------------------------------------------------------

//When bullet launches record time and set patternnumber, start pattern
void BulletLaunchTime() {
	if (!PatternStart) {	//패턴이 시작되지 않았을 경우
		double CheckedTime = TimeCheckerEnd() - PausingTime;
		if (CheckedTime > BulletPatternEndTime + PATTERNDURATION) {	//체크한 시간이 패턴 종료시간 + durationtime보다 크면 작동
			SetRandomPatternNumber(TOTALPATTERNCOUNT);					//패턴 넘버 결정(랜덤)
			if (PatternNumber == 2) BulletSpeed = 6;									//패턴 넘버가 2번이면 총알 속도 조금 증가
			else if (PatternNumber == 1) BulletSpeed = 1;
			else if (PatternNumber == 4) BulletSpeed = 8;
			PatternStart = 1; BulletPatternStartTime = CheckedTime;				//패턴 시작 인디케이터 1로 갱신, 패턴 시작시간 갱신
		}
	}
	else return;
}

//Bullet Pattern Spread_Note : 좌우로 움직임(일정한 속도와 패턴으로 움직임)
int BulletPattern_Spread() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_SPREAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) BULLETCOUNT = (++PatternCycle) * 3; //패턴 사이클이 증가함에 따라 총알의 갯수도 3의 배수로 증가(3개의 총알을 하나의 세트로 이용하기 때문)
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }	//만약 총알이 사용되지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 총알 출력
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;	//총알을 남서쪽으로 이동
		case 1: flag += MoveBullet_S(i); break;		//총알을 남쪽으로 이동
		case 2: flag += MoveBullet_SW(i); break;	//총알을 남동쪽으로 이동
		}
	}
	if (!flag) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }	//만약 모든 총알들이 게임판에서 사라졌을 경우 --패턴 종료시간 갱신--, 1을 반환
	return 0;
}

//Bullet Pattern 3way
int BulletPattern_3way() {
	int flag = 0; 
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_3WAY + BulletPatternStartTime && CheckedTime > BulletPatternStartTime) BULLETCOUNT = (++PatternCycle) * 3; //패턴 사이클이 증가함에 따라 총알의 갯수도 3의 배수로 증가(3개의 총알을 하나의 세트로 이용하기 때문)
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }	//만약 총알이 사용되지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 총알 출력
		switch (i % 3) {
		case 0: flag += MoveBullet_SE(i); break;	//총알을 남서쪽으로 이동
		case 1: flag += MoveBullet_S(i); break;		//총알을 남쪽으로 이동
		case 2: flag += MoveBullet_SW(i); break;	//총알을 남동쪽으로 이동
		}
	}
	if (!flag) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }	//만약 모든 총알들이 게임판에서 사라졌을 경우 --패턴 종료시간 갱신--, 1을 반환
	return 0;
}

//Bullet Pattern Laser_Note : 좌우로 움직임(움직임 패턴 구현 필요)
int BulletPattern_Laser() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_LASER + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)
		BULLETCOUNT = (++PatternCycle) * 3;
	for (int i = 0; i < 3 * PatternCycle; i++) {
		if (!bullet[i].BulletActivation && !bullet[i].CollisionPlayer && !bullet[i].CollisionWall) { BulletPostionRenewal(i); bullet[i].BulletActivation = 1; ShowBullet(i); }
		switch (i % 3) {
		case 0: flag += MoveBullet_S(i); break;
		case 1: flag += MoveBullet_S(i); break;
		case 2: flag += MoveBullet_S(i); break;
		}
	}
	if (!flag) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Bullet Pattern Circle Spread_Note : 게임영역 전체를 움직임(전체를 움직일 때 속도를 충분히 낮출필요 있음, 다시 원점으로 돌아와야 함, 결국 움직임 패턴 구현 필요)
int BulletPattern_CircleSpread() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < PATTERNTIME_CIRCLESPREAD + BulletPatternStartTime && CheckedTime > BulletPatternStartTime)
		BULLETCOUNT = (++PatternCycle) * 8;
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
	if (!flag) { BulletPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//총알의 위치 갱신 함수
void InvalidateBullet() {
	if (!CalculateBulletTimeBuffer()) {
		if (!GamePaused) {
			BulletLaunchTime();	//패턴 시작시간 및 패턴 결정
			if (PatternStart) {
				switch (PatternNumber) {	//패턴 넘버에 따라 다른 함수 작동
				case 1: if (BulletPattern_Spread()) ClearBulletPosition(); break;
				case 2: if (BulletPattern_Laser()) ClearBulletPosition(); break;
				case 3: if (BulletPattern_CircleSpread()) ClearBulletPosition(); break;
				case 4: if (BulletPattern_3way()) ClearBulletPosition(); break;
				default: break;
				}
			}
			else return;
		}
		else {
			//총알이 버퍼시간으로 인해 움직이지 않을 때도 검사하기 위해 작성하였다
			for (int i = 0; i < BULLETCOUNT; i++) {
				if (bullet[i].BulletActivation) {	//총알이 작동 중일때만 검사
					if (DetectCollision_BulletwithPlayer(bullet[i].BULLET_POS_X, bullet[i].BULLET_POS_Y)) { //플레이어와 부딪혔으면 총알 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신
						HideBullet(i); bullet[i].BulletActivation = 0; bullet[i].CollisionPlayer = 1;	//플레이어와 충돌했다는 인디케이터 작동, 총알 비활성화, 총알 숨김
					}
				}
			}
		}
	}
}
#endif // !BULLET_H