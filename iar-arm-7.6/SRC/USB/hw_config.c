/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "hardware.h"
/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_it.h"
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
EXTI_InitTypeDef EXTI_InitStructure;

//UART tx
#define USB_TBuffer_Size 1024
uint8_t  USB_TBuffer [USB_TBuffer_Size]; 
uint16_t USB_TBuffer_in = 0;

//UART rx
#define USB_RBuffer_Size 1024
static uint8_t USB_RBuffer[USB_RBuffer_Size];
static uint16_t USB_RBuffer_Current=0;
static uint16_t USB_RBuffer_Read=0;

uint8_t  USB_Tx_State = 0;
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
/* Extern variables ----------------------------------------------------------*/

extern LINE_CODING linecoding;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{  
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */   
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS) || defined(STM32F37X) || defined(STM32F30X)
  /* Enable the SYSCFG module clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
#endif /* STM32L1XX_XD */ 
   
  /* Configure the EXTI line 18 connected internally to the USB IP */
  EXTI_ClearITPendingBit(EXTI_Line18);
  EXTI_InitStructure.EXTI_Line = EXTI_Line18; 
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD) || defined(STM32L1XX_MD_PLUS) 
  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
  
#else 
  /* Select USBCLK source */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  
  /* Enable the USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
#endif /* STM32L1XX_MD */
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
  /*Enable SystemCoreClock*/
  SystemInit();
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  /* 2 bit for pre-emption priority, 2 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
  
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
    /* Enable the USB Wake-up interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USB_FS_WKUP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
#elif defined(STM32F37X)
  /* Enable the USB interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the USB Wake-up interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
#else
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
    /* Enable the USB Wake-up interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Init(&NVIC_InitStructure);
#endif /* STM32L1XX_XD */

}


/*******************************************************************************
* Function Name  : USB_To_Buffer.
* Description    : send the received data from USB to buffer.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
* Return         : none.
*******************************************************************************/
void USB_To_Buffer(uint8_t* data_buffer, uint16_t Nb_bytes)
{
  uint16_t i;
  for (i = 0; i < Nb_bytes; i++){
    USB_RBuffer[USB_RBuffer_Current++] = *(data_buffer + i);
    /* To avoid buffer overflow */
    if(USB_RBuffer_Current >= USB_RBuffer_Size)    USB_RBuffer_Current = 0;
  }  
}
/*******************************************************************************
* Function Name  : Read_From_USB_RBuffer.
* Description    : send the received data from USB to buffer.
* Input          : none.
* Return         : uint8_t.
*******************************************************************************/
uint8_t USB_Read_RBuffer(void)
{
  if(USB_RBuffer_Read>=USB_RBuffer_Size) USB_RBuffer_Read=0;
  if(USB_RBuffer_Current==USB_RBuffer_Read) return 0xff;
  return USB_RBuffer[USB_RBuffer_Read++];
}

uint16_t USB_RBuffer_Count(void){
    uint16_t count;
    if(USB_RBuffer_Read<=USB_RBuffer_Current) count=USB_RBuffer_Current-USB_RBuffer_Read;
    else count=USB_RBuffer_Current+USB_RBuffer_Size-USB_RBuffer_Read;
    if(count<=127) return count;
    else return 127;
}
void USB_Reset_RBuffer(void) {
      //USB_RBuffer_Read=0;
      //USB_RBuffer_Current=0;
}
/*******************************************************************************
* Function Name  : USB_Send_Data.
* Description    : send the data to USB.
* Input          : uint8_t data.
* Return         : none.
*******************************************************************************/
void USB_Send_Data(uint8_t data){
    uint16_t USB_TBuffer_in_tmp=USB_TBuffer_in;
    USB_TBuffer[USB_TBuffer_in_tmp++] = data;
    /* To avoid buffer overflow */
    if(USB_TBuffer_in_tmp >= USB_TBuffer_Size)    USB_TBuffer_in = 0;
    else USB_TBuffer_in++;
}

/*******************************************************************************
* Function Name  : Handle_USBAsynchXfer.
* Description    : send data to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void Handle_USBAsynchXfer (void)
{
  uint16_t USB_Tx_ptr,USB_Tx_length,USB_Tx_Count;
  static uint16_t USB_TBuffer_out = 0;
  
  if(USB_Tx_State) return;
  
  if (USB_TBuffer_out == USB_TBuffer_Size) USB_TBuffer_out = 0;
    
  if(USB_TBuffer_out == USB_TBuffer_in) 
  {
      USB_Tx_State = 0; 
      return;
  }
  
  if(USB_TBuffer_out > USB_TBuffer_in) USB_Tx_Count = USB_TBuffer_Size - USB_TBuffer_out;
  else USB_Tx_Count = USB_TBuffer_in - USB_TBuffer_out;
  
  USB_Tx_ptr = USB_TBuffer_out;
  if (USB_Tx_Count > VIRTUAL_COM_PORT_DATA_SIZE)
  {
      USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
      USB_TBuffer_out += VIRTUAL_COM_PORT_DATA_SIZE;	
  }
  else
  {
      USB_Tx_length = USB_Tx_Count;
      USB_TBuffer_out += USB_Tx_length;
  }
  USB_Tx_State = 1; 
  UserToPMABufferCopy(&USB_TBuffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
  SetEPTxCount(ENDP1, USB_Tx_length);
  SetEPTxValid(ENDP1); 
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(uint32_t*)ID1;
  Device_Serial1 = *(uint32_t*)ID2;
  Device_Serial2 = *(uint32_t*)ID3;  

  Device_Serial0 += Device_Serial2;

  if (Device_Serial0 != 0)
  {
    IntToUnicode (Device_Serial0, &Virtual_Com_Port_StringSerial[2] , 8);
    IntToUnicode (Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
  }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA ) pbuf[ 2* idx] = (value >> 28) + '0';
    else pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    value = value << 4;
    pbuf[ 2* idx + 1] = 0;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
