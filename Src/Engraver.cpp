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

#include "Vector2.hpp"
#include "Configuration.h"
#include "Motion.hpp"
#include "Engraver.h"
#include "Commands.h"

Pin_t XStep(XSTEPPORT, XSTEPPIN);
Pin_t XDir(XDIRPORT, XDIRPIN);
Pin_t XEnable(XENABLEPORT, XENABLEPIN);

Pin_t YStep(YSTEPPORT, YSTEPPIN);
Pin_t YDir(YDIRPORT, YDIRPIN);
Pin_t YEnable(YENABLEPORT, YENABLEPIN);

Delay_t Delay(DELAYTIM);

Stepper_t XStepper(XStep, XDir, XEnable, Delay);
Stepper_t YStepper(YStep, YDir, YEnable, Delay);

Bresenham_t _Bresenham(XStepper, YStepper);

Motion_t _Motion(_Bresenham);
PWM_t Laser0(LASER0TIM, LASER0CHANNEL); 

Engraver::Engraver(Motion_t& motion, PWM_t& laser0) : _Motion(motion), Laser0(laser0) {}
Engraver EngraverSingleton(_Motion, Laser0);

void Engraver::SetLaser0Duty(int duty) {
	Laser0.SetDuty(duty);
}

void Engraver::MoveTo(float x, float y, float speed, bool hasX, bool hasY, bool relative) {
	_Motion.SetTarget(x, y, speed, hasX, hasY, relative);
	MOTIONTIM.Instance->ARR = _Motion.GetCurrentPeriod();
	HAL_TIM_Base_Start_IT(&MOTIONTIM);
	while (!_Motion.IsIdle());
}

void Engraver::Step() {
	int newPeriod = _Motion.Step();
	if (newPeriod == -1) {
		HAL_TIM_Base_Stop_IT(&MOTIONTIM);
	}
	else
		MOTIONTIM.Instance->ARR = newPeriod;
}

Vector2<volatile int>& Engraver::GetCurrentPosition() {
	return _Motion.GetCurrentPosition();
}


extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &MOTIONTIM) {
		EngraverSingleton.Step();
		//XStepper.Step(1);
		//XStep.Toggle();
	}
}

extern "C" void Init() {
	HAL_TIM_Base_Start(&DELAYTIM);
	HAL_TIM_PWM_Start(&LASER0TIM, LASER0TIMCHANNEL);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);//enable USB

	//MOTIONTIM.Instance->ARR = 40000;
	//HAL_TIM_Base_Start_IT(&MOTIONTIM);

}

extern "C" int getch();

Commands commands(EngraverSingleton);

extern "C" void Loop() {
	commands.Next();
}