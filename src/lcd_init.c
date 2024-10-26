#include "lcd_init.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_spi.h>

// todo：SPI_BUS_NAME要从脚本里边获取宏定义
#define SPI_BUS_NUM			0
#define SPI_BUS_NAME   		PKG_USING_GC9A01_SPI_BUS_NAME
#define SPI_DEV_NAME(a,b)	a#b
#define RES_PIN     		PKG_USING_GC9A01_RES_PIN
#define DC_PIN      		PKG_USING_GC9A01_DC_PIN
#define CS_PIN      		PKG_USING_GC9A01_CS_PIN

#define LCD_RES_Clr()  		rt_pin_write(RES_PIN, PIN_LOW)
#define LCD_RES_Set()  		rt_pin_write(RES_PIN, PIN_HIGH)

#define LCD_DC_Clr()   		rt_pin_write(DC_PIN, PIN_LOW)
#define LCD_DC_Set()   		rt_pin_write(DC_PIN, PIN_HIGH)

#define LCD_BLK_Clr()  {}
#define LCD_BLK_Set()  {}

static struct rt_spi_device *spi_device;

void LCD_GPIO_Init(void)
{
	struct rt_spi_configuration cfg;

	// pin assignment
	rt_pin_mode(RES_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(DC_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(CS_PIN, PIN_MODE_OUTPUT);

    rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_DEV_NAME(PKG_USING_GC9A01_SPI_BUS_NAME, SPI_BUS_NUM), CS_PIN);
    
    spi_device = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME(PKG_USING_GC9A01_SPI_BUS_NAME, SPI_BUS_NUM));
    if (!spi_device)
    {
        rt_kprintf("can't find %s device!\n", SPI_BUS_NAME);
    }

    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 12* 1000 * 1000; 
    rt_spi_configure(spi_device, &cfg);
}

void LCD_Writ_Bus(u8 dat) 
{	
    rt_uint8_t recv_buf;
    rt_spi_transfer(spi_device, &dat, &recv_buf, 1);
}

void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}

void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}

void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();
	LCD_Writ_Bus(dat);
	LCD_DC_Set();
}

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	LCD_WR_REG(0x2a);
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2b);
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2);
	LCD_WR_REG(0x2c);
}

void LCD_Init(void)
{
	LCD_GPIO_Init();
	LCD_RES_Clr();
	rt_thread_mdelay(100);
	LCD_RES_Set();
	rt_thread_mdelay(100);
	
	LCD_BLK_Set();
  	rt_thread_mdelay(100);
	
	LCD_WR_REG(0xEF);
	LCD_WR_REG(0xEB);
	LCD_WR_DATA8(0x14); 
  	LCD_WR_REG(0xFE);			 
	LCD_WR_REG(0xEF); 
	LCD_WR_REG(0xEB);	
	LCD_WR_DATA8(0x14); 
	LCD_WR_REG(0x84);			
	LCD_WR_DATA8(0x40); 
	LCD_WR_REG(0x85);			
	LCD_WR_DATA8(0xFF); 
	LCD_WR_REG(0x86);			
	LCD_WR_DATA8(0xFF); 
	LCD_WR_REG(0x87);			
	LCD_WR_DATA8(0xFF);
	LCD_WR_REG(0x88);			
	LCD_WR_DATA8(0x0A);
	LCD_WR_REG(0x89);			
	LCD_WR_DATA8(0x21); 
	LCD_WR_REG(0x8A);			
	LCD_WR_DATA8(0x00); 
	LCD_WR_REG(0x8B);			
	LCD_WR_DATA8(0x80); 
	LCD_WR_REG(0x8C);			
	LCD_WR_DATA8(0x01); 
	LCD_WR_REG(0x8D);			
	LCD_WR_DATA8(0x01); 
	LCD_WR_REG(0x8E);			
	LCD_WR_DATA8(0xFF); 
	LCD_WR_REG(0x8F);			
	LCD_WR_DATA8(0xFF); 
	LCD_WR_REG(0xB6);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x20);

	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x68);
	else LCD_WR_DATA8(0xA8);

	LCD_WR_REG(0x3A);			
	LCD_WR_DATA8(0x05);
	LCD_WR_REG(0x90);			
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08); 

	LCD_WR_REG(0xBD);			
	LCD_WR_DATA8(0x06);
	
	LCD_WR_REG(0xBC);			
	LCD_WR_DATA8(0x00);	

	LCD_WR_REG(0xFF);			
	LCD_WR_DATA8(0x60);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x04);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA8(0x13);
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA8(0x13);

	LCD_WR_REG(0xC9);			
	LCD_WR_DATA8(0x22);

	LCD_WR_REG(0xBE);			
	LCD_WR_DATA8(0x11); 

	LCD_WR_REG(0xE1);			
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x0E);

	LCD_WR_REG(0xDF);			
	LCD_WR_DATA8(0x21);
	LCD_WR_DATA8(0x0c);
	LCD_WR_DATA8(0x02);

	LCD_WR_REG(0xF0);   
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_REG(0xF1);    
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37);  
 	LCD_WR_DATA8(0x6F);


 	LCD_WR_REG(0xF2);   
 	LCD_WR_DATA8(0x45);
 	LCD_WR_DATA8(0x09);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_REG(0xF3);   
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37); 
 	LCD_WR_DATA8(0x6F);

	LCD_WR_REG(0xED);	
	LCD_WR_DATA8(0x1B); 
	LCD_WR_DATA8(0x0B); 

	LCD_WR_REG(0xAE);			
	LCD_WR_DATA8(0x77);
	
	LCD_WR_REG(0xCD);			
	LCD_WR_DATA8(0x63);		


	LCD_WR_REG(0x70);			
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x03);

	LCD_WR_REG(0xE8);			
	LCD_WR_DATA8(0x34);

	LCD_WR_REG(0x62);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xED);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xEF);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0x63);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF3);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0x64);			
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x29);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x07);

	LCD_WR_REG(0x66);			
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xCD);
	LCD_WR_DATA8(0x67);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);

	LCD_WR_REG(0x67);			
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x32);
	LCD_WR_DATA8(0x98);

	LCD_WR_REG(0x74);			
	LCD_WR_DATA8(0x10);	
	LCD_WR_DATA8(0x85);	
	LCD_WR_DATA8(0x80);
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x4E);
	LCD_WR_DATA8(0x00);					
	
  	LCD_WR_REG(0x98);			
	LCD_WR_DATA8(0x3e);
	LCD_WR_DATA8(0x07);

	LCD_WR_REG(0x35);	
	LCD_WR_REG(0x21);

	LCD_WR_REG(0x11);
	rt_thread_mdelay(120);
	LCD_WR_REG(0x29);
	rt_thread_mdelay(20);
} 