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

#define BGM "C:\\Users\\bange\\OneDrive\\���� ȭ��\\Documents\\GitHub\\�� ����\\TeamProjectFinal\\BGM.mp3"	//BGM ���� Ȯ���
#define DAMAGE "C:\\�����\\bange\\OneDrive\\���� ȭ��\\Documents\\GitHub\\�� ����\\TeamProjectFinal\\GameResource\\Explosion.mp3"		//DAMAGE ȿ���� Ȯ���
//#define CLEAR ""		//���� Ŭ���� �� ���� Clear ȿ���� Ȯ���

int dwID;
void PlayBgm() {
	openBgm.lpstrElementName = BGM;
	openBgm.lpstrDeviceType = "mpegvideo";    //mp3 ����, wav �����̸� "waveaudio" �ۼ�
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playBgm);    //���� �ݺ� ���
}
void PlayDamageSound() {
	openDamageSound.lpstrElementName = DAMAGE;    //���� ����
	openDamageSound.lpstrDeviceType = "mpegvideo";    //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDamageSound);
	dwID = openDamageSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openDamageSound);    //������ �� �� ���
	if (TimeCheckerEnd() - PausingTime - CollisionTime > 0.8)
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
}
#endif // !SOUNDPLAY_H
