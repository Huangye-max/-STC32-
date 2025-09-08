#include "headfile.h"
#define SEPWM_MAX 1350    //zuo
#define SEPWM_MIN 1070    //you
uint32 SE_Center_Value = 1210 ; //�����ֵ
uint32 SE_Value =0 ;      //���ֵ
float p=0.45;//0.475
float d=1;//1.05



void SEngine_pwm(int16 sepwm_data)//���ռ�ձ�
{
  //�޷�
  if(sepwm_data < SEPWM_MIN)
    sepwm_data = SEPWM_MIN; 
  else if(sepwm_data > SEPWM_MAX)
    sepwm_data = SEPWM_MAX;
  //���
  pwm_duty(PWMB_CH1_P74, sepwm_data);
}

void SEngine_out()
{    
	SE_Value = (int)(Error_S*p+Deviation_rate*d + SE_Center_Value);
  SEngine_pwm(SE_Value);	
}

void chaomifen()
{
	if(P72 == 0)
     {
       delay_ms(50); //������������ֹ��������
      if(P72 == 0)	
			 {
				  p=p+0.1;
			 }
		 }
				
	if(P71 == 0)
     {
       delay_ms(50); //������������ֹ��������
       if(P71 == 0)	
			 {
					p=p-0.1;
			 }
		 }
				
	if(P70 == 0)
     {
       delay_ms(50); //������������ֹ��������
       if(P70 == 0)	
				{
					d=d+1;
				}
		 }
				
	if(P73 == 0)
     {
       delay_ms(50); //������������ֹ��������
       if(P73 == 0)	
				{
					d=d-1;
				}
		 }
}

