#include "console_draw_utils.hpp"
#include <iostream>

#define _WIN32_WINNT 0x0500
#include <Windows.h>

#define P(x, y) (sx+1)*y + x 
#define CHARXY 2 // vo skolko raz x menche y

int get_console_x() {
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.right;
}
int get_console_y() {
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.bottom;
}

void swap(int& a, int& b) {
	int t = b;
	b = a;
	a = t;
}

ConsolePainter::ConsolePainter(int sx, int sy) : sx{ sx }, sy{ sy }
{
	// create char array
	screen_lenght = (sx + 1) * sy + 1;

	clear_screen = new char[screen_lenght];
	screen = new char[screen_lenght];

	// create clear screen
	for (int y = 0; y < sy; y++) { // iter 
		for (int x = 0; x < sx; x++) // iter 
		{
			clear_screen[P(x, y)] = ' ';
		}
		int p = P(sx, y);
		clear_screen[p] = '\n';
	}
	clear_screen[screen_lenght - 1] = '\0'; // add end string symbol
}

void ConsolePainter::edit_symbol(int px, int py, char symbol) {
	screen[P(px, py)] = symbol;
}

void ConsolePainter::clear() {
	for (int i = 0; i < screen_lenght; i++) {
		screen[i] = clear_screen[i];
	}
}

void ConsolePainter::display() {
	std::cout << screen;
}

int ConsolePainter::get_sx() {
	return sx;
}
int ConsolePainter::get_sy() {
	return sy;
}

void ConsolePainter::find_console_size()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	sx = csbi.srWindow.Right - csbi.srWindow.Left;
	sy = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ConsolePainter::update_cons_par()
{
	find_console_size();

	// create char array
	screen_lenght = (sx + 1) * sy + 1;

	delete[screen_lenght] clear_screen;
	clear_screen = new char[screen_lenght];
	delete[screen_lenght] screen;
	screen = new char[screen_lenght];

	// create clear screen
	for (int y = 0; y < sy; y++) { // iter 
		for (int x = 0; x < sx; x++) // iter 
		{
			clear_screen[P(x, y)] = ' ';
		}
		int p = P(sx, y);
		clear_screen[p] = '\n';
	}
	clear_screen[screen_lenght - 1] = '\0'; // add end string symbol
}
//---------------------------------------

ConsolePrimDrawer::ConsolePrimDrawer(int sx, int sy) : ConsolePainter(sx, sy) 
{

}

void ConsolePrimDrawer::line(int x0, int y0, int x1, int y1, char symbol)
{
	x0 *= CHARXY; sx *= CHARXY;

	bool swapped = false;
	if( abs( x1 - x0 ) < abs( y1 - y0 )) // swap x and y points
	{
		swap(x0, y0);
		swap(x1, y1);
		swapped = true;
	}
	if( x0 > x1 ) // swap line end/start
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float rot2 = abs(dy) * 2; // koficient naklona !!! mult 2
	float err2 = 0; // distance wtih ideal line !!! mult 2
	
	for (int x = x0, y = y0;
		x <= x1;
		x++) 
	{
		if ( swapped )
			screen[P(y, x)] = symbol;
		else
			screen[P(x, y)] = symbol;

		err2 += rot2;

		if (err2 > dx) {
			y += (y1 / y0 ? 1 : -1);
			err2 -= dx*2.;
		}
	}
}

void ConsolePrimDrawer::rectangle(int x0, int y0, int x1, int y1, char fill)
{
	x0 *= CHARXY; x1 *= CHARXY;

	if (x0 < 0)
		x0 = 0;
	if (x1 < 0)
		x1 = 0;
	if (y0 < 0)
		y0 = 0;
	if (y1 < 0)
		y1 = 0;
	if (x0 >= sx)
		x0 = sx;
	if (x1 >= sx)
		x1 = sx;
	if (y0 >= sy)
		y0 = sy;
	if (y1 >= sy)
		y1 = sy;


	for (int x = x0; x < x1; x++) {
		for (int y = y0; y < y1; y++)
		{
			int p = P(x, y);
			screen[p] = fill;
		}
	}
			
}

int ConsolePrimDrawer::get_sx() {
	return int(sx / CHARXY);
}

//---------------------------------------

