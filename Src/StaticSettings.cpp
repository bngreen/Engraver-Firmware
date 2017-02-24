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

#include "Settings.h"
#include "Configuration.h"

uint32_t Settings::GetXStepsPerMM() { return XSTEPSPERMM; }
uint32_t Settings::GetYStepsPerMM() { return YSTEPSPERMM; }
uint32_t Settings::GetAccel() { return ACCEL; }
uint32_t Settings::GetTimFreq() { return TIMFREQ; }

uint32_t Settings::GetDefaultSpeed() { return DEFAULTSPEED; }