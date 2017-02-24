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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "STM32Pin.hpp"
#include "STM32PWM.hpp"
#include "STM32DelayTimer.hpp"
#include "Stepper.hpp"
#include "Bresenham.hpp"
#include "Motion.hpp"

#include "stm32f1xx_hal.h"
#include "tim.h"

//Types
typedef STM32Pin<GPIO_TypeDef> Pin_t;
typedef STM32DelayTimer<TIM_HandleTypeDef> Delay_t;
typedef Stepper<Pin_t, Delay_t> Stepper_t;
typedef Bresenham<Stepper_t> Bresenham_t;
typedef STM32PWM<TIM_HandleTypeDef> PWM_t;
typedef Motion<Bresenham_t> Motion_t;

//Definitions
#define XSTEPPORT GPIOA
#define XDIRPORT GPIOA
#define XENABLEPORT GPIOA
#define XSTEPPIN GPIO_PIN_0
#define XDIRPIN GPIO_PIN_1
#define XENABLEPIN GPIO_PIN_2

#define YSTEPPORT GPIOB
#define YDIRPORT GPIOB
#define YENABLEPORT GPIOB
#define YSTEPPIN GPIO_PIN_12
#define YDIRPIN GPIO_PIN_13
#define YENABLEPIN GPIO_PIN_14

#define DELAYTIM htim3
#define MOTIONTIM htim4

#define LASER0TIM htim2
#define LASER0CHANNEL PWM_CHANNEL_3
#define LASER0TIMCHANNEL TIM_CHANNEL_3

#define XSTEPSPERMM 500
#define YSTEPSPERMM 500

#define ACCEL 100

#define DEFAULTSPEED 3

#define TIMFREQ (72000000/(MOTIONTIM.Init.Prescaler+1))



#endif
