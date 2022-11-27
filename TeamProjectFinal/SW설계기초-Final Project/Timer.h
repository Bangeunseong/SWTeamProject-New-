#pragma once
#pragma warning(disable:4996)
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
#include "VariableSets.h"
#ifndef TIMER_H
#define TIMER_H

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

// 게임을 시작하고부터 현재 시간이 몇 초 인지 int로 알 수 있습니다.
int TimeCheckerForInt() {
	return ((int)(TimeCheckerEnd()));
}
#endif // !TIMER_H