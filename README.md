# rtt-gc9a01

RT-Thread package for working with TFT LCD based on  SPI inspired by [GC9A01](https://gitee.com/meta-mcu/gc9a01-tft)

## 1、介绍

GC9A01是一款1.28寸的圆形TFT显示屏模块，分辨率为240x240，支持三种颜色格式：RGB444、RGB565、RGB666

### 1.1 目录结构

| 名称     | 说明       |
| -------- | ---------- |
| examples | 例子目录   |
| inc      | 头文件目录 |
| src      | 源代码目录 |

### 1.2 许可证

gc9a01软件包遵循 MIT 许可，详见 `LICENSE` 文件

## 2、获取rtt-gc9a01 软件包

使用这个软件包的前提是你得有成功移植的RT-Thread spi驱动和数量足够的GPIO，请先用menuconfig工具使能spi驱动

```
Hardware Drivers Config --->
	On-chip Peripheral Drivers --->
		[*] Enable SPI
		[*]		Enable SPI0
```

使用 gc9a01 package 需要在 RT-Thread 的包管理器中选择它，具体路径如下

```
RT-Thread online packages --->
    peripheral libraries and drivers --->
        [*] gc9a01: TFT LCD based on GC9A01 IC driver  --->
```

GPIO及SPI接口设置

```
(spi0) SPI bus name
(97) DC PIN number for example in frdm-mcxa153 board P3_1 -> 3*32+1
(126) RES PIN number for example in frdm-mcxa153 board P3_30 -> 3*32+30
(35) CS PIN number for example in frdm-mcxa153 board P1_3 -> 1*32+3
[*] Enable gc9a01 example
    Version (latest)  --->
```

然后使用 `pkgs --update` 命令更新包到 BSP 中

```bash
pkgs --update
scons --target=mdk5
```

## 3、API 说明

### 背景颜色

```c
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
```

### 绘制点

```c
void LCD_DrawPoint(u16 x,u16 y,u16 color);
```

### 绘制线段

```c
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
```

### 绘制矩形

```c
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
```

### 绘制圆形

```c
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);
```

## 4、联系方式

- 维护：hywing.sir@qq.com
- 主页：<https://github.com/hywing/rtt-gc9a01.git>

## 5、说明

这个软件包在NXP [FRDM-MCXA153](https://www.nxp.com.cn/design/design-center/development-boards-and-designs/FRDM-MCXA153)开发板上面测试通过

![](./intro.png)
