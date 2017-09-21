#include "stepper_four-phase.h"

static uint8_t firstrun=1;

static void Steppers_Init(void)
{
    HW_GPIO_Init_Out(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
    HW_GPIO_Write(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11,0);
    
    HW_GPIO_Init_Out(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
    HW_GPIO_Write(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,0);
}
/*
void Xstepper(int16_t val){
  static uint8_t step=0;
  if(firstrun)
  {
    firstrun=0;
    Steppers_Init();
  }
  if(val>0)
  {
    step++;
    if(step>=8) step-=8;
  }
  else if(val<0)
  {
    if(step<=0) step+=8;
    step--;
  }
  HW_GPIO_Write(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11,0);
  switch(step)
  {
    case 0:
      HW_GPIO_Write(GPIOB,GPIO_Pin_8,1);
      break;
    case 1:
      HW_GPIO_Write(GPIOB,GPIO_Pin_9,1);
      break;
    case 2:
      HW_GPIO_Write(GPIOB,GPIO_Pin_10,1);
      break;
    case 3:
      HW_GPIO_Write(GPIOB,GPIO_Pin_11,1);
      break;
    default:
      break;
  }
}

void Ystepper(int16_t val){
  static uint8_t step=0;
  if(firstrun)
  {
    firstrun=0;
    Steppers_Init();
  }
  if(val>0)
  {
    step++;
    if(step>=8) step-=8;
  }
  else if(val<0)
  {
    if(step<=0) step+=8;
    step--;
  }
  HW_GPIO_Write(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,0);
  switch(step)
  {
    case 0:
      HW_GPIO_Write(GPIOB,GPIO_Pin_12,1);
      break;
    case 1:
      HW_GPIO_Write(GPIOB,GPIO_Pin_13,1);
      break;
    case 2:
      HW_GPIO_Write(GPIOB,GPIO_Pin_14,1);
      break;
    case 3:
      HW_GPIO_Write(GPIOB,GPIO_Pin_15,1);
      break;
    default:
      break;
  }
}
*/

void Xstepper(int16_t val){
  static uint8_t step=0;
  if(firstrun)
  {
    firstrun=0;
    Steppers_Init();
  }
  if(val>0)
  {
    step++;
    if(step>=8) step-=8;
  }
  else if(val<0)
  {
    if(step<=0) step+=8;
    step--;
  }
  HW_GPIO_Write(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11,0);
  switch(step)
  {
    case 0:
      HW_GPIO_Write(GPIOB,GPIO_Pin_8,1);
      break;
    case 1:
      HW_GPIO_Write(GPIOB,GPIO_Pin_8,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_9,1);
      break;
    case 2:
      HW_GPIO_Write(GPIOB,GPIO_Pin_9,1);
      break;
    case 3:
      HW_GPIO_Write(GPIOB,GPIO_Pin_9,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_10,1);
      break;
    case 4:
      HW_GPIO_Write(GPIOB,GPIO_Pin_10,1);
      break;
    case 5:
      HW_GPIO_Write(GPIOB,GPIO_Pin_10,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_11,1);
      break;
    case 6:
      HW_GPIO_Write(GPIOB,GPIO_Pin_11,1);
      break;
    case 7:
      HW_GPIO_Write(GPIOB,GPIO_Pin_11,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_8,1);
      break;
    default:
      break;
  }
}

void Ystepper(int16_t val){
  static uint8_t step=0;
  if(firstrun)
  {
    firstrun=0;
    Steppers_Init();
  }
  if(val>0)
  {
    step++;
    if(step>=8) step-=8;
  }
  else if(val<0)
  {
    if(step<=0) step+=8;
    step--;
  }
  HW_GPIO_Write(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,0);
  switch(step)
  {
    case 0:
      HW_GPIO_Write(GPIOB,GPIO_Pin_12,1);
      break;
    case 1:
      HW_GPIO_Write(GPIOB,GPIO_Pin_12,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_13,1);
      break;
    case 2:
      HW_GPIO_Write(GPIOB,GPIO_Pin_13,1);
      break;
    case 3:
      HW_GPIO_Write(GPIOB,GPIO_Pin_13,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_14,1);
      break;
    case 4:
      HW_GPIO_Write(GPIOB,GPIO_Pin_14,1);
      break;
    case 5:
      HW_GPIO_Write(GPIOB,GPIO_Pin_14,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_15,1);
      break;
    case 6:
      HW_GPIO_Write(GPIOB,GPIO_Pin_15,1);
      break;
    case 7:
      HW_GPIO_Write(GPIOB,GPIO_Pin_15,1);
      HW_GPIO_Write(GPIOB,GPIO_Pin_12,1);
      break;
    default:
      break;
  }
}



