#ifndef __HARDWARE_H
#define __HARDWARE_H


#include "stm32f10x.h"


//#####################【标准库】#####################
#include <string.h>	
//#####################【底层】#####################
#include "HW_GPIO.h"	//GPIO
#include "HW_INT.h"	//GPIO
#include "HW_TIM.h"		//定时器
#include "HW_EXTI.h"	//外部中断
#include "HW_PWM.h"		//PWM
#include "HW_EEPROM.h"	//STM32的Flash作EEPROM
#include "HW_USBUART.h"
#include "HW_Delay.h"
#include "stepper_four-phase.h"


#define F_CPU 72000000
#define M_PI  3.14159265358979323846


void Hardware_Init(void);


#endif
