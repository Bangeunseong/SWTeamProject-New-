#pragma once
#pragma warning(disable:4996)
#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <Windows.h>
#include <stdbool.h>

LARGE_INTEGER ticksPerSec;
LARGE_INTEGER start, end, diff;

//�� ������ ����
int second = 1;

//���� ����
void TimeCheckerStart() {
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
}

//���� �� (���� double�� ��ȯ)
double TimeCheckerEnd() {
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	return ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
}

//���� ��, ���ۺ��� �ʴ����� Ȯ���� �� �ֽ��ϴ�. ��, �� �Լ��� �̴ϸʿ��� ������ ��ĥ �� �ֽ��ϴ�.
int DetectTimeFromTimeChecker() {
	if ((int)TimeCheckerEnd() > second * 2 && second < 37) { // �� 36�ʵ��� ������ �� �ֽ��ϴ�
		return 1;
	}
	return 0;
}

// ������ �����ϰ���� ���� �ð��� �� �� ���� int�� �� �� �ֽ��ϴ�.
int TimeCheckerForInt() {
	return ((int)(TimeCheckerEnd()));
}
#endif // !TIMER_H