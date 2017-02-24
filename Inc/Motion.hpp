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

#ifndef MOTION_HPP
#define MOTION_HPP

#include "Vector2.hpp"
#include "Settings.h"
#include <math.h>

template<typename T> class Motion {
private:
	T& bresenham;
	volatile int currentPeriod;
	volatile int targetPeriod;
	Vector2<volatile int> targetPosition;
	volatile bool isIdle;
public:
	Motion(T& _bresenham) : bresenham(_bresenham), currentPeriod(0), targetPeriod(0), targetPosition(0,0), isIdle(true) {}
	void SetCurrentPosition(int x, int y) {
		bresenham.SetCurrentPosition(x, y);
	}
	Vector2<volatile int>& GetCurrentPosition() {
		return bresenham.GetCurrentPosition();
	}
	volatile int GetCurrentPeriod() {
		return currentPeriod;
	}
	void SetTarget(float x, float y, float speed, bool hasX, bool hasY, bool relative) {
		if (!isIdle)
			return;
		isIdle = false;
		int addX = relative ? GetCurrentPosition().GetX() : 0;
		int addY = relative ? GetCurrentPosition().GetY() : 0;
		if (hasX)
			targetPosition.SetX(roundf(Settings::GetXStepsPerMM()*x) + addX);
		else
			targetPosition.SetX(GetCurrentPosition().GetX());
		if(hasY)
			targetPosition.SetY(roundf(Settings::GetYStepsPerMM()*y) + addY);
		else
			targetPosition.SetY(GetCurrentPosition().GetY());

		bresenham.Setup(bresenham.GetCurrentPosition(), targetPosition);
		targetPeriod = (Settings::GetTimFreq()) / (ceilf(speed*Settings::GetXStepsPerMM())) - 1;//TODO handle speed for each axis
		if (targetPeriod < 0) targetPeriod = 0;
		if (targetPeriod > 65535) targetPeriod = 65535;
		currentPeriod = targetPeriod;//TODO: implement acceleration
	}
	int Step() {
		if (bresenham.Step()) {
			isIdle = true;
			return -1;//finished
		}
		//TODO: implement acceleration
		return currentPeriod;
	}
	bool IsIdle() { return isIdle; }
};


#endif
