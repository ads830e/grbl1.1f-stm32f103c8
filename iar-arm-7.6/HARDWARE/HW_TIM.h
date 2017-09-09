#ifndef __HW_TIM_H
#define __HW_TIM_H


//##############################【API】##############################
void HW_TIM_Init(void);				//定时器初始化，要移至到stepper.c中的st_init()
//Driver Interrupt
void HW_TIM_DriverInterrupt_Enable(void); 		//开启定时器
void HW_TIM_DriverInterrupt_Disable(void);		//关闭定时器
void HW_TIM_DriverInterrupt_ValueConfig(uint16_t Prescaler,uint16_t Autoreload);		//设置定时器重装值
//Port Reset Interrupt
void HW_TIM_PortResetInterrupt_Enable(void);  	//开启定时器
void HW_TIM_PortResetInterrupt_Disable(void);	//关闭定时器
void HW_TIM_PortResetInterrupt_ValueConfig(uint16_t Prescaler,uint16_t Autoreload); 	//设置定时器重装值
//Debounce
void HW_Debounce_Init(void);		//去抖定时器
void HW_Debounce_Enable(void);		//使能去抖定时器
void HW_Debounce_Disable(void);		//除能去抖定时器


#endif
