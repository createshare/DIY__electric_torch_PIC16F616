/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MyProject.c
* 附属文件-Dependencies:  	 MyProject.h; 	
* 文件描述-File Description:	 ( 源程序-Source File)
	■ 具体项目: 总功能程序
	01) 系统状态值分配
	02) EEPROM 地址分配
	03) Flash 地址分配   
	04) 具体项目的变量定义    
	05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)     ▲02)     ▲03)    ▲04)    ▲05)    ▲06)      
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* 公司-Company: 			CSE  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CSE  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -头文件-Hardware specific definitions for Processor

#include "MyProject.h"	//具体项目: 总功能程序-头文件




////////////////////////////////////////////////////////////////////////////
//==**"具体项目" 全局变量定义**Global variables**============//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 WorkFlagBits = 0;   //工作时,用到的标志位


unsigned char G_KeyCnt = 0; // 用于按键选择菜单

unsigned char DutyCycleValue = 0; //PWM占空比值//范围:0<=占空比<=100


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char ChangeCnt = 0; //PWM占空比值//以10ms为时基(SystemTick)


/****************************************************************************
*函数名-Function:		void  set_dutyCycle_ccp1_pwm(unsigned int dutyCycle) 
*描述- Description:		设置CCP1模块的PWM输出的占空比
*输入参数-Input:	dutyCycle    
*输出参数-output:	None
*注意事项-Note：	
	▲01) dutyCycle值范围:0--100, 其中0表示0%即输出低电平;   100表示100%，即输出高电平
	▲02) 占空比=    (CCPR1L<7:0>:CCP1CON<5:4>)/(4* (PR2 + 1)) 
	        故，(CCPR1L<7:0>:CCP1CON<5:4> =占空比*(4* (PR2 + 1)) 
	▲03) 	▲04) 
*****************************************************************************/
void  set_dutyCycle_ccp1_pwm(unsigned int dutyCycle)  //设置CCP1模块的PWM输出的占空比
{
	unsigned int pwm_Value;

	// 下面的"10",为10 = 4* (PR2 + 1)
	pwm_Value = dutyCycle * 10;   //care// PR2 = 249 //占空比:0-100%,对应值为0--1，例65%=0.65

	
	CCPR1L =  pwm_Value /4;  //10位中的高8位值
	
	pwm_Value = pwm_Value % 4;
	pwm_Value = pwm_Value << 4;
	
	CCP1CON = pwm_Value + 0x0C;  //care// 0x0C=//设置CCP1模块为PWM工作方式，且10位占空比的低2bit为00
}


/****************************************************************************
*函数名-Function:		void  close_ccp1_pwm(void)
*描述- Description:		关闭CCP1模块的PWM输出
*输入参数-Input:	None    
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)  	▲03) 	▲04) 
*****************************************************************************/
void  close_ccp1_pwm(void)  //关闭CCP1模块的PWM输出
{
	TRISC5 = 1; //设置RC5为输入引脚，即PWM不输出 //RC5为CCP1模块的PWM输出引脚
}

/****************************************************************************
*函数名-Function:		void  open_ccp1_pwm(void)
*描述- Description:		使能CCP1模块的PWM输出
*输入参数-Input:	None    
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)  	▲03) 	▲04) 
*****************************************************************************/
void  open_ccp1_pwm(void)  //使能CCP1模块的PWM输出
{
	TRISC5 = 0; //设置RC5为输出引脚，即PWM可输出 //RC5为CCP1模块的PWM输出引脚
}


/****************************************************************************
*函数名-Function:		void  initial_ccp1_pwm(void)
*描述- Description:		CCP1模块的PWM工作方式初使化子程序
*输入参数-Input:	None    
*输出参数-output:	None
*注意事项-Note：	
	▲01) pwm模块，用于调试大功率LED的亮度
	            采用PWM 周期为2 ms , 初始化输出占空比为0%
	▲02)  CCP1模块的PWM输出引脚为RC5 (对于PIC16F616)
	▲03) 	PR2 = 249 ;    TMR2 预分频值= 16 ; 
	              故  (CCPR1L<7:0>:CCP1CON<5:4>)最大值=4* (PR2 + 1)=1000 对应占空比为100%
	              周期 = 4 * TOSC * (PR2 + 1) * (TMR2 预分频值) = 4*(1/8000000)*(249+1)*16 = 2 ms
			脉冲宽度 = TOSC * (CCPR1L<7:0>:CCP1CON<5:4>) * (TMR2 预分频值)   
			占空比=    (CCPR1L<7:0>:CCP1CON<5:4>)/(4* (PR2 + 1))
	▲04) 
*****************************************************************************/
void  initial_ccp1_pwm(void)  //CCP1模块的PWM工作方式初使化子程序
{ 
	

	//00 = 单输出； P1A 被调制；P1B、P1C 和P1D 配置为端口引脚
	//CCP1CON<5:4>=00
	//1100 = PWM模式； P1A 和P1C 高电平有效； P1B 和P1D 高电平有效
	CCP1CON = 0x0C;    //设置CCP1模块为PWM工作方式，且10位占空比的低2bit为00，高8bit为CCPR1L

	DutyCycleValue = 0; //PWM占空比值//范围:0<=占空比<=100
	set_dutyCycle_ccp1_pwm(DutyCycleValue);  //初始化PWM占空比为0%，即输出低电平
	
	PR2 = 249;      //设置PWM的工作周期参数
	
	//TRISC5 = 0;  //设置CCP1模块的PWM输出引脚为RC5引脚为输出方式

		//打开定时器TMR2，预分频比为16，后分频比为1,同时开始输出PWM波形
	T2CON = 0x07;  

	
	open_ccp1_pwm();  //使能CCP1模块的PWM输出
}
    

/****************************************************************************
*函数名-Function:		void Bright_GradualChange(void)
*描述- Description:		 亮度调节: 渐变
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)调节过程: 先变亮--> 达到最亮-->变暗-->达到最暗-->变亮
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Bright_GradualChange(void)  //亮度调节: 渐变
{
	ChangeCnt ++;
	if(ChangeCnt >= M_CHANGE_TIME)  // 每"40ms" PWM占空比加1或减1//调节渐变速度// 10ms的时基
	{
		ChangeCnt = 0;
	
		if(F_bright)
		{
			DutyCycleValue --;  //PWM占空比值//范围:0<=占空比<=100
			if(DutyCycleValue == 0)  
			{
				F_bright = 0;
			}
		}
		else
		{
			DutyCycleValue ++;  //PWM占空比值//范围:0<=占空比<=100
			if(DutyCycleValue >= 100) 
			{
				F_bright = 1;
			}
		}

		set_dutyCycle_ccp1_pwm(DutyCycleValue);   //设置CCP1模块的PWM输出的占空比		
	}
}


/****************************************************************************
*函数名-Function:		void Deal_Key(void)
*描述- Description:		 按键处理//care--按键弹起有效
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_Key(void)  // 按键处理//care--按键弹起有效
{
////////////////////////////////////////////////////////////////////////////
//==**按键长按"m秒":可调任意亮度** ==//
//松开后，保持这个亮度
	if(KeyBuffer != M_NullKey)
	{
		if(LongKeyCnt > M_ADJUST_KEY_TIME)  //长按F_ADJUST_KEY_TIME秒// 10ms的时基
		{
			F_KeyRead = 0; 
			open_ccp1_pwm();  //使能CCP1模块的PWM输出
			Bright_GradualChange();  //亮度调节: 渐变	
		}
	}

	//长按m秒以上，使下面的n秒关机失效
	if((KeyBuffer == M_NullKey)&&(LongKeyCnt > M_ADJUST_KEY_TIME))  
	{
		LongKeyCnt = 0;
	}

////////////////////////////////////////////////////////////////////////////
//==**按键长按"n秒": 关机(关灯)，进入休眠低功耗** ===//
	if((KeyBuffer == M_NullKey)&&(LongKeyCnt > M_CLOSE_KEY_TIME))  //长按M_CLOSE_TIME秒// 10ms的时基
	{
		F_KeyRead = 0; 
		G_KeyCnt = 0;
		
		G_WorkState = WORK_Close; //Work▓"大功率LED"  亮度: "熄灭"=  0 %占空比
		DutyCycleValue = 0; //PWM占空比值//范围:0<=占空比<=100
	}

////////////////////////////////////////////////////////////////////////////
	if(KeyBuffer != M_NullKey)
	{
		LongKeyCnt ++;  //时基为10ms
	}
	else LongKeyCnt = 0;


////////////////////////////////////////////////////////////////////////////
//==**按键短按: 切换工作状态** ======================//
	if(F_KeyRead && (KeyBuffer == M_NullKey))  //有按键按下后，并松开后，按键才有效
	{
		F_KeyRead = 0; 
		
		G_KeyCnt ++ ;
		if(G_KeyCnt > 6)  G_KeyCnt = 0;  //"6" 表示有6种功能(台灯+手电筒)
		
		switch(G_KeyCnt)
		{
			case 0: 
				G_WorkState = WORK_Close; //Work▓"大功率LED"  亮度: "熄灭"=  0 %占空比
				DutyCycleValue = 0; //PWM占空比值//范围:0<=占空比<=100
				break;
				
			case 1: 
				G_WorkState = WORK_Brightest; //Work▓"大功率LED"  亮度: "最强"=100%占空比
				DutyCycleValue = 100; //PWM占空比值//范围:0<=占空比<=100
				break;

			case 2: 
				G_WorkState = WORK_Sub_Bright; //Work▓"大功率LED"  亮度: "次强"= 70%占空比
				DutyCycleValue = 70; //PWM占空比值//范围:0<=占空比<=100
				break;

			case 3: 
				G_WorkState = WORK_Sub_Dark; //Work▓"大功率LED"  亮度: "次弱"= 40%占空比
				DutyCycleValue = 40; //PWM占空比值//范围:0<=占空比<=100
				break;
				
			case 4:
				G_WorkState = WORK_Darkest; //Work▓"大功率LED"  亮度: "最弱"= 10%占空比
				DutyCycleValue = 10; //PWM占空比值//范围:0<=占空比<=100
				break;

			case 5: 
				G_WorkState = WORK_Flash; //Work▓"大功率LED"  亮度: "频闪"
				DutyCycleValue = 100; //PWM占空比值//范围:0<=占空比<=100
				break;	
				
			case 6: 
				G_WorkState = WORK_Change; //Work▓"大功率LED"  亮度: "渐变"，渐亮-->渐暗-->渐亮
				DutyCycleValue = 50; //从50%开始亮度: "渐变"
				break;
				
		///////////////////////////////////////////////////
			default : break;
		}
	}
}



/****************************************************************************
*函数名-Function:		void Deal_WorkState(void)
*描述- Description:	 	"处理"各工作Work▓"状态"下的事务 (状态机)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_WorkState(void)
{

////////////////////////////////////////////////////////////////////////////
//==**工作运行: **0x8000--0x8FFF** =========================//
////////////////////////////////////////////////////////////////////////////

	switch(G_WorkState) 
	{
		case  WORK_IdleState: //Work▓空闲状态(工作时)
			break;
			
		case  WORK_Close: //Work▓"大功率LED"  亮度: "熄灭"=  0 %占空比
			set_dutyCycle_ccp1_pwm(DutyCycleValue);  //初始化PWM占空比为0%，即输出低电平
			close_ccp1_pwm();  //关闭CCP1模块的PWM输出
			
			NOP(); NOP(); NOP(); NOP();
			SLEEP();  //使能MCU 进入休眠
			NOP(); NOP(); NOP(); NOP();
			
			G_WorkState = WORK_IdleState;

			//care= 要加上这两条程序后，才能在按下按键后，
			//系统一唤醒的第1次按键就可以马上打开灯。
			//如果没有这两条程序，则唤醒后，要先松开按键后，
			//再按一次按键，才能打开灯。
			KeyValue = M_NullKey;  
			F_KeyNull = 1;
			break;
			
		case  WORK_Brightest: //Work▓"大功率LED"  亮度: "最强"=100%占空比
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //设置CCP1模块的PWM输出的占空比
			open_ccp1_pwm();  //使能CCP1模块的PWM输出
			break;

		case  WORK_Sub_Bright: //Work▓"大功率LED"  亮度: "次强"= 70%占空比
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //设置CCP1模块的PWM输出的占空比
			open_ccp1_pwm();  //使能CCP1模块的PWM输出
			break;

		case  WORK_Sub_Dark: //Work▓"大功率LED"  亮度: "次弱"= 40%占空比
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //设置CCP1模块的PWM输出的占空比
			open_ccp1_pwm();  //使能CCP1模块的PWM输出
			break;
			
		case  WORK_Darkest: //Work▓"大功率LED"  亮度: "最弱"= 10%占空比
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //设置CCP1模块的PWM输出的占空比
			open_ccp1_pwm();  //使能CCP1模块的PWM输出
			break;
	
		case  WORK_Flash: //Work▓"大功率LED"  亮度: "频闪"
				//亮时=250ms的100%占空比//暗时=250ms的常暗
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //设置CCP1模块的PWM输出的占空比
			
			if(F_250ms_Turn)  open_ccp1_pwm();  //使能CCP1模块的PWM输出
			else  close_ccp1_pwm();  //关闭CCP1模块的PWM输出
			break;		

		case  WORK_Change: //Work▓"大功率LED"  亮度: "渐变"，渐亮-->渐暗-->渐亮
			open_ccp1_pwm();  //使能CCP1模块的PWM输出
			Bright_GradualChange();  //亮度调节: 渐变	
			break;		


			
	///////////////////////////////////////////////////
		default : break;
	}
}


 
