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

#ifndef STM32DELAYTIMER_HPP
#define STM32DELAYTIMER_HPP

template<typename T> class STM32DelayTimer {
private:
	T& tim;
public:
	STM32DelayTimer(T& _tim) :tim(_tim) {}
	inline void DelayUs(uint16_t v) {
		tim.Instance->CNT = 0;
		while (tim.Instance->CNT < v);
	}
};

#endif
