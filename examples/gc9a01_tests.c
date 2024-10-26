/*
 * Copyright (c) 2024, hywing <hywing@aliyum.com>
 *
 * SPDX-License-Identifier: MIT License
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-15     hywing       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "stdlib.h"
#include "lcd.h"
#include "lcd_init.h"

void oled_test(void)
{
    int j = 0;

    LCD_Init();

    LCD_Fill(0, 0, 240, 240, BLACK);

    while(1) {
        for(int i = 0; i < 240; i += 10) {
            Draw_Circle(120, 120, i, 400 * j);
        }
        if(j++ > 65536 / 400) {
            j = 0;
        }

        rt_thread_mdelay(1);
    }
}

MSH_CMD_EXPORT(oled_test, "LCD example to run");