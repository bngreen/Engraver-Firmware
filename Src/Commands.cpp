/*
Copyright (C) 2016  Bruno Naspolini Green. All rights reserved.

This file is part of Engraver-Firmware.
https://github.com/bngreen/Engraver-Firmware

Engraver-Firmware is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Engraver-Firmware is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Engraver-Firmware.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Commands.h"
#include <stdlib.h>

extern "C" int getch();
extern "C" int peekch();

char Commands::ReadChar() {
	int v;
	do {
		v = getch();
	} while (v == -1);
	return v;
}

char Commands::PeekChar() {
	int v;
	do {
		v = peekch();
	} while (v == -1);
	return v;
}

void Commands::GCommands(char* command) {
	int n, pos=1;
	n = strtol(command + pos, &command, 10);
	if (n == 1) {
		char c;
		float x, y, speed = Settings::GetDefaultSpeed();
		x = y = 0;
		bool hasX, hasY;
		bool relative = false;
		hasX = hasY = false;
		do {
			c = *command++;
			switch (c) {
			case 'X':
			case 'x':
				x = strtod(command, &command);
				hasX = true;
				break;
			case 'Y':
			case 'y':
				y = strtod(command, &command);
				hasY = true;
				break;
			case 'F':
			case 'f':
				speed = strtod(command, &command);
				speed /= 60;
				break;
			case 'R':
			case'r':
				relative = true;
				break;
			}
		} while (c != '\n' && c != '\r');
		if (hasX || hasY)
			engraver.MoveTo(x, y, speed, hasX, hasY, relative);
	}
	else if (n == 92) {
		Vector2<volatile int>& v = engraver.GetCurrentPosition();
		v.SetX(0);
		v.SetY(0);
	}
	else if (n == 28) {
		engraver.MoveTo(0, 0, Settings::GetDefaultSpeed(), true, true, false);
	}
}

void Commands::MCommands(char* command) {
	int n;
	n = strtol(command + 1, &command, 10);
	if (n == 900) {
		int l, duty=0;
		l = strtod(command, &command);
		duty = strtod(command, &command);
		if (l == 0) {
			engraver.SetLaser0Duty(duty);
		}
	}
}

const int MaxCommandSize = 64;

void Commands::Next() {
	char command[MaxCommandSize];
	int i;
	char c = PeekChar();
	while (c != 'G' && c != 'g' && c != 'M' && c != 'm') {
		ReadChar();
		c = PeekChar();
	}
	for (i = 0;i < MaxCommandSize;i++) {
		c = ReadChar();
		command[i] = c;
		if (c == '\r' || c == '\n') break;
	}
	switch (command[0])
	{
	case 'G':
	case 'g':
		GCommands(command);
		break;
	case 'M':
	case 'm':
		MCommands(command);
		break;
	default:
		break;
	}
	printf("done\r\n");
}