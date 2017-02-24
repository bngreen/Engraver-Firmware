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

#ifndef ENGRAVER_H
#define ENGRAVER_H

#include "Configuration.h"
#include "Motion.hpp"

class Engraver {
private:
	Motion_t& _Motion;
	PWM_t& Laser0;
public:
	Engraver(Motion_t& motion, PWM_t& laser0);
	void SetLaser0Duty(int duty);
	void MoveTo(float x, float y, float speed, bool hasX, bool hasY, bool relative);
	void Step();
	Vector2<volatile int>& GetCurrentPosition();
};

#endif
