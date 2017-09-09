#include "Hardware.h"

void HW_GPIO_Init_CLK(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 			//使能端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    // 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
    // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
    
}

//此处代码将实现GPIO的功能控制，包括初始化，设置引脚电平和读取引脚电平。
void HW_GPIO_Init_Out(GPIO_TypeDef * gpio,u16 gpio_pin)			
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = gpio_pin;						//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		 	//IO口速度为50MHz
	GPIO_Init(gpio, &GPIO_InitStructure);					//根据设定参数初始化
}

void HW_GPIO_Init_In(GPIO_TypeDef * gpio,u16 gpio_pin)			
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = gpio_pin;						//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 		//上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		 	//IO口速度为50MHz
	GPIO_Init(gpio, &GPIO_InitStructure);					//根据设定参数初始化
}

void HW_GPIO_Write(GPIO_TypeDef* gpio, uint16_t gpio_pin, u8 val)
{
  if(val==0) gpio->BRR = gpio_pin;else gpio->BSRR = gpio_pin;
}

