#ifndef __HW_GPIO_H
#define __HW_GPIO_H

#include "hardware.h"
//此处代码将实现GPIO的功能控制，包括输入输出初始化，设置引脚电平和读取引脚电平。

//##############################【API】##############################
void HW_GPIO_Init_CLK(void);
void HW_GPIO_Init_Out(GPIO_TypeDef * gpio,u16 gpio_pin);	
void HW_GPIO_Init_In(GPIO_TypeDef * gpio,u16 gpio_pin);
void HW_GPIO_Write(GPIO_TypeDef * gpio,u16 gpio_pin,u8 val);

#define HW_GPIO_ReadIDR(gpio,gpio_pin) (gpio->IDR & gpio_pin)

#define HW_GPIO_ReadODR(gpio,gpio_pin) (gpio->ODR & gpio_pin)

#endif
