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

#define BGM ""	//BGM ���� Ȯ���
#define DAMAGE ""		//DAMAGE ȿ���� Ȯ���
#define CLEAR ""		//Clear ȿ���� Ȯ���

int dwID;

void PlayBgm(void) {
	openBgm.lpstrElementName = LPCWSTR(BGM);            //���� ����
	openBgm.lpstrDeviceType = LPCWSTR("mpegvideo");    //mp3 ����, wav �����̸� "waveaudio" �ۼ�
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);    //���� �ݺ� ���
}

#endif // !SOUNDPLAY_H
