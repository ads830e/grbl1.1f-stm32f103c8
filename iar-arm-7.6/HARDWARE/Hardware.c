#include "Hardware.h"

void Hardware_Init(void){
  HW_USB_Init();
  HW_GPIO_Init_CLK();
  HW_Delay_Init();
}






