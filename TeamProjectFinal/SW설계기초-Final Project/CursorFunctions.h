#pragma once
#include <stdio.h>
#include <Windows.h>
#ifndef CURSORFUNCTIONS_H
#define CURSORFUNCTIONS_H

//커서 위치 설정
void SetCurrentCursorPos(int x, int y) {
	COORD ptr = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ptr);
}

//커서 위치 반환
COORD GetCurrentCursorPos() {
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint = curInfo.dwCursorPosition;
	return curPoint;
}

//시각적으로 표현되는 커서 지우기
void RemoveCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
#endif // !CURSORFUNCTION_H