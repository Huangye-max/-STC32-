#include "headfile.h"
void xianshi()
{	     
   lcd_showstr(0,1,"ADC1 :");   lcd_showint32(6*8,1,(int)Normalize_Value[0],4);  lcd_showint32(11*8,1,adc_once(ADC_P16,ADC_12BIT),4);//6,11为列，1为行
   lcd_showstr(0,2,"ADC2 :");   lcd_showint32(6*8,2,(int)Normalize_Value[1],4);  lcd_showint32(11*8,2,adc_once(ADC_P05,ADC_12BIT),4);
   lcd_showstr(0,3,"ADC3 :");   lcd_showint32(6*8,3,(int)Normalize_Value[2],4);  lcd_showint32(11*8,3,adc_once(ADC_P01,ADC_12BIT),4);
   lcd_showstr(0,4,"ADC4 :");   lcd_showint32(6*8,4,(int)Normalize_Value[3],4);  lcd_showint32(11*8,4,adc_once(ADC_P13,ADC_12BIT),4);
	 lcd_showstr(0,5,"ES :");	    lcd_showfloat(6*8,5,Error_S,4,3); 
	 lcd_showstr(0,6,"f :");      lcd_showint32(6*8,6,f,1);
	 lcd_showstr(0,7,"huan :");   lcd_showint32(6*8,7,huan,1);
 	 lcd_showstr(0,8,"all :");    lcd_showint32(6*8,8,ADraw[0]+ADraw[1]+ADraw[2]+ADraw[3],5);	
}
//void xianshiqt()
//{
//  lcd_showstr(0,1,"p=");      lcd_showfloat(6*8,1,p,2,1);
//  lcd_showstr(0,2,"d=");		  lcd_showint32(6*8,2,d,2);
//}

//void xianshi()
//{	     
//   lcd_showstr(0,1,"16:");   lcd_showint32(6*8,1,adc_once(ADC_P16,ADC_12BIT),4);//6,11为列，1为行
//   lcd_showstr(0,2,"05:");   lcd_showint32(6*8,2,adc_once(ADC_P05,ADC_12BIT),4);
//   lcd_showstr(0,3,"14:");   lcd_showint32(6*8,3,adc_once(ADC_P14,ADC_12BIT),4);
//   lcd_showstr(0,4,"01:");   lcd_showint32(6*8,4,adc_once(ADC_P01,ADC_12BIT),4);
//	 lcd_showstr(0,5,"13:");   lcd_showint32(6*8,5,adc_once(ADC_P13,ADC_12BIT),4);	
//	 lcd_showstr(0,6,"00:");   lcd_showint32(6*8,6,adc_once(ADC_P00,ADC_12BIT),4);
//	 lcd_showstr(0,7,"06:");   lcd_showint32(6*8,7,adc_once(ADC_P06,ADC_12BIT),4);
//	 lcd_showstr(0,8,"15:");   lcd_showint32(6*8,8,adc_once(ADC_P15,ADC_12BIT),4);
//}

//void shaocha()
//	{
//		lcd_showstr(0,1,"actulz=");       lcd_showint32(6*8,1,templ_pluse,2);
//    lcd_showstr(0,2,"actuly=");		    lcd_showint32(6*8,2,tempr_pluse,2);
//		lcd_showstr(0,3,"xinhaoz=");      lcd_showint32(6*8,3,pwml,2);
//    lcd_showstr(0,4,"xinhaoy=");		  lcd_showint32(6*8,4,pwmr,2);
//	}
	
	
int b=0;
void anjian()
{	
	if(P72 == 0)//KEY0
    {
      delay_ms(20);//按键消抖，防止按下许多次
      if(P72 == 0)	
			  {
					if(b==0||b==2)  b=1;
					else	b=2;				
				}
		}
				
	switch(b)
	{
		case 1:
		xianshi();	
		break;
		case 2:
		lcd_clear(YELLOW);	
    break;					
	}	
}