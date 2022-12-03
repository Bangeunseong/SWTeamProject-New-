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
MCI_OPEN_PARMS openNpcSound;
MCI_PLAY_PARMS playNpcSound;
MCI_OPEN_PARMS openBulletSound;
MCI_PLAY_PARMS playBulletSound;
MCI_OPEN_PARMS openMissionCompleteSound;
MCI_PLAY_PARMS playMissionCompleteSound;
MCI_OPEN_PARMS openMissionFailedSound;
MCI_PLAY_PARMS playMissionFailedSound;

#define BGM L"BGM_B1.mp3"	//BGM
#define SOUNDEFFECT_COLLISION L"COLLISION.mp3"		//DAMAGE 효과음
#define SOUNDEFFECT_DEFAULTGUN L"DEFAULTGUN.mp3"
#define SOUNDEFFECT_SHOTGUN L"SHOTGUN.mp3"
#define SOUNDEFFECT_MACHINEGUN L"MACHINEGUN.mp3"
#define SOUNDEFFECT_NPCDAMAGED L"NPC_DAMAGED.mp3"
#define MISSIONCOMPLETE L"MISSIONCOMPLETE.mp3"
#define MISSIONFAILED L"MISSIONFAILED.mp3"

UINT dwID;

void PlayBGMSound() {
	MCI_DGV_SETAUDIO_PARMS BgmVolume;
	BgmVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	BgmVolume.dwValue = 100;
	openBgm.lpstrElementName = BGM;
	openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 형식, wav 형식이면 "waveaudio" 작성
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommandW(dwID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&BgmVolume);
	mciSendCommandW(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playBgm);    //음악 반복 재생
}

UINT dwIDSE_D;

void PlayCOLLISIONSound() {
	MCI_DGV_SETAUDIO_PARMS CollisionVolume;
	CollisionVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	CollisionVolume.dwValue = 450;
	openDamageSound.lpstrElementName = SOUNDEFFECT_COLLISION;    //파일 오픈
	openDamageSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDamageSound);
	dwIDSE_D = openDamageSound.wDeviceID;
	mciSendCommandW(dwIDSE_D, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&CollisionVolume);
	mciSendCommandW(dwIDSE_D, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playDamageSound);    //음악을 한 번 재생
}

UINT dwIDSE_NPCD;

void PlayNPCDAMAGEDSound() {
	MCI_DGV_SETAUDIO_PARMS NPCDAMAGEDVolume;
	NPCDAMAGEDVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	NPCDAMAGEDVolume.dwValue = 450;
	openNpcSound.lpstrElementName = SOUNDEFFECT_NPCDAMAGED;    //파일 오픈
	openNpcSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openNpcSound);
	dwIDSE_NPCD = openNpcSound.wDeviceID;
	mciSendCommandW(dwIDSE_NPCD, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playNpcSound);    //음악을 한 번 재생
}

UINT dwIDSE_B;

void PlayGUNSHOOTSound(LPCWSTR Filename, LPCWSTR Filetype) {
	MCI_DGV_SETAUDIO_PARMS BulletVolume;
	BulletVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	BulletVolume.dwValue = 450;
	openBulletSound.lpstrElementName = Filename;    //파일 오픈
	openBulletSound.lpstrDeviceType = Filetype;    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBulletSound);
	dwIDSE_B = openBulletSound.wDeviceID;
	mciSendCommandW(dwIDSE_B, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&BulletVolume);
	mciSendCommandW(dwIDSE_B, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playBulletSound);    //음악을 한 번 재생
}

UINT dwID_MC;

void PlayMISSIONCOMPLETESound() {
	openDamageSound.lpstrElementName = MISSIONCOMPLETE;    //파일 오픈
	openDamageSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openMissionCompleteSound);
	dwIDSE_D = openMissionCompleteSound.wDeviceID;
	mciSendCommandW(dwIDSE_D, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playMissionCompleteSound);    //음악을 한 번 재생
}

UINT dwID_MF;

void PlayMISSIONFAILEDSound() {
	openDamageSound.lpstrElementName = MISSIONFAILED;    //파일 오픈
	openDamageSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
	mciSendCommandW(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openMissionFailedSound);
	dwIDSE_D = openMissionFailedSound.wDeviceID;
	mciSendCommandW(dwIDSE_D, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playMissionFailedSound);    //음악을 한 번 재생
}
#endif // !SOUNDPLAY_H