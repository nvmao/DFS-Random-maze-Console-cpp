#pragma once

enum Controler
{
	Back,
	Enter,
	Add,
	Watch,
	Quit
};

enum SymbolChar
{
	RectangleChar = 219,
	SquareChar = 254,

	UpRightCorner = 187,
	DownRightCorner = 188,
	UpLeftCorner = 201,
	DownLeftCorner = 200,
	Horizontal = 205,
	Vertical = 186,

};

enum Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15,

};

enum Direction
{
	left,
	right,
	up,
	down
};

enum Key : char
{
	arrow_up = 72,
	arrow_down = 80,
	arrow_left = 75,
	arrow_right = 77
};
