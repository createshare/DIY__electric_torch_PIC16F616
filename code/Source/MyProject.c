/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MyProject.c
* �����ļ�-Dependencies:  	 MyProject.h; 	
* �ļ�����-File Description:	 ( Դ����-Source File)
	�� ������Ŀ: �ܹ��ܳ���
	01) ϵͳ״ֵ̬����
	02) EEPROM ��ַ����
	03) Flash ��ַ����   
	04) ������Ŀ�ı�������    
	05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)     ��02)     ��03)    ��04)    ��05)    ��06)      
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CSE  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CSE  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -ͷ�ļ�-Hardware specific definitions for Processor

#include "MyProject.h"	//������Ŀ: �ܹ��ܳ���-ͷ�ļ�




////////////////////////////////////////////////////////////////////////////
//==**"������Ŀ" ȫ�ֱ�������**Global variables**============//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 WorkFlagBits = 0;   //����ʱ,�õ��ı�־λ


unsigned char G_KeyCnt = 0; // ���ڰ���ѡ��˵�

unsigned char DutyCycleValue = 0; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char ChangeCnt = 0; //PWMռ�ձ�ֵ//��10msΪʱ��(SystemTick)


/****************************************************************************
*������-Function:		void  set_dutyCycle_ccp1_pwm(unsigned int dutyCycle) 
*����- Description:		����CCP1ģ���PWM�����ռ�ձ�
*�������-Input:	dutyCycle    
*�������-output:	None
*ע������-Note��	
	��01) dutyCycleֵ��Χ:0--100, ����0��ʾ0%������͵�ƽ;   100��ʾ100%��������ߵ�ƽ
	��02) ռ�ձ�=    (CCPR1L<7:0>:CCP1CON<5:4>)/(4* (PR2 + 1)) 
	        �ʣ�(CCPR1L<7:0>:CCP1CON<5:4> =ռ�ձ�*(4* (PR2 + 1)) 
	��03) 	��04) 
*****************************************************************************/
void  set_dutyCycle_ccp1_pwm(unsigned int dutyCycle)  //����CCP1ģ���PWM�����ռ�ձ�
{
	unsigned int pwm_Value;

	// �����"10",Ϊ10 = 4* (PR2 + 1)
	pwm_Value = dutyCycle * 10;   //care// PR2 = 249 //ռ�ձ�:0-100%,��ӦֵΪ0--1����65%=0.65

	
	CCPR1L =  pwm_Value /4;  //10λ�еĸ�8λֵ
	
	pwm_Value = pwm_Value % 4;
	pwm_Value = pwm_Value << 4;
	
	CCP1CON = pwm_Value + 0x0C;  //care// 0x0C=//����CCP1ģ��ΪPWM������ʽ����10λռ�ձȵĵ�2bitΪ00
}


/****************************************************************************
*������-Function:		void  close_ccp1_pwm(void)
*����- Description:		�ر�CCP1ģ���PWM���
*�������-Input:	None    
*�������-output:	None
*ע������-Note��	
	��01) 	��02)  	��03) 	��04) 
*****************************************************************************/
void  close_ccp1_pwm(void)  //�ر�CCP1ģ���PWM���
{
	TRISC5 = 1; //����RC5Ϊ�������ţ���PWM����� //RC5ΪCCP1ģ���PWM�������
}

/****************************************************************************
*������-Function:		void  open_ccp1_pwm(void)
*����- Description:		ʹ��CCP1ģ���PWM���
*�������-Input:	None    
*�������-output:	None
*ע������-Note��	
	��01) 	��02)  	��03) 	��04) 
*****************************************************************************/
void  open_ccp1_pwm(void)  //ʹ��CCP1ģ���PWM���
{
	TRISC5 = 0; //����RC5Ϊ������ţ���PWM����� //RC5ΪCCP1ģ���PWM�������
}


/****************************************************************************
*������-Function:		void  initial_ccp1_pwm(void)
*����- Description:		CCP1ģ���PWM������ʽ��ʹ���ӳ���
*�������-Input:	None    
*�������-output:	None
*ע������-Note��	
	��01) pwmģ�飬���ڵ��Դ���LED������
	            ����PWM ����Ϊ2 ms , ��ʼ�����ռ�ձ�Ϊ0%
	��02)  CCP1ģ���PWM�������ΪRC5 (����PIC16F616)
	��03) 	PR2 = 249 ;    TMR2 Ԥ��Ƶֵ= 16 ; 
	              ��  (CCPR1L<7:0>:CCP1CON<5:4>)���ֵ=4* (PR2 + 1)=1000 ��Ӧռ�ձ�Ϊ100%
	              ���� = 4 * TOSC * (PR2 + 1) * (TMR2 Ԥ��Ƶֵ) = 4*(1/8000000)*(249+1)*16 = 2 ms
			������ = TOSC * (CCPR1L<7:0>:CCP1CON<5:4>) * (TMR2 Ԥ��Ƶֵ)   
			ռ�ձ�=    (CCPR1L<7:0>:CCP1CON<5:4>)/(4* (PR2 + 1))
	��04) 
*****************************************************************************/
void  initial_ccp1_pwm(void)  //CCP1ģ���PWM������ʽ��ʹ���ӳ���
{ 
	

	//00 = ������� P1A �����ƣ�P1B��P1C ��P1D ����Ϊ�˿�����
	//CCP1CON<5:4>=00
	//1100 = PWMģʽ�� P1A ��P1C �ߵ�ƽ��Ч�� P1B ��P1D �ߵ�ƽ��Ч
	CCP1CON = 0x0C;    //����CCP1ģ��ΪPWM������ʽ����10λռ�ձȵĵ�2bitΪ00����8bitΪCCPR1L

	DutyCycleValue = 0; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
	set_dutyCycle_ccp1_pwm(DutyCycleValue);  //��ʼ��PWMռ�ձ�Ϊ0%��������͵�ƽ
	
	PR2 = 249;      //����PWM�Ĺ������ڲ���
	
	//TRISC5 = 0;  //����CCP1ģ���PWM�������ΪRC5����Ϊ�����ʽ

		//�򿪶�ʱ��TMR2��Ԥ��Ƶ��Ϊ16�����Ƶ��Ϊ1,ͬʱ��ʼ���PWM����
	T2CON = 0x07;  

	
	open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
}
    

/****************************************************************************
*������-Function:		void Bright_GradualChange(void)
*����- Description:		 ���ȵ���: ����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)���ڹ���: �ȱ���--> �ﵽ����-->�䰵-->�ﵽ�-->����
	��02)    ��03)    ��04)  
*****************************************************************************/
void Bright_GradualChange(void)  //���ȵ���: ����
{
	ChangeCnt ++;
	if(ChangeCnt >= M_CHANGE_TIME)  // ÿ"40ms" PWMռ�ձȼ�1���1//���ڽ����ٶ�// 10ms��ʱ��
	{
		ChangeCnt = 0;
	
		if(F_bright)
		{
			DutyCycleValue --;  //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
			if(DutyCycleValue == 0)  
			{
				F_bright = 0;
			}
		}
		else
		{
			DutyCycleValue ++;  //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
			if(DutyCycleValue >= 100) 
			{
				F_bright = 1;
			}
		}

		set_dutyCycle_ccp1_pwm(DutyCycleValue);   //����CCP1ģ���PWM�����ռ�ձ�		
	}
}


/****************************************************************************
*������-Function:		void Deal_Key(void)
*����- Description:		 ��������//care--����������Ч
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_Key(void)  // ��������//care--����������Ч
{
////////////////////////////////////////////////////////////////////////////
//==**��������"m��":�ɵ���������** ==//
//�ɿ��󣬱����������
	if(KeyBuffer != M_NullKey)
	{
		if(LongKeyCnt > M_ADJUST_KEY_TIME)  //����F_ADJUST_KEY_TIME��// 10ms��ʱ��
		{
			F_KeyRead = 0; 
			open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			Bright_GradualChange();  //���ȵ���: ����	
		}
	}

	//����m�����ϣ�ʹ�����n��ػ�ʧЧ
	if((KeyBuffer == M_NullKey)&&(LongKeyCnt > M_ADJUST_KEY_TIME))  
	{
		LongKeyCnt = 0;
	}

////////////////////////////////////////////////////////////////////////////
//==**��������"n��": �ػ�(�ص�)���������ߵ͹���** ===//
	if((KeyBuffer == M_NullKey)&&(LongKeyCnt > M_CLOSE_KEY_TIME))  //����M_CLOSE_TIME��// 10ms��ʱ��
	{
		F_KeyRead = 0; 
		G_KeyCnt = 0;
		
		G_WorkState = WORK_Close; //Work��"����LED"  ����: "Ϩ��"=  0 %ռ�ձ�
		DutyCycleValue = 0; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
	}

////////////////////////////////////////////////////////////////////////////
	if(KeyBuffer != M_NullKey)
	{
		LongKeyCnt ++;  //ʱ��Ϊ10ms
	}
	else LongKeyCnt = 0;


////////////////////////////////////////////////////////////////////////////
//==**�����̰�: �л�����״̬** ======================//
	if(F_KeyRead && (KeyBuffer == M_NullKey))  //�а������º󣬲��ɿ��󣬰�������Ч
	{
		F_KeyRead = 0; 
		
		G_KeyCnt ++ ;
		if(G_KeyCnt > 6)  G_KeyCnt = 0;  //"6" ��ʾ��6�ֹ���(̨��+�ֵ�Ͳ)
		
		switch(G_KeyCnt)
		{
			case 0: 
				G_WorkState = WORK_Close; //Work��"����LED"  ����: "Ϩ��"=  0 %ռ�ձ�
				DutyCycleValue = 0; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
				break;
				
			case 1: 
				G_WorkState = WORK_Brightest; //Work��"����LED"  ����: "��ǿ"=100%ռ�ձ�
				DutyCycleValue = 100; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
				break;

			case 2: 
				G_WorkState = WORK_Sub_Bright; //Work��"����LED"  ����: "��ǿ"= 70%ռ�ձ�
				DutyCycleValue = 70; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
				break;

			case 3: 
				G_WorkState = WORK_Sub_Dark; //Work��"����LED"  ����: "����"= 40%ռ�ձ�
				DutyCycleValue = 40; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
				break;
				
			case 4:
				G_WorkState = WORK_Darkest; //Work��"����LED"  ����: "����"= 10%ռ�ձ�
				DutyCycleValue = 10; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
				break;

			case 5: 
				G_WorkState = WORK_Flash; //Work��"����LED"  ����: "Ƶ��"
				DutyCycleValue = 100; //PWMռ�ձ�ֵ//��Χ:0<=ռ�ձ�<=100
				break;	
				
			case 6: 
				G_WorkState = WORK_Change; //Work��"����LED"  ����: "����"������-->����-->����
				DutyCycleValue = 50; //��50%��ʼ����: "����"
				break;
				
		///////////////////////////////////////////////////
			default : break;
		}
	}
}



/****************************************************************************
*������-Function:		void Deal_WorkState(void)
*����- Description:	 	"����"������Work��"״̬"�µ����� (״̬��)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_WorkState(void)
{

////////////////////////////////////////////////////////////////////////////
//==**��������: **0x8000--0x8FFF** =========================//
////////////////////////////////////////////////////////////////////////////

	switch(G_WorkState) 
	{
		case  WORK_IdleState: //Work������״̬(����ʱ)
			break;
			
		case  WORK_Close: //Work��"����LED"  ����: "Ϩ��"=  0 %ռ�ձ�
			set_dutyCycle_ccp1_pwm(DutyCycleValue);  //��ʼ��PWMռ�ձ�Ϊ0%��������͵�ƽ
			close_ccp1_pwm();  //�ر�CCP1ģ���PWM���
			
			NOP(); NOP(); NOP(); NOP();
			SLEEP();  //ʹ��MCU ��������
			NOP(); NOP(); NOP(); NOP();
			
			G_WorkState = WORK_IdleState;

			//care= Ҫ��������������󣬲����ڰ��°�����
			//ϵͳһ���ѵĵ�1�ΰ����Ϳ������ϴ򿪵ơ�
			//���û���������������Ѻ�Ҫ���ɿ�������
			//�ٰ�һ�ΰ��������ܴ򿪵ơ�
			KeyValue = M_NullKey;  
			F_KeyNull = 1;
			break;
			
		case  WORK_Brightest: //Work��"����LED"  ����: "��ǿ"=100%ռ�ձ�
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //����CCP1ģ���PWM�����ռ�ձ�
			open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			break;

		case  WORK_Sub_Bright: //Work��"����LED"  ����: "��ǿ"= 70%ռ�ձ�
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //����CCP1ģ���PWM�����ռ�ձ�
			open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			break;

		case  WORK_Sub_Dark: //Work��"����LED"  ����: "����"= 40%ռ�ձ�
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //����CCP1ģ���PWM�����ռ�ձ�
			open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			break;
			
		case  WORK_Darkest: //Work��"����LED"  ����: "����"= 10%ռ�ձ�
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //����CCP1ģ���PWM�����ռ�ձ�
			open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			break;
	
		case  WORK_Flash: //Work��"����LED"  ����: "Ƶ��"
				//��ʱ=250ms��100%ռ�ձ�//��ʱ=250ms�ĳ���
			set_dutyCycle_ccp1_pwm(DutyCycleValue);   //����CCP1ģ���PWM�����ռ�ձ�
			
			if(F_250ms_Turn)  open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			else  close_ccp1_pwm();  //�ر�CCP1ģ���PWM���
			break;		

		case  WORK_Change: //Work��"����LED"  ����: "����"������-->����-->����
			open_ccp1_pwm();  //ʹ��CCP1ģ���PWM���
			Bright_GradualChange();  //���ȵ���: ����	
			break;		


			
	///////////////////////////////////////////////////
		default : break;
	}
}


 
