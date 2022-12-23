#pragma once
#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "ExpItem.h"
#include "WeaponItem.h"
#include "Timer.h"
#include "SoundPlay.h"
#ifndef NPC_H
#define NPC_H

//---------------------------------------------------------
//---------------�ʱ�ȭ �� �ð���� �Լ�----------------

//Npc ���� �ð� ��� �Լ�
int CalculateNpcTimeBuffer() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime - NpcInputTime> NPCTIMEBUFFER / NpcSpeed) { NpcInputTime = CheckedTime; return 0; }
	else return 1;
}

//Npc ��ġ ����
void NpcPositionRenewal(int n) { // n = Npc number
	if (NpcPatternNumber == 5) {	//NpcPattern-SpiralMove�϶��� ����
		npc[n].destinationX = npc[n].destinationY = npc[n].arrived = 0;
		switch (n) {
		case 0:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = rand() % (GAMEBOARD_COLUMN - 30) + GAMEBOARD_ORIGIN_Y + 6;
			npc[n].distance = rand() % (GAMEBOARD_ROW / 2 - 30) + 6;
			break;
		case 1:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = rand() % (GAMEBOARD_COLUMN - 20) + GAMEBOARD_ORIGIN_Y + 6;
			npc[n].distance = rand() % (GAMEBOARD_ROW / 2 - 30) + 6;
			break;
		case 2:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = rand() % (GAMEBOARD_COLUMN - 20) + GAMEBOARD_ORIGIN_Y + 6;
			npc[n].distance = rand() % (GAMEBOARD_ROW / 2 - 30) + 6;
			break;
		case 3:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
			npc[n].NPC_POS_Y = rand() % (GAMEBOARD_COLUMN - 20) + GAMEBOARD_ORIGIN_Y + 6;
			npc[n].distance = rand() % (GAMEBOARD_ROW / 2 - 30) + 6;
			break;
		case 4:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
			npc[n].NPC_POS_Y = rand() % (GAMEBOARD_COLUMN - 20) + GAMEBOARD_ORIGIN_Y + 6;
			npc[n].distance = rand() % (GAMEBOARD_ROW / 2 - 30) + 6;
			break;
		}
	}
	else if (NpcPatternNumber == 6) {
		npc[n].BounceCount = 0;
		switch (n) {
		case 0:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 5;
			npc[n].Direction = SOUTH_EAST;// �߰� : �Ʒ� ������ �밢������ �̵� - �ʱ⼼��
			break;
		case 1:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 3;
			npc[n].Direction = SOUTH_EAST;// �߰� : �Ʒ� ������ �밢������ �̵�
			break;
		case 2:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2;
			npc[n].Direction = SOUTH_EAST;// �߰� : �Ʒ� ������ �밢������ �̵�
			break;
		case 3:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 5;
			npc[n].Direction = SOUTH_WEST;// �߰� : �Ʒ� ���� �밢������ �̵�
			break;
		case 4:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 3;
			npc[n].Direction = SOUTH_WEST;// �߰� : �Ʒ� ���� �밢������ �̵�
			break;
		}
	}
	else {
		switch (n) {
		case 0:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + 2;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 5;
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
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 5;
			break;
		case 4:
			npc[n].NPC_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
			npc[n].NPC_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 3;
			break;
		}
	}
}

//Npc ü�� �Ҵ�
void InitStageNpcHealth() { for (int i = 0; i < NPC_COUNT; i++) npc[i].life = Npc_Health[StageNumber - 1]; }

//----------------------------------------------------------
//-----------------�� �̹��� ����Լ�--------------------

//Npc ���� �Լ�
void HideNpc(int n) {
	for (int i = 0; i < NPCSIZE_H; i++) {
		for (int j = 0; j < NPCSIZE_W; j++) {
			SetCurrentCursorPos(npc[n].NPC_POS_X + j, npc[n].NPC_POS_Y + i);
			if (NpcModel[n][i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(npc[n].NPC_POS_X, npc[n].NPC_POS_Y);
}

//Npc ��� �Լ�
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


//Npc ��ġ �ʱ�ȭ �Լ�
void ClearNpcPosition() {
	for (int i = 0; i < NPC_COUNT; i++) {
		HideNpc(i);
		NpcPositionRenewal(i);
		npc[i].distance = npc[i].Movecount = npc[i].NpcActivation = npc[i].CollisionPlayer = npc[i].CollisionPbullet = npc[i].CollisionWall = 0;
		npc[i].BounceCount = npc[i].Direction = 0;
		npc[i].life = Npc_Health[StageNumber - 1];
	}
	NpcPatternStart = 0;
	NpcPatternCycle = 0;
	NpcPatternNumber = 0;
	NpcPatternTimeEnded = 1;
	NpcSweepDownChecker = 0;
	NpcIsMoving = NPC_COUNT;
	NPCCOUNT = 0;
}

//Npc ���� ���� �ѹ� ����
void SetNpcRandomPatternNumber() {
	if (StageNumber < 2) NpcPatternNumber = rand() % (NPCPATTERNCOUNT - 3) + 1;
	else if(StageNumber < 3) rand() % (NPCPATTERNCOUNT - 2) + 1;
	else rand() % NPCPATTERNCOUNT + 1;
}

//----------------------------------------------------------
//-------------------�浹�˻� �Լ�------------------------

//Npc�� ���� �浹�Ͽ����� ���� Ȯ�� �Լ�
int DetectCollision_NpcwithWall(int x, int y) {
	for (int i = 0; i < NPCSIZE_H; i++) {
		for (int j = 0; j < NPCSIZE_W; j++)
			if (UniBoard[y - GAMEBOARD_ORIGIN_Y + i][x - GAMEBOARD_ORIGIN_X + j] == WALL) { NpcIsMoving--; return 1; }
	}
	return 0;
}
//Npc�� �÷��̾�� �浹�Ͽ����� ���� Ȯ�� �Լ�
int DetectCollision_NpcwithPlayer(int x, int y, int n) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;

	int flag = 0; int index;
	for (int i = 0; i < NPCSIZE_H; i++) { if (npc[n].NPC_POS_Y + i == PLAYER_POS_Y) { index = i; flag = 1; break; } }
	if (!flag) return 0;

	for (int i = 0; i < Modellen; i++) {
		for (int j = 0; j < NPCSIZE_W; j++) {
			if (NpcModel[n][index][j] != ' ')
				if (npc[n].NPC_POS_X + j == PLAYER_POS_X + i) { NpcIsMoving--; return 1; }
		}
	}
	return 0;
}

//npc������ ó���Լ�
void NpcGetDamagedFromPlayer(int n, int P_bulletnumber) {
	npc[n].life -= PB[P_bulletnumber].BulletDamage;
	if (npc[n].life > 0) return;
	else {
		mciSendCommandW(dwIDSE_NPCD, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		PlayNPCDAMAGEDSound();
		int ran_N = rand() % 100;
		HideNpc(n);
		if (ran_N >= 0 && ran_N < 20) CreateExp(n);	//0 2 4 6 8 �϶� ����ġ ����
		else if (ran_N >= 20 && ran_N < 30) CreateWeaponItem(n);
		npc[n].NpcActivation = 0; npc[n].CollisionPbullet = 1; npc[n].life = Npc_Health[StageNumber - 1];
		NpcKillCount++; NpcIsMoving--;
		NpcPositionRenewal(n);
	}
}

//-------------------------------------------------------------
//-----------------Npc Movement Functions-------------------

//Move Npc to North
int MoveNpc_N(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y - 1)) npc[n].NPC_POS_Y--;
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			switch (rand() % 3) {
			case 0: npc[n].Direction = SOUTH_EAST; break;
			case 1: npc[n].Direction = SOUTH; break;
			case 2: npc[n].Direction = SOUTH_WEST; break;
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to NorthWest
int MoveNpc_NW(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 1, npc[n].NPC_POS_Y - 1)) { npc[n].NPC_POS_X--; npc[n].NPC_POS_Y--; }
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			int flag1 = 0, flag2 = 0;
			if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y - 1)) { flag1 = 1; }
			else if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 1, npc[n].NPC_POS_Y)) { flag2 = 1; }

			if (flag1 && flag2) npc[n].Direction = SOUTH_EAST;
			else if (flag1) {
				switch (rand() % 3) {
				case 0: npc[n].Direction = SOUTH_EAST; break;
				case 1: npc[n].Direction = SOUTH; break;
				case 2: npc[n].Direction = SOUTH_WEST; break;
				}
			}
			else {
				switch (rand() % 3) {
				case 0: npc[n].Direction = NORTH_WEST; break;
				case 1: npc[n].Direction = EAST; break;
				case 2: npc[n].Direction = SOUTH_EAST; break;
				}
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to NorthEast
int MoveNpc_NE(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 1, npc[n].NPC_POS_Y - 1)) { npc[n].NPC_POS_X++; npc[n].NPC_POS_Y--; }
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			int flag1 = 0, flag2 = 0;
			if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y - 1)) { flag1 = 1; }
			else if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 1, npc[n].NPC_POS_Y)) { flag2 = 1; }

			if (flag1 && flag2) npc[n].Direction = SOUTH_WEST;
			else if (flag1) {
				switch (rand() % 3) {
				case 0: npc[n].Direction = SOUTH_EAST; break;
				case 1: npc[n].Direction = SOUTH; break;
				case 2: npc[n].Direction = SOUTH_WEST; break;
				}
			}
			else {
				switch (rand() % 3) {
				case 0: npc[n].Direction = NORTH_WEST; break;
				case 1: npc[n].Direction = WEST; break;
				case 2: npc[n].Direction = SOUTH_WEST; break;
				}
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to West
int MoveNpc_W(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 1, npc[n].NPC_POS_Y)) npc[n].NPC_POS_X--;
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			switch (rand() % 3) {
			case 0: npc[n].Direction = NORTH_EAST; break;
			case 1: npc[n].Direction = EAST; break;
			case 2: npc[n].Direction = SOUTH_EAST; break;
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to SouthWest
int MoveNpc_SW(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 1, npc[n].NPC_POS_Y + 1)) { npc[n].NPC_POS_X--; npc[n].NPC_POS_Y++; }
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			int flag1 = 0, flag2 = 0;
			if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y + 1)) { flag1 = 1; }
			else if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X - 1, npc[n].NPC_POS_Y)) { flag2 = 1; }

			if (flag1 && flag2) npc[n].Direction = NORTH_EAST;
			else if (flag1) {
				switch (rand() % 3) {
				case 0: npc[n].Direction = NORTH_EAST; break;
				case 1: npc[n].Direction = NORTH; break;
				case 2: npc[n].Direction = NORTH_WEST; break;
				}
			}
			else {
				switch (rand() % 3) {
				case 0: npc[n].Direction = NORTH_EAST; break;
				case 1: npc[n].Direction = EAST; break;
				case 2: npc[n].Direction = SOUTH_EAST; break;
				}
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to South
int MoveNpc_S(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y + 1)) { npc[n].NPC_POS_Y++; }
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			switch (rand() % 3) {
			case 0: npc[n].Direction = NORTH_EAST; break;
			case 1: npc[n].Direction = NORTH; break;
			case 2: npc[n].Direction = NORTH_WEST; break;
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to SouthEast
int MoveNpc_SE(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 1, npc[n].NPC_POS_Y + 1)) { npc[n].NPC_POS_X++; npc[n].NPC_POS_Y++; }
	else { 
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			int flag1 = 0, flag2 = 0;
			if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X, npc[n].NPC_POS_Y + 1)) { flag1 = 1; }
			else if (DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 1, npc[n].NPC_POS_Y)) { flag2 = 1; }

			if (flag1 && flag2) npc[n].Direction = NORTH_WEST;
			else if (flag1) {
				switch (rand() % 3) {
				case 0: npc[n].Direction = NORTH_EAST; break;
				case 1: npc[n].Direction = NORTH; break;
				case 2: npc[n].Direction = NORTH_WEST; break;
				}
			}
			else {
				switch (rand() % 3) {
				case 0: npc[n].Direction = NORTH_WEST; break;
				case 1: npc[n].Direction = WEST; break;
				case 2: npc[n].Direction = SOUTH_WEST; break;
				}
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//Move Npc to East
int MoveNpc_E(int n) {
	if (!npc[n].NpcActivation) return 0;

	HideNpc(n);
	if (DetectCollision_NpcwithPlayer(npc[n].NPC_POS_X, npc[n].NPC_POS_Y, n)) { npc[n].NpcActivation = 0; npc[n].CollisionPlayer = 1; return 0; }//�÷��̾�� �ε������� npc ��Ȱ��ȭ, �÷��̾�� �ε����ٴ� �ε������� 1�� ���� 0�� �����ϸ� ����
	if (!DetectCollision_NpcwithWall(npc[n].NPC_POS_X + 1, npc[n].NPC_POS_Y)) { npc[n].NPC_POS_X++; }
	else {
		if (NpcPatternNumber == 6 && npc[n].BounceCount < NPC_BOUNCECOUNT) {
			switch (rand() % 3) {
			case 0: npc[n].Direction = NORTH_WEST; break;
			case 1: npc[n].Direction = WEST; break;
			case 2: npc[n].Direction = SOUTH_WEST; break;
			}
			npc[n].BounceCount++;
		}
		else { npc[n].NpcActivation = 0; npc[n].CollisionWall = 1; return 0; }
	}
	ShowNpc(n); return 1;
}

//----------------------------------------------------------------------------
//---------------------Npc LaunchTime Set Function----------------------
//When Npc launches record time and set patternnumber, start pattern
void NpcLaunchTime() {
	if (!NpcPatternStart) {	//npc ������ ���۵��� �ʾ��� ���
		double CheckedTime = TimeCheckerEnd() - PausingTime;
		if (CheckedTime > NpcPatternEndTime + PATTERNDURATION) {		//üũ�� �ð��� ���� ����ð� + durationtime���� ũ�� �۵�
			SetNpcRandomPatternNumber();		//���� �ѹ� ����(����)
			NpcPatternStart = NpcIsMoving = NPC_COUNT; NpcPatternTimeEnded = 0; NpcMovementTiming = NpcPatternStartTime = CheckedTime;	//���� ���� �ε������� 1�� ����, ���� ���۽ð� ����, Enemy�� �����̰� �ִٴ� �ε������� 1�� ����
		}
	}
	else return;
}


//------------------------------------------------------------------------
//---------------------Npc Pattern Functions--------------------------

//Npc Pattern HeadButt : �ö󰬴ٰ� �����ġ��
int NpcPattern_HeadButt() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_HEADBUTT + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //Pattern Cycle ���� �����
	else NpcPatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPositionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//���� npc ��Ÿ���� ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� npc ���
		if (npc[i].NPC_POS_X < GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 15) {
			switch (i) {
			case 0: MoveNpc_E(i); break;
			case 1: MoveNpc_E(i); break;
			case 2: MoveNpc_E(i); break;
			}
		}
		else if (npc[i].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 + 15) {
			switch (i) {
			case 3: MoveNpc_W(i); break;
			case 4: MoveNpc_W(i); break;
			}
		}
		else if (npc[i].NPC_POS_X < GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 8) {
			switch (i) {
			case 0: MoveNpc_NE(i); break;
			case 1: MoveNpc_NE(i); break;
			case 2: MoveNpc_NE(i); break;
			}
		}
		else if (npc[i].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 + 8) {
			switch (i) {
			case 3: MoveNpc_NW(i); break;
			case 4: MoveNpc_NW(i); break;
			}
		}
		else {
			switch (i % 5) {
			case 0: MoveNpc_S(i); break;
			case 1: MoveNpc_S(i); break;
			case 2: MoveNpc_S(i); break;
			case 3: MoveNpc_S(i); break;
			case 4: MoveNpc_S(i); break;
			}
		}
		flag += npc[i].NpcActivation;
	}
	if (!flag || !NpcIsMoving) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Npc Pattern Stairs : ��ܽ����� ������
int NpcPattern_Stairs() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_STAIRS + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = (++NpcPatternCycle) * 5; //���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
	else PatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPositionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//���� npc ��Ÿ���� ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� npc ���
		if (npc[i].NPC_POS_X % 6 < 3) {
			switch (i % 5) {
			case 0: MoveNpc_SE(i); break;
			case 1: MoveNpc_SE(i); break;
			case 2: MoveNpc_SE(i); break;
			case 3: MoveNpc_SW(i); break;
			case 4: MoveNpc_SW(i); break;
			}
		}
		else {
			switch (i % 5) {
			case 0: MoveNpc_E(i); break;
			case 1: MoveNpc_E(i); break;
			case 2: MoveNpc_E(i); break;
			case 3: MoveNpc_W(i); break;
			case 4: MoveNpc_W(i); break;
			}
		}
		flag += npc[i].NpcActivation;
	}
	if (!flag || !NpcIsMoving) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

//Npc Pattern SweepDown : ���������� ���ļ� �������
int NpcPattern_SweepDown() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_SWEEPDOWN + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //Pattern Cycle ���� �����
	else NpcPatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPositionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//���� npc ��Ÿ���� ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� npc ���
		if (NpcSweepDownChecker) {
			switch (i % 5) {
			case 0: MoveNpc_SW(i); break;
			case 1: MoveNpc_SW(i); break;
			case 2: MoveNpc_SW(i); break;
			case 3: MoveNpc_SW(i); break;
			case 4: MoveNpc_SW(i); break;
			}
		}
		else if (npc[i].NPC_POS_X < GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 + 1) {
			switch (i) {
			case 0: MoveNpc_E(i); break;
			case 1: MoveNpc_E(i); break;
			case 2: MoveNpc_E(i); break;
			}
		}
		else if (npc[0].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 || npc[1].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 || npc[2].NPC_POS_X > GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 || (!npc[0].NpcActivation && !npc[1].NpcActivation && !npc[2].NpcActivation)) {
			NpcSweepDownChecker = 1;
		}
		flag += npc[i].NpcActivation;
	}
	if (!flag || !NpcIsMoving) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

int NpcPattern_Tracking() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_TRACKING + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //Pattern Cycle ���� �����
	else NpcPatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPositionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//���� npc ��Ÿ���� ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� npc ���
		if (npc[i].NPC_POS_Y > PLAYER_POS_Y) {
			switch (i) {
			case 0: flag += MoveNpc_N(i); break;
			case 1: flag += MoveNpc_N(i); break;
			case 2: flag += MoveNpc_N(i); break;
			case 3: flag += MoveNpc_N(i); break;
			case 4: flag += MoveNpc_N(i); break;
			}
		}
		else if (npc[i].NPC_POS_Y > PLAYER_POS_Y && npc[i].NPC_POS_X < PLAYER_POS_X - 5) {
			switch (i) {
			case 0: flag += MoveNpc_E(i); break;
			case 1: flag += MoveNpc_NE(i); break;
			case 2: flag += MoveNpc_E(i); break;
			case 3: flag += MoveNpc_NE(i); break;
			case 4: flag += MoveNpc_E(i); break;
			}
		}
		else if (npc[i].NPC_POS_Y > PLAYER_POS_Y && npc[i].NPC_POS_X > PLAYER_POS_X + 5) {
			switch (i) {
			case 0: flag += MoveNpc_NW(i); break;
			case 1: flag += MoveNpc_N(i); break;
			case 2: flag += MoveNpc_NW(i); break;
			case 3: flag += MoveNpc_N(i); break;
			case 4: flag += MoveNpc_NW(i); break;
			}
		}
		else if (npc[i].NPC_POS_X < PLAYER_POS_X - 5) {
			switch (i) {
			case 0: flag += MoveNpc_SE(i); break;
			case 1: flag += MoveNpc_E(i); break;
			case 2: flag += MoveNpc_SE(i); break;
			case 3: flag += MoveNpc_E(i); break;
			case 4: flag += MoveNpc_SE(i); break;
			}
		}
		else if (npc[i].NPC_POS_X > PLAYER_POS_X + 5) {
			switch (i) {
			case 0: flag += MoveNpc_W(i); break;
			case 1: flag += MoveNpc_SW(i); break;
			case 2: flag += MoveNpc_W(i); break;
			case 3: flag += MoveNpc_SW(i); break;
			case 4: flag += MoveNpc_W(i); break;
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
	if (!flag || !NpcIsMoving) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

int NpcPattern_SpiralMove() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_SPIRALMOVE + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //Pattern Cycle ���� �����
	else NpcPatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPositionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//���� npc ��Ÿ���� ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� npc ���
		switch (i) {
		case 0:
			if (npc[i].Movecount < npc[i].distance) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance && npc[i].Movecount < npc[i].distance + 2) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance + 2 && npc[i].Movecount < npc[i].distance + 4) MoveNpc_NE(i);
			else if (npc[i].Movecount >= npc[i].distance + 4 && npc[i].Movecount < npc[i].distance + 6) MoveNpc_N(i);
			else if (npc[i].Movecount >= npc[i].distance + 6 && npc[i].Movecount < npc[i].distance + 8) MoveNpc_NW(i);
			else if (npc[i].Movecount >= npc[i].distance + 8 && npc[i].Movecount < npc[i].distance + 10) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance + 10 && npc[i].Movecount < npc[i].distance + 12) MoveNpc_SW(i);
			else {
				if (!npc[i].destinationX && !npc[i].destinationY) { npc[i].destinationX = PLAYER_POS_X; npc[i].destinationY = PLAYER_POS_Y; }
				if (!npc[i].arrived) {
					if (npc[i].NPC_POS_X < npc[i].destinationX) MoveNpc_E(i);
					else if (npc[i].NPC_POS_X > npc[i].destinationX) MoveNpc_W(i);
					if (npc[i].NPC_POS_Y < npc[i].destinationY) MoveNpc_S(i);
					else if (npc[i].NPC_POS_Y > npc[i].destinationY) MoveNpc_N(i);
					if (npc[i].destinationX == npc[i].NPC_POS_X && npc[i].destinationY == npc[i].NPC_POS_Y) npc[i].arrived = 1;
				}
				else MoveNpc_NW(i);
			}
			npc[i].Movecount++; break;
		case 1:
			if (npc[i].Movecount < npc[i].distance) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance && npc[i].Movecount < npc[i].distance + 2) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance + 2 && npc[i].Movecount < npc[i].distance + 4) MoveNpc_NE(i);
			else if (npc[i].Movecount >= npc[i].distance + 4 && npc[i].Movecount < npc[i].distance + 6) MoveNpc_N(i);
			else if (npc[i].Movecount >= npc[i].distance + 6 && npc[i].Movecount < npc[i].distance + 8) MoveNpc_NW(i);
			else if (npc[i].Movecount >= npc[i].distance + 8 && npc[i].Movecount < npc[i].distance + 10) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance + 10 && npc[i].Movecount < npc[i].distance + 12) MoveNpc_SW(i);
			else {
				if (!npc[i].destinationX && !npc[i].destinationY) { npc[i].destinationX = PLAYER_POS_X; npc[i].destinationY = PLAYER_POS_Y; }
				if (!npc[i].arrived) {
					if (npc[i].NPC_POS_X < npc[i].destinationX) MoveNpc_E(i);
					else if (npc[i].NPC_POS_X > npc[i].destinationX) MoveNpc_W(i);
					if (npc[i].NPC_POS_Y < npc[i].destinationY) MoveNpc_S(i);
					else if (npc[i].NPC_POS_Y > npc[i].destinationY) MoveNpc_N(i);
					if (npc[i].destinationX == npc[i].NPC_POS_X && npc[i].destinationY == npc[i].NPC_POS_Y) npc[i].arrived = 1;
				}
				else MoveNpc_NE(i);
			}
			npc[i].Movecount++; break;
		case 2:
			if (npc[i].Movecount < npc[i].distance) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance && npc[i].Movecount < npc[i].distance + 2) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance + 2 && npc[i].Movecount < npc[i].distance + 4) MoveNpc_NE(i);
			else if (npc[i].Movecount >= npc[i].distance + 4 && npc[i].Movecount < npc[i].distance + 6) MoveNpc_N(i);
			else if (npc[i].Movecount >= npc[i].distance + 6 && npc[i].Movecount < npc[i].distance + 8) MoveNpc_NW(i);
			else if (npc[i].Movecount >= npc[i].distance + 8 && npc[i].Movecount < npc[i].distance + 10) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance + 10 && npc[i].Movecount < npc[i].distance + 12) MoveNpc_SW(i);
			else {
				if (!npc[i].destinationX && !npc[i].destinationY) { npc[i].destinationX = PLAYER_POS_X; npc[i].destinationY = PLAYER_POS_Y; }
				if (!npc[i].arrived) {
					if (npc[i].NPC_POS_X < npc[i].destinationX) MoveNpc_E(i);
					else if (npc[i].NPC_POS_X > npc[i].destinationX) MoveNpc_W(i);
					if (npc[i].NPC_POS_Y < npc[i].destinationY) MoveNpc_S(i);
					else if (npc[i].NPC_POS_Y > npc[i].destinationY) MoveNpc_N(i);
					if (npc[i].destinationX == npc[i].NPC_POS_X && npc[i].destinationY == npc[i].NPC_POS_Y) npc[i].arrived = 1;
				}
				else MoveNpc_SW(i);
			}
			npc[i].Movecount++; break;
		case 3:
			if (npc[i].Movecount < npc[i].distance) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance && npc[i].Movecount < npc[i].distance + 2) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance + 2 && npc[i].Movecount < npc[i].distance + 4) MoveNpc_NW(i);
			else if (npc[i].Movecount >= npc[i].distance + 4 && npc[i].Movecount < npc[i].distance + 6) MoveNpc_NE(i);
			else if (npc[i].Movecount >= npc[i].distance + 6 && npc[i].Movecount < npc[i].distance + 8) MoveNpc_NE(i);
			else if (npc[i].Movecount >= npc[i].distance + 8 && npc[i].Movecount < npc[i].distance + 10) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance + 10 && npc[i].Movecount < npc[i].distance + 12) MoveNpc_SE(i);
			else {
				if (!npc[i].destinationX && !npc[i].destinationY) { npc[i].destinationX = PLAYER_POS_X; npc[i].destinationY = PLAYER_POS_Y; }
				if (!npc[i].arrived) {
					if (npc[i].NPC_POS_X < npc[i].destinationX) MoveNpc_E(i);
					else if (npc[i].NPC_POS_X > npc[i].destinationX) MoveNpc_W(i);
					if (npc[i].NPC_POS_Y < npc[i].destinationY) MoveNpc_S(i);
					else if (npc[i].NPC_POS_Y > npc[i].destinationY) MoveNpc_N(i);
					if (npc[i].destinationX == npc[i].NPC_POS_X && npc[i].destinationY == npc[i].NPC_POS_Y) npc[i].arrived = 1;
				}
				else MoveNpc_SE(i);
			}
			npc[i].Movecount++; break;
		case 4:
			if (npc[i].Movecount < npc[i].distance) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance && npc[i].Movecount < npc[i].distance + 2) MoveNpc_W(i);
			else if (npc[i].Movecount >= npc[i].distance + 2 && npc[i].Movecount < npc[i].distance + 4) MoveNpc_NW(i);
			else if (npc[i].Movecount >= npc[i].distance + 4 && npc[i].Movecount < npc[i].distance + 6) MoveNpc_N(i);
			else if (npc[i].Movecount >= npc[i].distance + 6 && npc[i].Movecount < npc[i].distance + 8) MoveNpc_NE(i);
			else if (npc[i].Movecount >= npc[i].distance + 8 && npc[i].Movecount < npc[i].distance + 10) MoveNpc_E(i);
			else if (npc[i].Movecount >= npc[i].distance + 10 && npc[i].Movecount < npc[i].distance + 12) MoveNpc_SE(i);
			else {
				if (!npc[i].destinationX && !npc[i].destinationY) { npc[i].destinationX = PLAYER_POS_X; npc[i].destinationY = PLAYER_POS_Y; }
				if (!npc[i].arrived) {
					if (npc[i].NPC_POS_X < npc[i].destinationX) MoveNpc_E(i);
					else if (npc[i].NPC_POS_X > npc[i].destinationX) MoveNpc_W(i);
					if (npc[i].NPC_POS_Y < npc[i].destinationY) MoveNpc_S(i);
					else if (npc[i].NPC_POS_Y > npc[i].destinationY) MoveNpc_N(i);
					if (npc[i].destinationX == npc[i].NPC_POS_X && npc[i].destinationY == npc[i].NPC_POS_Y) npc[i].arrived = 1;
				}
				else MoveNpc_S(i);
			}
			npc[i].Movecount++; break;
		}
	}
	if (!flag || !NpcIsMoving) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }
	return 0;
}

int NpcPattern_Random() {
	int flag = 0;
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime < NPC_PATTERNTIME_RANDOMEDIRECTION + NpcPatternStartTime && CheckedTime > NpcPatternStartTime) NPCCOUNT = 5; //���� ���ӽð��϶� ���ϻ���Ŭ �� bulletcount ����
	else NpcPatternTimeEnded = 1;	//���� ���ӽð� ������ patterntimeended 1�� ����
	for (int i = 0; i < 5; i++) {
		if (!npc[i].NpcActivation && !npc[i].CollisionPlayer && !npc[i].CollisionWall && !npc[i].CollisionPbullet) { NpcPositionRenewal(i); npc[i].NpcActivation = 1; ShowNpc(i); }	//���� npc ��Ÿ���� ���� ���̶�� �ʱ� ��ġ�� ���Ͽ� �°� �ʱ�ȭ�� ��Ű�� npc ���
		switch (npc[i].Direction) {
		case NORTH_EAST: MoveNpc_NE(i); break;
		case NORTH: MoveNpc_N(i); break;
		case NORTH_WEST:	MoveNpc_NW(i); break;
		case SOUTH_EAST: MoveNpc_SE(i); break;
		case SOUTH: MoveNpc_S(i); break;
		case SOUTH_WEST: MoveNpc_SW(i); break;
		case EAST: MoveNpc_E(i); break;
		case WEST: MoveNpc_W(i); break;
		}
		flag += npc[i].NpcActivation;
	}
	if (!flag || !NpcIsMoving) { NpcPatternEndTime = TimeCheckerEnd() - PausingTime; return 1; }// NpcIsMoving ������ ���δ�. �̰� ����ٸ�?
	return 0;
}

//--------------------------------------------------------------
//-------------------Invalidation �Լ�-------------------------

//npc ���� �Լ�
void InvalidateNpc() {
	if (!CalculateNpcTimeBuffer()) {
		if (!GamePaused) {		//Game�� Paused���� �ʾ��� �� bullet�� ���� �� ��ġ ����
			NpcLaunchTime();	//���� ���۽ð� �� ���� ����
			if (NpcPatternStart) {
				switch (NpcPatternNumber) {	//���� �ѹ��� ���� �ٸ� �Լ� �۵�
				case 1: if (NpcPattern_Stairs()) ClearNpcPosition(); break;
				case 2: if (NpcPattern_HeadButt()) ClearNpcPosition(); break;
				case 3: if (NpcPattern_SweepDown()) ClearNpcPosition(); break;
				case 4: if (NpcPattern_Tracking()) ClearNpcPosition(); break;
				case 5: if (NpcPattern_SpiralMove()) ClearNpcPosition(); break;
				case 6: if(NpcPattern_Random()) ClearNpcPosition(); break;
				default: break;
				}
			}
			else return;
		}
	}
}
#endif // !NPC_H