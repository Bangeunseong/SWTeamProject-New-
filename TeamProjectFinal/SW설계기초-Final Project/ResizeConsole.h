#pragma once
#include <stdio.h>
#include <Windows.h>
#ifndef RESIZECONSOLE_H
#define RESIZECONSOLE_H

//콘솔 창 ROW 길이
#define CONSOLE_ROW 45

//콘솔 창 COLUMN 길이
#define CONSOLE_COLUMN 108

//콘솔 창 크기 설정 함수
void ResizeConsole() { system("mode con cols=108 lines=45 | title Astronauts"); }

//콘솔 창 버퍼 크기 설정 함수
void ResizeConsoleBuffer() {
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	COORD new_size = { curInfo.srWindow.Right - curInfo.srWindow.Left + 1, curInfo.srWindow.Bottom - curInfo.srWindow.Top + 1 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), new_size);
}
#endif // !RESIZECONSOLE_H