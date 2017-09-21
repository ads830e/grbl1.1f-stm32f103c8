/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */


#ifndef cpu_map_h
#define cpu_map_h

/****************************************************************************/
  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  //定义步进脉冲输出引脚。注：所有的步进脉冲引脚必须定义在同一个端口上。
  #define STEP_GPIO				GPIOB					//端口
  #define X_STEP_GPIO_PIN			GPIO_Pin_0				//引脚
  #define Y_STEP_GPIO_PIN			GPIO_Pin_1			   	//引脚
  #define Z_STEP_GPIO_PIN			GPIO_Pin_2				//引脚

//原平台适配，可不用修改。
  #define X_STEP_BIT      			2  
  #define Y_STEP_BIT      			3  
  #define Z_STEP_BIT      			4  
  #define STEP_MASK       			((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) 

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
//定义方向电平输出引脚。注：所有的方向引脚必须定义在同一个端口上。
  #define DIRECTION_GPIO			GPIOB					//端口
  #define X_DIRECTION_GPIO_PIN			GPIO_Pin_3				//引脚
  #define Y_DIRECTION_GPIO_PIN			GPIO_Pin_4			   	//引脚
  #define Z_DIRECTION_GPIO_PIN			GPIO_Pin_5				//引脚

//原平台适配，可不用修改。
  #define X_DIRECTION_BIT   			5  
  #define Y_DIRECTION_BIT   			6  
  #define Z_DIRECTION_BIT   			7  
  #define DIRECTION_MASK    			((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT))

  // Define stepper driver enable/disable output pin.
  //定义步进电机驱动器使能引脚
  #define STEPPERS_DISABLE_GPIO   		GPIOA					//端口
  #define STEPPERS_DISABLE_GPIO_PIN		GPIO_Pin_3				//引脚
//原平台适配，可不用修改。
  #define STEPPERS_DISABLE_BIT    		0  
  #define STEPPERS_DISABLE_MASK   		(1<<STEPPERS_DISABLE_BIT)
/****************************************************************************/
  // Define homing/hard limit switch input pins and limit interrupt vectors.
  // NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
  //定义原点/硬限位开关输入引脚和限位中断向量
//注意：所有的限位引脚必须使用同一个中断处理函数。
  #define LIMIT_GPIO				GPIOA					//端口
  #define X_LIMIT_GPIO_PIN			GPIO_Pin_10				//引脚
  #define Y_LIMIT_GPIO_PIN			GPIO_Pin_13			   	//引脚
  #define Z_LIMIT_GPIO_PIN			GPIO_Pin_14				//引脚

  #define LIMIT_INT_PORTSOURCE 		        GPIO_PortSourceGPIOA 	//中断源端口
  #define X_LIMIT_INT_PINSOURCE		        GPIO_PinSource10	   	//中断源引脚
  #define Y_LIMIT_INT_PINSOURCE		        GPIO_PinSource13		//中断源引脚
  #define Z_LIMIT_INT_PINSOURCE		        GPIO_PinSource14		//中断源引脚
  #define X_LIMIT_INT_LINE			EXTI_Line10				//中断线
  #define Y_LIMIT_INT_LINE			EXTI_Line13				//中断线
  #define Z_LIMIT_INT_LINE			EXTI_Line14				//中断线

  #define LIMIT_INT_CHANNEL			EXTI15_10_IRQn			//中断向量通道
//注意：中断处理函数需在代码中修改
//原平台适配，可不用修改。
  #define X_LIMIT_BIT                           1
  #define Y_LIMIT_BIT                           2
  #define Z_LIMIT_BIT    	                3
  #define LIMIT_MASK                            ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
/****************************************************************************/
  // Define spindle enable and spindle direction output pins.
  //定义主轴使能输出引脚
  #define SPINDLE_ENABLE_GPIO   		GPIOA					//端口
  #define SPINDLE_ENABLE_GPIO_PIN		GPIO_Pin_1				//引脚
//定义主轴方向输出引脚
  #define SPINDLE_DIRECTION_GPIO   		GPIOA					//端口
  #define SPINDLE_DIRECTION_GPIO_PIN		GPIO_Pin_2				//引脚// Z Limit pin and spindle PWM/enable pin swapped to access hardware PWM on Pin 11.

//开启PWM控制主轴
  #ifdef VARIABLE_SPINDLE 
    #define SPINDLE_PWM_GPIO   		        GPIOA					//端口
    #define SPINDLE_PWM_GPIO_PIN		GPIO_Pin_0				//引脚
  
    #define PWM_MAX_VALUE       		65535.0					//PWM最大输入值
//阅读源文件spindle_control.c可知PWM最大值为0xffff（65535）

    #define PWM_TIMER				TIM2					//PWM从属时钟
    #define PWM_CLK 				RCC_APB1Periph_TIM2		//外设时钟
  //注意：OC1Init()和TIM_OC1PreloadConfig()等特定通道函数需在代码中修改

  #endif // End of VARIABLE_SPINDLE

/****************************************************************************/
  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_GPIO   		        GPIOB					//端口
  #define COOLANT_FLOOD_GPIO_PIN	        GPIO_Pin_6				//引脚
  #define COOLANT_MIST_GPIO   		        GPIOB					//端口
  #define COOLANT_MIST_GPIO_PIN		        GPIO_Pin_7				//引脚
/****************************************************************************/
  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
//定义用户控制（循环开始，复位，给进保持）输入引脚
//注意：所有的限位引脚必须使用同一个中断处理函数。
  #define CONTROL_GPIO			        GPIOA					//端口
  #define RESET_GPIO_PIN			GPIO_Pin_5				//引脚
  #define FEED_HOLD_GPIO_PIN			GPIO_Pin_6			   	//引脚
  #define CYCLE_START_GPIO_PIN		        GPIO_Pin_7				//引脚
  #define SAFETY_DOOR_GPIO_PIN		        GPIO_Pin_8				//引脚

  #define CONTROL_INT_PORTSOURCE 		GPIO_PortSourceGPIOA 	//中断源端口
  #define RESET_INT_PINSOURCE		        GPIO_PinSource5			//中断源引脚：复位
  #define FEED_HOLD_INT_PINSOURCE		GPIO_PinSource6			//中断源引脚：给进保持
  #define CYCLE_START_INT_PINSOURCE	        GPIO_PinSource7			//中断源引脚：循环开始
  #define SAFETY_DOOR_INT_PINSOURCE	        GPIO_PinSource8			//中断源引脚：紧急停车
  #define RESET_INT_LINE			EXTI_Line5				//中断线：复位
  #define FEED_HOLD_INT_LINE		        EXTI_Line6				//中断线：给进保持
  #define CYCLE_START_INT_LINE		        EXTI_Line7				//中断线：循环开始
  #define SAFETY_DOOR_INT_LINE		        EXTI_Line8				//中断线：紧急停车

  #define CONTROL_INT_CHANNEL		        EXTI9_5_IRQn			//中断向量通道
//注意：中断处理函数需在代码中修改

//原平台适配，可不用修改。
  #define CONTROL_RESET_BIT                     0  // Uno Analog Pin 0
  #define CONTROL_FEED_HOLD_BIT                 1  // Uno Analog Pin 1
  #define CONTROL_CYCLE_START_BIT               2  // Uno Analog Pin 2
  #define CONTROL_SAFETY_DOOR_BIT               3  //tq2017  Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.
  #define CONTROL_MASK                          ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
  #define CONTROL_INVERT_MASK                   CONTROL_MASK // May be re-defined to only invert certain control pins.
/****************************************************************************/
  // Define probe switch input pin.
  //定义探测开关输入引脚
  #define PROBE_GPIO   		                GPIOA					//端口
  #define PROBE_GPIO_PIN		        GPIO_Pin_4				//引脚

/****************************************************************************/
  // Variable spindle configuration below. Do not change unless you know what you are doing.
  // NOTE: Only used when variable spindle is enabled.
  #define SPINDLE_PWM_MAX_VALUE                 255 // Don't change. 328p fast PWM mode fixes top value as 255.
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE               1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE                 0
  #define SPINDLE_PWM_RANGE                     (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

#endif
