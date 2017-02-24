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

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

template<typename T> class Vector2 {
private:
	T _x, _y;
public:
	Vector2() {}
	Vector2(T& x, T& y) : _x(x), _y(y) {}
	Vector2(T x, T y) : _x(x), _y(y) {}
	inline void SetX(T x) { _x = x; }
	inline void SetY(T y) { _y = y; }
	inline T& GetX() { return _x; }
	inline T& GetY() { return _y; }
	void Add(Vector2<T>& b, Vector2<T>& output) {
		T rx = GetX() + b.GetX();
		T ry = GetY() + b.GetY();
		output.SetX(rx);
		output.SetY(ry);
	}
	void Subtract(Vector2<T>& b, Vector2<T>& output) {
		T rx = GetX() - b.GetX();
		T ry = GetY() - b.GetY();
		output.SetX(rx);
		output.SetY(ry);
	}
	void Abs() {
		T& x = GetX();
		T& y = GetY();
		if (x < 0) x = -x;
		if (y < 0) y = -y;
	}
	T& Max() {
		if (GetX() > GetY())
			return GetX();
		else
			return GetY();
	}
	bool Equals(Vector2<T>& b) {
		if (GetX() == b.GetX() && GetY() == b.GetY())
			return true;
		else
			return false;
	}
};

#endif
