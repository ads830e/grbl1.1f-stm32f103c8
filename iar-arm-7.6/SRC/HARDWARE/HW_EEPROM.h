#ifndef __HW_EEPROM_h
#define __HW_EEPROM_h

//##############################【API】##############################
void HW_EEPROM_Init(void);			//EEPROM初始化

unsigned char HW_EEPROM_getChar(unsigned int addr);				   //EEPROM读取一个u8数据
void HW_EEPROM_putChar(unsigned int addr,unsigned char new_value); //EEPROM写入一个u8数据

#endif
