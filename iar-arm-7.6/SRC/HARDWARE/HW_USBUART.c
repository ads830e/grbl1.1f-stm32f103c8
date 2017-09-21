/**
  ******************************************************************************
  * @file    usbuart.c
  * $Author: tuoqiang
  * $Revision: 67 $
  * $Date:: 2012-08-15 19:00:29 +0800 #$
  * @brief   USB虚拟串口接口函数.
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "usb_desc.h"
#include "usb_lib.h"
#include "hw_config.h"


#include "Hardware.h"


/* Private functions ---------------------------------------------------------*/
/* 初始化USB虚拟串口 */
void HW_USB_Init(void){
    Set_System();//系统时钟初始化
    USB_Interrupts_Config();
    Set_USBClock();
    USB_Init();
}  


