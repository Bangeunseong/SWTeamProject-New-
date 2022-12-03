#pragma once
#pragma warning(disable:4996)
#include <conio.h>
#include <WinUser.h>
#include <string.h>
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Item.h"
#include "Timer.h"
#include "UI.h"
#include "Npc.h"
#include "SoundPlay.h"
#ifndef PLAYER_H
#define PLAYER_H

//플레이어 인풋타임 버퍼 시간 계산 함수
int CalculatePlayerTimeBuffer() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime - PlayerInputTime > PLAYERTIMEBUFFER / CurSpeed) { PlayerInputTime = CheckedTime; return 0; }
	else return 1;
}

//게임 정지함수
void GamePause() {
	GamePaused = 1;
 	PausedTime = TimeCheckerEnd();
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	printf("Pause");
	while (1) { if (GetAsyncKeyState(QUIT) & 0x0001) { PausingTime += TimeCheckerEnd() - PausedTime; GamePaused = 0; break; } }
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	for (int i = 0; i < 5; i++) printf(" ");
}

//플레이어 위치 초기화 함수
void ClearPlayerPosition() {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - (Modellen / 2);
	PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 10;
}

//플레이어 출력 함수
void ShowPlayer() {
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else if (UsingSkill > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERUSINGSKILLCOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);

	int Modellen; int ModifiedLevel;
	if (PlayerLevel < 4) { Modellen = PlayerLevel * 2; ModifiedLevel = PlayerLevel - 1; }
	else { Modellen = 6; ModifiedLevel = 2; }
	for (int i = 0; i < Modellen; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf("%c", PlayerModel[PlayerModelIndex][ModifiedLevel][i]); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}
//플레이어 숨김 함수
void HidePlayer() {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf(" "); }
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}

//---------------------데미지 및 라이프 게이지 관련 처리 함수--------------------------

//플레이어 기준 벽과 부딫혔을 때 사용하는 함수
int DetectCollision_PlayerwithWall(int x, int y) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		if (EnemySkillPrisonActivation) {
			if (y <= P.LU_Y || y >= P.RD_Y) return 1;
			if ((x + i < P.LU_X + 2) || (x + i >= P.RD_X)) return 1;
		}
		else { if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == WALL) return 1; }
	}
	return 0;
}
//플레이어 기준 적과 부딫혔을 때 사용하는 함수
int DetectCollision_PlayerwithEnemy(int x, int y) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		for (int j = 0; j < ENEMYSIZE_H; j++) {
			for (int k = 0; k < ENEMYSIZE_W; k++) {
				if (EnemyModel[j][k] != ' ')
					if (ENEMY_POS_Y + j == PLAYER_POS_Y && ENEMY_POS_X + k == PLAYER_POS_X + i) return 1;
			}
		}
	}
	return 0;
}

int DetectCollision_PlayerwithBullet(int x, int y) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == BULLET) return 1;
	}
	return 0;
}

int DetectCollision_PlayerwithNpc(int x, int y, int n) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		for (int j = 0; j < NPCSIZE_H; j++) {
			for (int k = 0; k < NPCSIZE_W; k++) {
				if (NpcModel[n][j][k] != ' ')
					if ((npc[n].NPC_POS_Y) + j == PLAYER_POS_Y && (npc[n].NPC_POS_X) + k == PLAYER_POS_X + i) return 1;
			}
		}
	}
	return 0;
}

//플레이어 기준 아이템과 부딪혔을 때 검사하는 함수
int DetectCollision_PlayerwithItem(int x, int y) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	if (itemFLAG) {
		for (int i = 0; i < Modellen; i++) {
			if (x == PLAYER_POS_X + i && y == PLAYER_POS_Y) return 1;
		}
	}
	return 0;
}

//라이프 게이지 감소
void ReduceLifeGauge(int damage) {
	CurrentLife -= damage;
	for (int i = 0; i < SelectedLife; i++) { if (i >= CurrentLife) LifeGauge[i] = 0; }
}

//데미지 처리함수
void GetDamagedFromEnemy() {
	if (UsingSkill == 3) return;
	if (Invinsible == 1) { //무적인 상태에서 지속시간이 지나면 해제하는 함수
		if (TimeCheckerEnd() - CollisionTime - PausingTime > InvinsibleTime) { 
			Invinsible = 0; mciSendCommand(dwIDSE_D, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		}
	}
	if (DetectCollision_PlayerwithBullet(PLAYER_POS_X, PLAYER_POS_Y) && Invinsible == 0) {
		PlayCOLLISIONSound();
		if (PlayerLevel < 2) {		//플레이어 레벨 2보다 작은 경우 데미지 1을 받음
			ReduceLifeGauge(BULLETDAMAGE);
			InvalidateLifeGauge();												//라이프 게이지 갱신은 데미지를 받을 때만 수행
		}
		else { 
			EXP -= 2;
			if (PlayerLevel < 4) { HidePlayer(); PlayerLevel--; ShowPlayer(); }
			else PlayerLevel--;
		}
		Invinsible = 1; CollisionTime = TimeCheckerEnd() - PausingTime;		//무적상태로 만들고 충돌한 시간 갱신
		return;
	}
	if (DetectCollision_PlayerwithEnemy(PLAYER_POS_X, PLAYER_POS_Y) && Invinsible == 0) {
		PlayCOLLISIONSound();
		if (PlayerLevel > 2) { EXP -= 4; HidePlayer(); PlayerLevel -= 2; ShowPlayer(); }		//플레이어 레벨 3인 경우 2단계 강등
		else if (PlayerLevel > 1) {		//플레이어 레벨 2인 경우 1단계 강등 및 데미지 1 받음
			ReduceLifeGauge(BULLETDAMAGE);
			InvalidateLifeGauge();												//라이프 게이지 갱신은 데미지를 받을 때만 수행
			EXP -= 4;
			HidePlayer(); PlayerLevel--; ShowPlayer();
		}
		else {	//플레이어 레벨 1인 경우 데미지 2 받음
			ReduceLifeGauge(ENEMYDAMAGE);
			InvalidateLifeGauge();												//라이프 게이지 갱신은 데미지를 받을 때만 수행
		}
		Invinsible = 1; CollisionTime = TimeCheckerEnd() - PausingTime;		//무적상태로 만들고 충돌한 시간 갱신
		return;
	}
	if (Invinsible == 0) {
		for (int i = 0; i < NPC_COUNT; i++) {
			if (DetectCollision_PlayerwithNpc(PLAYER_POS_X, PLAYER_POS_Y, i)) {
				if (PlayerLevel < 2) {		//플레이어 레벨 2보다 작은 경우 데미지 1을 받음
					ReduceLifeGauge(BULLETDAMAGE);
					InvalidateLifeGauge();												//라이프 게이지 갱신은 데미지를 받을 때만 수행
				}
				else {
					EXP -= 2;
					if (PlayerLevel < 4) { HidePlayer(); PlayerLevel--; ShowPlayer(); }
					else PlayerLevel--;
				}
				Invinsible = 1; CollisionTime = TimeCheckerEnd() - PausingTime;		//무적상태로 만들고 충돌한 시간 갱신
				return;
			}
		}
	}
}


//-----------------------------------------------------------------------------------------------

//--------------------------사용자 입력 키에 따른 위치 변환 및 스킬 사용 함수------------------------------
//사용자 입력 키에 따라 위치 변환 함수

void shiftUp() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y - 1)) PLAYER_POS_Y--;
	ShowPlayer();
}
void shiftDown() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y + 1)) PLAYER_POS_Y++;
	ShowPlayer();
}
void shiftLeft() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X - 1, PLAYER_POS_Y)) PLAYER_POS_X--;
	ShowPlayer();
}
void shiftRight() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X + 1, PLAYER_POS_Y)) PLAYER_POS_X++;
	ShowPlayer();
}

//------------------------------------------------------------------------------------------------------------------

//-------------------------------------플레이어 총알 관련 함수------------------------------------------

int CalculateP_BulletTimeBuffer() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (PlayerWeapon == 0) P_BULLETLAUNCHTIMEBUFFER = 0.2;
	else if (PlayerWeapon == 1) P_BULLETLAUNCHTIMEBUFFER = 0.1;
	else if (PlayerWeapon == 2) P_BULLETLAUNCHTIMEBUFFER = 0.5;
	if (CheckedTime - P_BulletInputTime > P_BULLETTIMEBUFFER / P_BulletSpeed) { P_BulletInputTime += P_BULLETTIMEBUFFER / P_BulletSpeed; return 0; }
	else return 1;
}

void HideP_Bullet(int P_bulletnumber) {
	SetCurrentCursorPos(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y);
	printf(" ");
}

void ShowP_Bullet(int P_bulletnumber) {
	SetCurrentCursorPos(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y);
	printf("%c", PLAYERBULLETMODEL[PlayerWeapon]);
}

void ClearAll_PBulletPosition() {
	for (int i = 0; i < BULLETCOUNTLIMIT; i++) {
		HideP_Bullet(i);
		PB[i].BulletActivation = PB[i].CollisionEnemy = PB[i].CollisionWall = PB[i].CollisionNpc = PB[i].inProgress = 0;
	}
	P_BULLETCOUNTSTART = 0;
	P_BULLETCOUNTEND = -1;
	P_BulletInputTime = 0;
}

void ClearSingle_PBulletPosition(int P_bulletnumber) {
	PB[P_bulletnumber].BulletActivation = PB[P_bulletnumber].CollisionEnemy = PB[P_bulletnumber].CollisionWall = PB[P_bulletnumber].CollisionNpc = PB[P_bulletnumber].BulletDamage = PB[P_bulletnumber].inProgress = 0;
	PB[P_bulletnumber].BulletModel = "";
}

void InvalidateP_BulletDamageNModel(int P_bulletnumber) {
	if (PlayerWeapon == 0) { PB[P_bulletnumber].BulletDamage = 1 + PlayerLevel / 2; PB[P_bulletnumber].BulletModel = PLAYERBULLETMODEL[PlayerWeapon]; }
	else if (PlayerWeapon == 1) { PB[P_bulletnumber].BulletDamage = 2 + PlayerLevel / 2; PB[P_bulletnumber].BulletModel = PLAYERBULLETMODEL[PlayerWeapon]; }
	else if (PlayerWeapon == 2) { PB[P_bulletnumber].BulletDamage = 4 + PlayerLevel / 2; PB[P_bulletnumber].BulletModel = PLAYERBULLETMODEL[PlayerWeapon]; }
}

void P_BulletPositionRenewal(int P_bulletnumber) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	if (PlayerWeapon == 0) {	//DEFAULT GUN BulletPosition
		if (P_bulletnumber % 2 == 0) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + Modellen / 2 - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + Modellen / 2; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
	}
	else if (PlayerWeapon == 1) {	//MACHINEGUN BulletPosition
		if (P_bulletnumber % 2 == 0) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + Modellen - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
	}
	else if (PlayerWeapon == 2) {	//SHOTGUN BulletPosition
		if (P_bulletnumber % 4 == 0) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else if(P_bulletnumber % 4 == 1){ PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + Modellen / 2 - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else if(P_bulletnumber % 4 == 2) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + Modellen / 2; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + Modellen - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
	}
}

int DetectCollision_P_BulletwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == WALL)
		return 1;
	return 0;
}

int DetectCollision_P_BulletwithEnemy(int x, int y) {
	for (int i = 0; i < ENEMYSIZE_H; i++) {
		for (int j = 0; j < ENEMYSIZE_W; j++) {
			if (EnemyModel[i][j] != ' ') {
				if (ENEMY_POS_X + j == x && ENEMY_POS_Y + i == y) return 1;
			}
		}
	}
	return 0;
}

int DetectCollision_P_BulletwithNpc(int x, int y, int n) {
	if (!npc[n].NpcActivation) return 0;
	int flag = 0;
	for (int i = 0; i < NPCSIZE_H; i++) { if (npc[n].NPC_POS_Y + i == y) { flag = 1; break; } }
	if (!flag) return 0;

	for (int i = 0; i < NPCSIZE_W; i++) { if (npc[n].NPC_POS_X + i == x) return 1; }
	return 0;
}

//----------------------BulletMovementFunction-------------------------

int MoveP_Bullet_N(int P_bulletnumber) {
	if (!PB[P_bulletnumber].BulletActivation) return 0;
	HideP_Bullet(P_bulletnumber);
	if (NpcKilledOver) {
		if (DetectCollision_P_BulletwithEnemy(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y)) {
			PB[P_bulletnumber].BulletActivation = 0; PB[P_bulletnumber].CollisionEnemy = 1; StageEnemyHealth -= P_BULLETDAMAGE; return 0;		//Enemy가 받는 데미지도 처리
		}
	}
	for (int i = 0; i < NPC_COUNT; i++) {
		if (DetectCollision_P_BulletwithNpc(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y, i)) {
			PB[P_bulletnumber].BulletActivation = 0; PB[P_bulletnumber].CollisionNpc = 1; NpcGetDamagedFromPlayer(i); return 0;			//Npc가 받는 데미지도 처리
		}
	}
	if (!DetectCollision_P_BulletwithWall(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y - 1)) PB[P_bulletnumber].P_BULLET_POS_Y--;
	else { PB[P_bulletnumber].BulletActivation = 0; PB[P_bulletnumber].CollisionWall = 1; return 0; }
	ShowP_Bullet(P_bulletnumber); return 1;
}

//-----------------------------------------------------------------------------

void P_BulletLaunch() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime - P_BulletLaunchTime > P_BULLETLAUNCHTIMEBUFFER) {
		mciSendCommand(dwIDSE_B, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		P_BulletLaunchTime = CheckedTime;
		if (PlayerWeapon == 0) { PlayGUNSHOOTSound(SOUNDEFFECT_DEFAULTGUN, L"mpegvideo"); P_BulletSpeed = 1.0; }
		else if (PlayerWeapon == 1) { PlayGUNSHOOTSound(SOUNDEFFECT_MACHINEGUN, L"mpegvideo"); P_BulletSpeed = 1.4; }
		else if (PlayerWeapon == 2) { PlayGUNSHOOTSound(SOUNDEFFECT_SHOTGUN, L"mpegvideo"); P_BulletSpeed = 0.8; }
		if (PlayerWeapon == 0 || PlayerWeapon == 1) P_BULLETCOUNTEND += 2;
		else if(PlayerWeapon == 2) P_BULLETCOUNTEND += 4;
	}
}

void InvalidateP_Bullet() {
	if (!CalculateP_BulletTimeBuffer()) {
		for (int i = P_BULLETCOUNTSTART; i <= P_BULLETCOUNTEND; i++) {
			if (!PB[i % BULLETCOUNTLIMIT].BulletActivation && !PB[i % BULLETCOUNTLIMIT].inProgress) {
				P_BulletPositionRenewal(i % BULLETCOUNTLIMIT); PB[i % BULLETCOUNTLIMIT].BulletActivation = PB[i % BULLETCOUNTLIMIT].inProgress = 1; InvalidateP_BulletDamageNModel(i % BULLETCOUNTLIMIT);
				ShowP_Bullet(i % BULLETCOUNTLIMIT);
			}
			if (!MoveP_Bullet_N(i % BULLETCOUNTLIMIT) && i == P_BULLETCOUNTSTART) { ClearSingle_PBulletPosition(i % BULLETCOUNTLIMIT); P_BULLETCOUNTSTART++; }
		}
	}
	else {
		for (int i = P_BULLETCOUNTSTART; i <= P_BULLETCOUNTEND; i++) {
			if (NpcKilledOver) {
				if (DetectCollision_P_BulletwithEnemy(PB[i % BULLETCOUNTLIMIT].P_BULLET_POS_X, PB[i % BULLETCOUNTLIMIT].P_BULLET_POS_Y)) {
					HideP_Bullet(i % BULLETCOUNTLIMIT);
					if (PB[i % BULLETCOUNTLIMIT].BulletActivation) StageEnemyHealth -= P_BULLETDAMAGE; //Enemy가 받는 데미지도 처리
					if (i == P_BULLETCOUNTSTART) { ClearSingle_PBulletPosition(i % BULLETCOUNTLIMIT); P_BULLETCOUNTSTART++; }
					else { PB[i % BULLETCOUNTLIMIT].BulletActivation = 0; PB[i % BULLETCOUNTLIMIT].CollisionEnemy = 1; }
				}
			}
			for (int j = 0; j < NPC_COUNT; j++) {
				if (DetectCollision_P_BulletwithNpc(PB[i % BULLETCOUNTLIMIT].P_BULLET_POS_X, PB[i % BULLETCOUNTLIMIT].P_BULLET_POS_Y, j)) {
					HideP_Bullet(i % BULLETCOUNTLIMIT); 
					if (PB[i % BULLETCOUNTLIMIT].BulletActivation) NpcGetDamagedFromPlayer(j);
					if (i == P_BULLETCOUNTSTART) { ClearSingle_PBulletPosition(i % BULLETCOUNTLIMIT); P_BULLETCOUNTSTART++; }
					else { PB[i % BULLETCOUNTLIMIT].BulletActivation = 0; PB[i % BULLETCOUNTLIMIT].CollisionNpc = 1; PB[i % BULLETCOUNTLIMIT].CollisionEnemy = 1; }
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------

//-------------------------------------플레이어 갱신 함수-------------------------------------------------------
void InvalidatePlayer() {
	ShowPlayer(); 
	if (DetectCollision_PlayerwithItem(ITEM_POS_X, ITEM_POS_Y)) ItemCollisionDetected = 1;
	if (!CalculatePlayerTimeBuffer()) {
		if (kbhit()) {
			if (GetAsyncKeyState(LEFT) & 0x8000) shiftLeft();
			if (GetAsyncKeyState(RIGHT) & 0x8000) shiftRight();
			if (GetAsyncKeyState(UP) & 0x8000) shiftUp();
			if (GetAsyncKeyState(DOWN) & 0x8000) shiftDown();
			if (PlayerWeapon == 1) { if (GetAsyncKeyState(BULLETLAUNCH) & 0x8000) P_BulletLaunch(); }
			else { if (GetAsyncKeyState(BULLETLAUNCH) & 0x0001) P_BulletLaunch(); }
			if (GetAsyncKeyState(SKILLACTIVE) & 0x0001) ActivateSkillItem();
			if (GetAsyncKeyState(SWAP) & 0x0001) SwapItem();
			if (GetAsyncKeyState(QUIT) & 0x0001) GamePause();
		}
	}
	SkillTimeCheck();
	GetDamagedFromEnemy();
}
//--------------------------------------------------------------------------------------------------------------------
#endif // !PLAYER_H