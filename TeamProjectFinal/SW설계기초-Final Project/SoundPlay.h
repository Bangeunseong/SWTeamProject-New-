#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <Digitalv.h>
#include "VariableSets.h"
#include "Timer.h"
#ifndef SOUNDPLAY_H
#define SOUNDPLAY_H

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openDamageSound;
MCI_PLAY_PARMS playDamageSound;
MCI_OPEN_PARMS openBulletSound;
MCI_PLAY_PARMS playBulletSound;
#define BGM L"BGM.mp3"	//BGM
#define SOUNDEFFECT_COLLISION L"EXPLOSION.WAV"		//DAMAGE 효과음
#define SOUNDEFFECT_SHOOTBULLET L"SHOOTBULLET.mp3"
//#define CLEAR ""		//게임 클리어 시 들어가는 Clear 효과음 확장명

UINT dwID;

void PlayBGMSound() {
	openBgm.lpstrElementName = BGM;
	openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 형식, wav 형식이면 "waveaudio" 작성
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommandW(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playBgm);    //음악 반복 재생
}

UINT dwIDSE_D;

void PlayCOLLISIONSound() {
	openDamageSound.lpstrElementName = SOUNDEFFECT_COLLISION;    //파일 오픈
	openDamageSound.lpstrDeviceType = L"waveaudio";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDamageSound);
	dwIDSE_D = openDamageSound.wDeviceID;
	mciSendCommandW(dwIDSE_D, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playDamageSound);    //음악을 한 번 재생
}

UINT dwIDSE_B;

void PlaySHOOTBULLETSound() {
	openBulletSound.lpstrElementName = SOUNDEFFECT_SHOOTBULLET;    //파일 오픈
	openBulletSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBulletSound);
	dwIDSE_B = openBulletSound.wDeviceID;
	mciSendCommandW(dwIDSE_B, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playBulletSound);    //음악을 한 번 재생
}
#endif // !SOUNDPLAY_H