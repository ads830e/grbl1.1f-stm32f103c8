#ifndef __HW_Delay_h
#define __HW_Delay_h 			   

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************	 
void HW_Delay_Init(void);
void HW_Delay_ms(u16 nms);
void HW_Delay_us(u32 nus);


#define _delay_ms HW_Delay_ms
#define _delay_us HW_Delay_us

#endif





























