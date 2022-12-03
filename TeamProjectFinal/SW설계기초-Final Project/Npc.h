#pragma once
#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#include "SoundPlay.h"
#ifndef NPC_H
#define NPC_H

//---------------------------------------------------------
//---------------초기화 및 시간계산 함수----------------

//Npc 버퍼 시간 계산 함수
int CalculateNpcTimeBuffer() {
	if (TimeCheckerEnd() - NpcInputTime - PausingTime > NPCTIMEBUFFER / NpcSpeed) { NpcInputTime += NPCTIMEBUFFER / NpcSpeed; return 0; }
	else return 1;
}

//Npc 위치 갱신
void NpcPostionRenewal(int n) { // n = Npc number
	switch (n) {
	case 0:
		npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
		npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 6;
		break;
	case 1:
		npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
		npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 3;
		break;
	case 2:
		npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
		npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2;
		break;
	case 3:
		npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
		npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 6;
		break;
	case 4:
		npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
		npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 3;
		break;
	}
}

//Npc 체력 할당
void InitStageNpcHealth() { for (int i = 0; i < NPC_COUNT; i++) npc[i].life = Npc_Health[StageNumber - 1]; }

//----------------------------------------------------------
//-----------------적 이미지 출력함수--------------------

//Npc 삭제 함수
void HideNpc(int n) {
	for (int i = 0; i < NPCSIZE_H; i++) {
		for (int j = 0; j < NPCSIZE_W; j++) {
			SetCurrentCursorPos(npc[n].NPC_POS_X + j, npc[n].NPC_POS_Y + i);
			if (NpcModel[n][i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(npc[n].NPC_POS_X, npc[n].NPC_POS_Y);
}

//Npc 출력 함수
void ShowNpc(int n) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 + n);
	for (int i = 0; i < NPCSIZE_H; i++) {
		for (int j = 0; j < NPCSIZE_W; j++) {
			SetCurrentCursorPos(npc[n].NPC_POS_X + j, npc[n].NPC_POS_Y + i);
			if (NpcModel[n][i][j] != ' ') printf("%c", NpcModel[n][i][j]);
		}
	}
	SetCurrentCursorPos(npc[n].NPC_POS_X, npc[n].NPC_POS_Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


//Npc 위치 초기화 함수
void ClearNpcPosition() {
	for (int i = 0; i < NPC_COUNT; i++) {
		HideNpc(i);
		NpcPostionRenewal(i);
		npc[i].cnt = npc[i].NpcActivation = npc[i].CollisionPlayer = npc[i].CollisionPbullet = npc[i].CollisionWall = 0; npc[i].life = Npc_Health[StageNumber - 1];
	}
	NpcPatternStart = 0;
	NpcPatternCycle = 0;
	NpcPatternNumber = 0;
	NpcPatternTimeEnded = 1;
	NpcSweepDownChecker = 0;
	NpcIsMoving = 0;
	NPCCOUNT = 0;
	NpcSpeed = 0.2;
}
//Npc 랜덤 패턴 넘버 지정
void SetNpcRandomPatternNumber() {
	NpcPatternNumber = rand() % NPCPATTERNCOUNT + 1;
}

//----------------------------------------------------------
//-------------------충돌검사 함수------------------------

//Npc가 벽에 충돌하였는지 유무 확인 함수
int DetectCollision_NpcwithWall(int x, int y) {
	for (int i = 0; i < NPCSIZE_H; i++) {
		for (int j = 0; j < NPCSIZE_W; j++)
			if (UniBoard[y - GAMEBOARD_ORIGIN_Y + i][x - GAMEBOARD_ORIGIN_X + j] == WALL) return 1;
	}
	return 0;
}
//Npc가 플레이어와 충돌하였는지 유무 확인 함수
int DetectCollision_NpcwithPlayer(int x, int y, int n) {
	if (y == PLAYER_POS_Y) {
		int Modellen;
		if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
		else Modellen = 6;
		for (int i = 0; i < Modellen; i++) {
			for (int j = 0; j < NPCSIZE_H; j++) {
				for (int k = 0; k < NPCSIZE_W; k++) {
					if (NpcModel[n][j][k] != ' ')
						if ((npc[n].NPC_POS_Y + j == PLAYER_POS_Y) && (npc[n].NPC_POS_X + k == PLAYER_POS_X + i)) return 1;
				}
			}
		}
	}
	return 0;
}

//npc데미지 처리함수
void NpcGetDamagedFromPlayer(int n) {
	mciSendCommandW(dwIDSE_NPCD, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	PlayNPCDAMAGEDSound();
	npc[n].life -= P_BULLETDAMAGE;
	if (npc[n].life > 0) return;
	else {
		HideNpc(n); npc[n].NpcActivation = 0; npc[n].CollisionPbullet = 1; npc[n].life = Npc_Health[StageNumber - 1];
		NpcKillCount++;
		NpcPostionRenewal(n);
	}
}

//-------------------------------------------------------------
//-----------------Npc Movement Functions-------------------

//Move Npc to North
int MoveNpc_N(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y - 1)) npc[n].NPC_POS_Y--;
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to NorthWest
int MoveNpc_NW(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 2, npc[n].NPC_POS_Y - 1)) { npc[n].NPC_POS_X -= 2; npc[n].NPC_POS_Y--; }
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to NorthEast
int MoveNpc_NE(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 2, npc[n].NPC_POS_Y - 1)) { npc[n].NPC_POS_X += 2; npc[n].NPC_POS_Y--; }
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to West
int MoveNpc_W(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 2, npc[n].NPC_POS_Y)) npc[n].NPC_POS_X -= 2;
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to SouthWest
int MoveNpc_SW(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 2, npc[n].NPC_POS_Y + 1)) { npc[n].NPC_POS_X -= 2; npc[n].NPC_POS_Y++; }
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to South
int MoveNpc_S(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y + 1)) { npc[n].NPC_POS_Y++; }
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to SouthEast
int MoveNpc_SE(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 2, npc[n].NPC_POS_Y + 1)) { npc[n].NPC_POS_X += 2; npc[n].NPC_POS_Y++; }
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//Move Npc to East
int MoveNpc_E(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//플레이어와 부딪혔으면 npc 비활성화, 플레이어와 부딪혔다는 인디케이터 1로 갱신 0을 리턴하며 종료
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 2, npc[n].NPC_POS_Y)) { npc[n].NPC_POS_X += 2; }
	else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	ShowNpc(n); return 1;
}

//----------------------------------------------------------------------------
//---------------------Npc LaunchTime Set Function----------------------
//When Npc launches record time and set patternnumber, start pattern
void NpcLaunchTime() {
	if (!NpcPatternStart) {	//npc 패턴이 시작되지 않았을 경우
		double CheckedTime = TimeCheckerEnd() - PausingTime;
		if (CheckedTime > NpcPatternEndTime + PATTERNDURATION) {		//체크한 시간이 패턴 종료시간 + durationtime보다 크면 작동
			SetNpcRandomPatternNumber();		//패턴 넘버 결정(랜덤)
			NpcPatternStart = NpcIsMoving = 1; NpcPatternTimeEnded = 0; NpcMovementTiming = NpcPatternStartTime = CheckedTime;	//패턴 시작 인디케이터 1로 갱신, 패턴 시작시간 갱신, Enemy가 움직이고 있다는 인디케이터 1로 갱신
		}
	}
	else return;
}


//------------------------------------------------------------------------
//---------------------Npc Pattern Functions--------------------------

//Npc Pattern HeadButt : 올라갔다가 몸통박치기
int NpcPattern_HeadButt() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_HEADBUTT + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //Pattern Cycle 유무 고민중
	else NpcPatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPostionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//만약 npc 나타나지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 npc 출력
		if (npc[i].NPC_POS_X < GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 15) {
			switch (i) {
			case 0: flag += MoveNpc_E(i); break;
			case 1: flag += MoveNpc_E(i); break;
			case 2: flag += MoveNpc_E(i); break;
			}
		}
		else if (npc[i].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 + 15) {
			switch (i) {
			case 3: flag += MoveNpc_W(i); break;
			case 4: flag += MoveNpc_W(i); break;
			}
		}
		else if (npc[i].NPC_POS_X < GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 8) {
			switch (i) {
			case 0: flag += MoveNpc_NE(i); break;
			case 1: flag += MoveNpc_NE(i); break;
			case 2: flag += MoveNpc_NE(i); break;
			}
		}
		else if (npc[i].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 + 8) {
			switch (i) {
			case 3: flag += MoveNpc_NW(i); break;
			case 4: flag += MoveNpc_NW(i); break;
			}
		}
		else {
			switch (i % 5) {
			case 0: flag += MoveNpc_S(i); break;
			case 1: flag += MoveNpc_S(i); break;
			case 2: flag += MoveNpc_S(i); break;
			case 3: flag += MoveNpc_S(i); break;
			case 4: flag += MoveNpc_S(i); break;
			}
		}
	}
	if (!flag) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Npc Pattern Stairs : 계단식으로 내려옴
int NpcPattern_Stairs() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_STAIRS + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = (++NpcPatternCycle) * 5; //패턴 지속시간일때 패턴사이클 및 bulletcount 증가
	else PatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPostionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//만약 npc 나타나지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 npc 출력
		if (npc[i].NPC_POS_X % 6 < 3) {
			switch (i % 5) {
			case 0: flag += MoveNpc_SE(i); break;
			case 1: flag += MoveNpc_SE(i); break;
			case 2: flag += MoveNpc_SE(i); break;
			case 3: flag += MoveNpc_SW(i); break;
			case 4: flag += MoveNpc_SW(i); break;
			}
		}
		else {
			switch (i % 5) {
			case 0: flag += MoveNpc_E(i); break;
			case 1: flag += MoveNpc_E(i); break;
			case 2: flag += MoveNpc_E(i); break;
			case 3: flag += MoveNpc_W(i); break;
			case 4: flag += MoveNpc_W(i); break;
			}
		}
	}
	if (!flag) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Npc Pattern SweepDown : 오른쪽으로 뭉쳐서 쓸어내리기
int NpcPattern_SweepDown() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_SWEEPDOWN + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //Pattern Cycle 유무 고민중
	else NpcPatternTimeEnded = 1;	//패턴 지속시간 끝날시 patterntimeended 1로 갱신
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPostionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//만약 npc 나타나지 않은 것이라면 초기 위치를 패턴에 맞게 초기화를 시키고 npc 출력
		if (NpcSweepDownChecker) {
			switch (i % 5) {
			case 0: flag += MoveNpc_SW(i); break;
			case 1: flag += MoveNpc_SW(i); break;
			case 2: flag += MoveNpc_SW(i); break;
			case 3: flag += MoveNpc_SW(i); break;
			case 4: flag += MoveNpc_SW(i); break;
			}
		}
		else if (npc[i].NPC_POS_X < GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 + 1) {
			switch (i) {
			case 0: flag += MoveNpc_E(i); break;
			case 1: flag += MoveNpc_E(i); break;
			case 2: flag += MoveNpc_E(i); break;
			}
		}
		else if (npc[0].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2) {
			NpcSweepDownChecker = 1;
		}
	}
	if (!flag) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}



//--------------------------------------------------------------
//-------------------Invalidation 함수-------------------------

//npc 갱신 함수
void InvalidateNpc() {
	if (!CalculateNpcTimeBuffer()) {
		if (!GamePaused) {		//Game이 Paused되지 않았을 때 bullet의 상태 및 위치 갱신
			NpcLaunchTime();	//패턴 시작시간 및 패턴 결정
			if (NpcPatternStart) {
				switch (NpcPatternNumber) {	//패턴 넘버에 따라 다른 함수 작동
				case 1: if (NpcPattern_Stairs()) ClearNpcPosition(); break;
				case 2: if (NpcPattern_HeadButt()) ClearNpcPosition(); break;
				case 3: if (NpcPattern_SweepDown()) ClearNpcPosition(); break;
				default: break;
				}
			}
			else return;
		}
	}
}
#endif // !NPC_H