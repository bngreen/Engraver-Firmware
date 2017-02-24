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

#ifndef STM32PWM_HPP
#define STM32PWM_HPP

#include <stdint.h>
#include <math.h>

#ifndef SATURATE
#define SATURATE(v, _min, _max) (v > _max ? _max : v < _min ? _min : v)
#endif

enum PWMChannel {
	PWM_CHANNEL_1 = 1,
	PWM_CHANNEL_2 = 2,
	PWM_CHANNEL_3 = 4,
	PWM_CHANNEL_4 = 8,
};

template<typename T> class STM32PWM {
private:
	T& _tim;
	PWMChannel _channel;
	void setCCR(uint32_t value) {
		if (_channel & PWM_CHANNEL_1)
			_tim.Instance->CCR1 = value;
		if (_channel & PWM_CHANNEL_2)
			_tim.Instance->CCR2 = value;
		if (_channel & PWM_CHANNEL_3)
			_tim.Instance->CCR3 = value;
		if (_channel & PWM_CHANNEL_4)
			_tim.Instance->CCR4 = value;
	}
public:
	STM32PWM(T& tim, PWMChannel channel) : _tim(tim), _channel(channel) {}
	void SetDuty(int duty) {
		uint64_t nv = ((uint64_t)SATURATE(duty, 0, 10000)*(_tim.Instance->ARR + 1)) / 10000;
		setCCR(nv);
	}

	void SetDuty(float duty) {
		float nv = ((float)SATURATE(duty, 0.0f, 1.0f)*(_tim.Instance->ARR + 1));
		setCCR(roundf(nv));
	}
};

#endif
