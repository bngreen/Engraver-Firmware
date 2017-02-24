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

#ifndef STM32PIN_HPP
#define STM32PIN_HPP

template<typename T> class STM32Pin {
private:
	T* _port;
	int _number;
public:
	STM32Pin(T* port, int number) : _port(port), _number(number) {}
	void Set() {
		_port->BSRR = _number;
	}
	void Reset() {
		_port->BRR = _number;
	}
	void Toggle() {
		_port->ODR ^= _number;
	}
	bool Read() {
		return (_port->IDR & _number) != 0;
	}
};

#endif
