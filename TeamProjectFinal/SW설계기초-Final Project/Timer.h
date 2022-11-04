#pragma once
#pragma warning(disable:4996)
#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <Windows.h>
#include <stdbool.h>

LARGE_INTEGER ticksPerSec;
LARGE_INTEGER start, end, diff;

//초 단위로 저장
int second = 1;

//측정 시작
void TimeCheckerStart() {
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
}

//측정 끝 (값을 double로 반환)
double TimeCheckerEnd() {
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	return ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
}

//측정 시, 시작부터 초단위로 확인할 수 있습니다. 단, 이 함수는 미니맵에만 영향을 끼칠 수 있습니다.
int DetectTimeFromTimeChecker() {
	if ((int)TimeCheckerEnd() > second * 2 && second < 37) { // 총 36초동안 지속할 수 있습니다
		return 1;
	}
	return 0;
}

// 게임을 시작하고부터 현재 시간이 몇 초 인지 int로 알 수 있습니다.
int TimeCheckerForInt() {
	return ((int)(TimeCheckerEnd()));
}
#endif // !TIMER_H