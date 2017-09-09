#ifndef __HW_USBUART_H
#define __HW_USBUART_H
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ³õÊ¼»¯USBÐéÄâ´®¿Ú
  */
#include "hw_config.h"
void HW_USB_Init(void);
#define HW_USB_write USB_Send_Data
#define HW_USB_read USB_Read_RBuffer
#define HW_USB_get_rx_buffer_count USB_RBuffer_Count
#define HW_USB_reset_read_buffer USB_Reset_RBuffer

#endif