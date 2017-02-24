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

#ifndef STEPPER_HPP
#define STEPPER_HPP

template<typename T, typename T2> class Stepper {
private:
	T& _step;
	T& _dir;
	T& _enable;
	T2& _tim;
public:
	Stepper(T& step, T& dir, T& enable, T2& tim) : _step(step), _dir(dir), _enable(enable), _tim(tim) {}
	void SetState(bool enabled) {
		if (enabled)
			_enable.Set();
		else
			_enable.Reset();
		_tim.DelayUs(2);
	}
	void Step(int d) {
		if (d != 1 && d != -1)
			return;
		if (d == -1)
			_dir.Reset();
		else if (d == 1)
			_dir.Set();
		_tim.DelayUs(40);
		_step.Set();
		_tim.DelayUs(40);
		_step.Reset();
	}
};

#endif
