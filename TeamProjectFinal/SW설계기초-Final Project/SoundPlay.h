#pragma once
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <Digitalv.h>
#include "VariableSets.h"
#include "Timer.h"
#ifndef SOUNDPLAY_H
#define SOUNDPLAY_H

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openDamageSound;
MCI_PLAY_PARMS playDamageSound;

#define BGM "C:\\Users\\bange\\OneDrive\\바탕 화면\\Documents\\GitHub\\새 폴더\\TeamProjectFinal\\BGM.mp3"	//BGM 파일 확장명
#define DAMAGE "C:\\사용자\\bange\\OneDrive\\바탕 화면\\Documents\\GitHub\\새 폴더\\TeamProjectFinal\\GameResource\\Explosion.mp3"		//DAMAGE 효과음 확장명
//#define CLEAR ""		//게임 클리어 시 들어가는 Clear 효과음 확장명

int dwID;
void PlayBgm() {
	openBgm.lpstrElementName = BGM;
	openBgm.lpstrDeviceType = "mpegvideo";    //mp3 형식, wav 형식이면 "waveaudio" 작성
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playBgm);    //음악 반복 재생
}
void PlayDamageSound() {
	openDamageSound.lpstrElementName = DAMAGE;    //파일 오픈
	openDamageSound.lpstrDeviceType = "mpegvideo";    //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDamageSound);
	dwID = openDamageSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openDamageSound);    //음악을 한 번 재생
	if (TimeCheckerEnd() - PausingTime - CollisionTime > 0.8)
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //음원 재생 위치를 처음으로 초기화
}
#endif // !SOUNDPLAY_H
