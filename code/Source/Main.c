/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
◆项目-Project:			多功能强光台灯&手电筒Table lamp & Electric Torch
                                                    支持USB供电、外接电源、锂电池供电
◆设计者-Author:		BlueS
◆处理器-Processor: 		Microchip  PIC16F616    
◆编译器-Complier: 		HI_TECH_PICC9.82  or higher
◆仿真器-IDE: 			MPLAB IDE v8.76  or higher
◆版本-Version: 			V1.0
◆日期-Date: 			2013-12-28
①②③④⑤⑥⑦⑧⑨⑩
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 文件名-FileName:			 Main.c
* 附属文件-Dependencies:  	 
* 文件描述-File Description:	 ( 源程序-Source File)
	■01)  PIC16F616:
			程序存储器（闪存）：2048字 = 4096字节
			数据存储器（SRAM）：128字节
			I/O：11个；
			AD通道：8路10位A/D；
			比较器：2个；
			8/16位定时器：2/1；
			电压范围：2.0～5.5V

	■02)  系统频率8.00MHz Internal Clock
	■03)   使用了"2颗"7135_350mA_恒流LED驱动芯片
	             故最大可输出700mA的电流(LED亮度最强)
	■04)   MCLR 引脚作为复位引脚(若不作为复位引脚。则此引脚只作输入引脚)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01) 高性能RISC CPU：
- 8层深硬件堆栈、可编程代码保护
- 上电复位、上电延时定时器、振荡器起振定时器、欠压复位、
- 带独立振荡器的看门狗定时器
-最高工作频率：DC－ 20 MHz 振荡器/ 时钟输入；  用户可选择频率范围：4 MHz 或8 MHz
-PIC16F610/616：2.0V 到5.5V  ; PIC16HV610/616：2.0V 到用户定义的最大值

	▲02) 低功耗特性：
-待机电流：2.0V时典型值为50 nA；  
-工作电流：32kHz、2.0V 时典型值为20 μA； 4MHz、2.0V 时典型值为220 μA
-看门狗定时器电流：2.0V时典型值为1 μA

	▲03) I/O 引脚特性：	  
-11个I/O 引脚和1 个只能用作输入的引脚、带弱上拉的主复位引脚、
-高灌/ 拉电流能力，可直接驱动LED、电平变化中断引脚、可单独编程的弱上拉

	▲04)模拟比较器模块
- 2个模拟比较器
- 片上可编程参考电压（CVREF）模块（VDD的%）
- 固定参考电压
- 可从外部访问比较器输入和输出
- SR锁存器
- 内建滞后（用户可选择）	

	▲05) Timer0 ：带有8位可编程预分频器的8位定时器/ 计数器
	
	▲06) 增强型Timer1：
- 带有预分频器的16 位定时器/ 计数器
- 外部Timer1 门控（计数使能）
- 如果选用INTOSC 模式，可选择OSC1 和OSC2 之间的振荡器
 （工作在LP 模式下）作为Timer1 的振荡器
- Timer1振荡器	  

	▲07) Timer2：带有8 位周期寄存器、预分频器和后分频
器的8 位定时器/ 计数器	

	▲08)增强型捕捉、比较和PWM 模块：
- 16位捕捉，最大精度12.5 ns
- 16位比较，最大精度200 ns
- 10位PWM，带有1、2 或4 路输出通道及可编程“死区”，最高频率20 kHz

	▲09)A/D转换器：
- 10位精度
- 8路外部输入通道
- 2路内部参考通道	

	▲10)
	▲09)
	▲09)通过两个引脚进行在线串行编程（In-Circuit Serial ProgrammingTM， ICSPTM）		
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS      2013-12-28	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* 公司-Company: 			CSE  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CSE  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -头文件-Hardware specific definitions for Processor



__CONFIG (0xff84);        //选择内部振荡，内部振荡器频率选择位IOSCFS=1=8MHz，
                                             //禁止WDT  //令FOSC2＝1，FOSC1＝0，FOSC0＝0，
                                             //选INTOSCIO振荡，使RA4和RA5作为I/O口
                                             
//__CONFIG (0xffA4);       //增加//1 = MCLR 引脚功能为MCLR

//__CONFIG (0xff04);  //选择内部振荡，内部振荡器频率选择位IOSCFS=0=4MHz，
                                              //令FOSC2＝1，FOSC1＝0，FOSC0＝0，
                                             //选INTOSCIO振荡，使RA4和RA5作为I/O口
                                             
//bit ON,fZheng,fFan,fSB1,fLongKey;


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**===========================//
////////////////////////////////////////////////////////////////////////////


 /****************************************************************************
*函数名-Function:		void  interrupt  INTS(void)
*描述- Description:		中断服务总程序
*输入参数-Input:	None    
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void  interrupt  INTS(void)
{
	if(T0IF == 1)   //Timer0定时器中断服务程序(作为系统滴答时钟System Tick)
	{ 
		T0IF = 0; //清中断标志位
		TMR0 = 0xD0;  //每 1ms定时中断一次
		
		System_Clock();  //通用"系统时钟"处理: 产生定时为1ms,10ms, 20ms, 100ms,等
//RC0 =!RC0;		
	}  

		//PORTA 电平变化中断，主要用于通过按键将MCU 从休眠中唤醒
	if(RAIF == 1)  //PORTA 电平变化中断标志位//1 = 至少有一个PORTA <5:0> 引脚状态发生变化时（必须用软件清零）
	{
		RAIF = 0;  //清中断标志位
	}
	
}


/****************************************************************************
*函数名-Function:	int main(void)
*描述- Description:	主函数
*输入参数-Input:	None    
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
int main(void)
{  
	system_initial();  //系统初使化 :单片机内部资源+外部基本资源的初使化

	//==系统一上电，让进入==// WORK_Close; //Work▓"大功率LED"  亮度: "熄灭"=  0 %占空比
	G_KeyCnt = 0;
	G_WorkState = WORK_Close; //Work▓"大功率LED"  亮度: "熄灭"=  0 %占空比
	DutyCycleValue = 0; //PWM占空比值//范围:0<=占空比<=100

	while(1)
	{  
	////////////////////////////////////////////////////////////////////////////
	//==**系统每10ms"循环"执行一次程序**===================//
		System_GetLoopClockTick(); //每次"死等"延时10ms后，系统"循环"执行一次程序

//RC1 =!RC1;
	////////////////////////////////////////////////////////////////////////////
	//==**"按键处理**================//
		Deal_Key(); // 按键处理

	////////////////////////////////////////////////////////////////////////////
	//==**"处理"各工作Work▓"状态"下的事务**===============//
		Deal_WorkState(); // "处理"各工作Work▓"状态"下的事务 (状态机)

	}
}
 // 并让系统，进入待机或休眠状态

