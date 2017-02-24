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

#ifndef BRESENHAM_HPP
#define BRESENHAM_HPP

#include "Vector2.hpp"

//From: http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

/*void line(int x0, int y0, int x1, int y1) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    setPixel(x0,y0);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}*/

template<typename T> class Bresenham {
private:
	T& stepperX;
	T& stepperY;
	int err, sx, sy;
	Vector2<volatile int> current, D;
	Vector2<volatile int> _to;
public:

	Bresenham(T& _stepperX, T& _stepperY) : stepperX(_stepperX), stepperY(_stepperY) {

	}

	Vector2<volatile int>& GetCurrentPosition() { return current; }

	void SetCurrentPosition(int x, int y) {
		current.SetX(x);
		current.SetY(y);
	}

	void Setup(Vector2<volatile int>& from, Vector2<volatile int>& to) {
		current = from;
		_to = to;
		to.Subtract(from, D);
		D.Abs();
		sx = from.GetX() < to.GetX() ? 1 : -1;
		sy = from.GetY() < to.GetY() ? 1 : -1;
		err = (D.GetX() > D.GetY() ? D.GetX() : -D.GetY()) >> 1;
	}

	bool Step() {
		if (current.Equals(_to))
			return true;
		int e2 = err, dx=0, dy=0;
		if (e2 > -D.GetX()) { err -= D.GetY(); current.GetX() += sx; dx = sx; }
		if (e2 < D.GetY()) { err += D.GetX(); current.GetY() += sy; dy = sy; }
		stepperX.Step(dx);
		stepperY.Step(dy);
		if (current.Equals(_to))
			return true;
		return false;
	}

};

#endif
