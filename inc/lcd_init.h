#ifndef __LCD_INIT_H
#define __LCD_INIT_H

typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

#define USE_HORIZONTAL 0 
#define USE_HARDWARE_SPI 0
#define LCD_W 240
#define LCD_H 240

void LCD_GPIO_Init(void);
void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u16 dat);
void LCD_WR_REG(u8 dat);
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_Init(void);

#endif