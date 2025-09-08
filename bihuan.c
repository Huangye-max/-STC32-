#include "bihuan.h"
#include "SEEKFREE_VIRSCO.h"
//-------������
int16 templ_pluse =0;
int16 tempr_pluse =0;
//-------pid
PID pidl={500,0,0,0.3,1.1,2.2,0,0};
PID pidr={500,0,0,0.3,1.1,2.2,0,0};
//Ŀ��ֵ,ƫ��ֵ.��һ��ƫ��ֵ,p,i,d,����ֵ,���ֵ
//--------ccd
uint8 fazhi=211;
//---------���
uint16 djduty=750;
float djp=1.2;
float djd=2;
int8 djer=0;
int8 djerl=0;


void bmq()
{
	      //��ȡ�ɼ����ı�����������
    templ_pluse = ctimer_count_read(SPEEDL_PLUSE);
		tempr_pluse = ctimer_count_read(SPEEDR_PLUSE);

        //����������
    ctimer_count_clean(SPEEDL_PLUSE);
		ctimer_count_clean(SPEEDR_PLUSE);

        //�ɼ�������Ϣ
        if(1 == SPEEDL_DIR)    
        {
            templ_pluse = templ_pluse;
        }
        else                  
        {
            templ_pluse = -templ_pluse;
        }
		if(1 == SPEEDR_DIR)    
        {
            tempr_pluse = -tempr_pluse;
        }
        else                  
        {
            tempr_pluse = tempr_pluse;
        } 
}
int32 pidjisuanl(int16 actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	pidl.err = pidl.target_val - actual_val;
	
	/*������*/
	pidl.integral += pidl.err;	
	/*pidl�㷨ʵ��*/
	if(	pidl.integral>2500)
	{
		pidl.integral=2500;
	}
	if(pidl.integral<-2500)
	{
		pidl.integral=-2500;
	}
	pidl.output_val = pidl.p * pidl.err + 
				     pidl.i * pidl.integral + 
				     pidl.d * (pidl.err - pidl.err_last);

	/*����*/
	pidl.err_last = pidl.err;

	/*���ص�ǰʵ��ֵ*/
	return pidl.output_val;
}
int32 pidjisuanr(int16 actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	pidr.err = pidr.target_val - actual_val;
	
	/*������*/
	pidr.integral += pidr.err;	
	/*pidr�㷨ʵ��*/
if(	pidr.integral>2500)
	{
		pidr.integral=2500;
	}
	if(pidr.integral<-2500)
	{
		pidr.integral=-2500;
		
	}

	pidr.output_val = pidr.p * pidr.err + 
				     pidr.i * pidr.integral + 
				     pidr.d * (pidr.err - pidr.err_last);
	
	/*����*/
	pidr.err_last = pidr.err;

	/*���ص�ǰʵ��ֵ*/
	return pidr.output_val;
}

void pidlz() //����pid
{
	int32 pwml=0;
	int32 pwmr=0;	
	
// put_int32(1,templ_pluse);
//	 put_int32(2,tempr_pluse);
//	 put_int32(3,pidl.target_val);
//	 put_int32(4,pidr.target_val);
	pwml=pidjisuanl(templ_pluse);
	pwmr=pidjisuanr(tempr_pluse);
	   
	if(pwml>0)
	{
		if(pwml>8000)
		{
		pwm_duty(PWMA_CH1P_P60, 0);
		pwm_duty(PWMA_CH2P_P62, 8000);
		}
		else 					
		{	
		pwm_duty(PWMA_CH1P_P60, 0);
		pwm_duty(PWMA_CH2P_P62, pwml);
		}
		}
		
	else
	{
		if(pwml<-8000)
		{	
		pwm_duty(PWMA_CH1P_P60, 0);
		pwm_duty(PWMA_CH2P_P62, -8000);
		}
		else 					
		{	
		pwm_duty(PWMA_CH1P_P60,0);
		pwm_duty(PWMA_CH2P_P62, -pwml);
		}
	}
	if(pwmr>0)
	{
		if(pwmr>8000) 
		{	
		pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, 8000);
		}
		
		else 					
		{	
		pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, pwmr);
		}
	}
	else
	{
		if(pwmr<-8000)
		{	
		pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, 8000);
		}
		else 					
		{	
		pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, -pwmr);
		}
	}
	
}

//void pingmu()
//{
//uint8 aa=0;
//lcd_showint16(0,0,templ_pluse);//��������
//lcd_showint16(50,0,tempr_pluse);//��������
//lcd_showint16(0,1,djduty);
//lcd_showuint8(0,2,fazhi);
//for(aa=0;aa<128;aa++)						//��ʾccd1
//			{
//				if(ccd_data[aa]<fazhi)
//				{ccd_data[aa]=0;
//					lcd_drawpoint(aa,140,BLACK);
//				}
//								
//						else
//						{ccd_data[aa]=1;							
//							lcd_drawpoint(aa,140,WHITE);
//						}
//			}
//}

//void shibie()
//{
//	uint8 b=0;
//	uint8 bb=0;
//	djduty=750;
//	
//	
//	for(bb=0;bb<126;bb++)
//	{
//		if(ccd_data[0]==	  0 &&
//			 ccd_data[1]==	  0 &&
//			 ccd_data[126]==	0 &&
//			 ccd_data[127]==	0 )
//		{	
//		if(	ccd_data[bb]==	0 &&
//				ccd_data[bb+1]==0 &&
//				ccd_data[bb+2]==1 &&
//				ccd_data[bb+3]==1 )
//		
//		{
//			for(b=bb+1;b<126;b++)
//			{
//				if(ccd_data[b]==  1 &&
// 					 ccd_data[b+1]==1 &&
//					 ccd_data[b+2]==0 &&
//					 ccd_data[b+3]==0 )
//				{
//					djer=60-(b+bb+3)/2;
//					djduty+=djp*djer+djd*(djer-djerl);
//					djerl=djer;
//					if(djduty>835)djduty=835;
//					if(djduty<665)djduty=665;
//					pwm_duty(PWMB_CH1_P74, djduty);
//				}
//			}
//			
//		}
//		}
//		if(ccd_data[0]==	  1 &&
//			 ccd_data[1]==	  1 &&
//			 ccd_data[126]==	0 &&
//			 ccd_data[127]==	0 )
//		{
//			pwm_duty(PWMB_CH1_P74, 835);
//		}
//		if(ccd_data[0]==	  0 &&
//			 ccd_data[1]==	  0 &&
//			 ccd_data[126]==	1 &&
//			 ccd_data[127]==	1 )
//		{
//			pwm_duty(PWMB_CH1_P74, 665);
//		}
//	}	
//}