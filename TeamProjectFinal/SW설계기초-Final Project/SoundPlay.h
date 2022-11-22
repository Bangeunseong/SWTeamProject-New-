#pragma once
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include <Digitalv.h>
#ifndef SOUNDPLAY_H
#define SOUNDPLAY_H

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openDamageSound;
MCI_PLAY_PARMS playDamageSound;

#define BGM ""	//BGM 파일 확장명
#define DAMAGE ""		//DAMAGE 효과음 확장명
#define CLEAR ""		//Clear 효과음 확장명

int dwID;

void PlayBgm(void) {
	openBgm.lpstrElementName = LPCWSTR(BGM);            //파일 오픈
	openBgm.lpstrDeviceType = LPCWSTR("mpegvideo");    //mp3 형식, wav 형식이면 "waveaudio" 작성
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);    //음악 반복 재생
}

#endif // !SOUNDPLAY_H
