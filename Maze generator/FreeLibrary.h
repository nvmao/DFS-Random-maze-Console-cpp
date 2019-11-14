#pragma once
#pragma warning(disable:4996)
#include <Windows.h>
#include <string>
#include <iostream>
#include "enums.h"

using namespace std;


void Print_color(int x, int y, string text, int color);

void PrintColor(char text, int color);

void Set_bg_from_to(int x, int y, string value, Color color);

void PrintColor(string text, int color);

void ShowCursor(bool Visible);

void gotoxy(short x, short y);

int whereX();

int whereY();

void UnicodeMode();
void Console_OriginalMode();

void clreol();
void SetColor(WORD color);
void SetBGColor(WORD color);

///////////////////////

void resizeConsole(int width, int height);

void cls();

void FullScreen();

void CleanScreen(HANDLE hConsole);

void setTextSize(int x, int y);

WORD getKey();
