[TOC]

# 台灯/手电功能描述

自制 700mA 多功能台灯+手电筒 (9档功能；PWM载波；USB、锂电池供电)（基于PIC16F616）。

9 档功能，如下所示：

- 第 1 档：LED亮度: 熄灭=休眠低功耗  

- 第 2 档：亮度: 最强=700 mA   

- 第 3 档： LED亮度: 次强= 490 mA 

- 第 4 档：LED亮度: 次弱= 280 mA    

- 第 5 档：亮度: 最弱= 70 mA 

- 第 6 档：LED亮度: 250msm周期频闪 

- 第 7 档：LED亮度: 暗->亮->暗渐变 

- 第 8 档： 长按2秒: 关机熄灯 

- 第 9 档： 长按4秒: 亮度自动调节

![自制 700mA 多功能台灯+手电筒](figures/自制 700mA 多功能台灯+手电筒.png)



# 硬件相关

## 硬件用到的主要模块

- PIC16F616 微控制器：
  - 14 引脚、8位 CMOS 闪存单片机。
  - 2 MB Flash（用于存代码），128 字节 SRAM。
  - 主要用到了 PWM 模块和定时器模块。
  - 外接一个机械按键，作为输入。

- 7135 恒流驱动器，或者 TL431（三端可编程并联稳压二极管）

## 硬件原理图

![PIC16F616_自制700mA多功能台灯+手电筒 (9档功能、低功耗休眠、 USB供电、锂电池供电)](figures/PIC16F616_自制700mA多功能台灯+手电筒 (9档功能、低功耗休眠、 USB供电、锂电池供电).jpg)

# 软件相关

- MapLab IDE 软件；

- HI-TECH C编译器；

- C语言。

  

# 联系方式 & 感谢

- 维护：createshare@163.com 
- 主页：https://blog.csdn.net/blues_123
- DIY 开源项目仓库：
  - https://gitee.com/createshare/DIY__electric_torch_PIC16F616
  - https://github.com/createshare/DIY__electric_torch_PIC16F616

