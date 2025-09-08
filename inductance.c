#include "headfile.h"
#include<math.h>
#define maxsize 10000
uint16 ADC_Min[4]={10,10,10,10};//最小值             207 352  477 294
uint16 ADC_Max[4]={2600,2050,2050,3350};//最大值          1215  875  1036 950
float Filter_Value[4]={0,0,0,0}; //滤波值
float Normalize_Value[4]={0,0,0,0};//归一化值
uint16 ADraw[4];
 //偏差计算
float Error_S=0,Last_Error_S=0;
float Deviation_rate=0;//偏差变化率
uint8 flag=0,flag1=0;
uint16 Mean_Val[4];   //均值	
int dat=0;
int mid;
int z=0;
int zuo;
int you;
int huan=0;
int f=0;
int yuan=0;
int ting=0;
//int shch=0;

void adc()//adc模块初始化
{
	adc_init(ADC_P16,ADC_SYSclk_DIV_32);
	adc_init(ADC_P15,ADC_SYSclk_DIV_32);
	adc_init(ADC_P01,ADC_SYSclk_DIV_32);
	adc_init(ADC_P05,ADC_SYSclk_DIV_32);
	adc_init(ADC_P13,ADC_SYSclk_DIV_32);
	adc_init(ADC_P14,ADC_SYSclk_DIV_32);
	adc_init(ADC_P00,ADC_SYSclk_DIV_32);
	adc_init(ADC_P06,ADC_SYSclk_DIV_32);
}
void Collect_ADC()  //adc采集
{
  uint8 k,i,j;
  uint16 temp;
   static uint16 ADC_Temp[4][5];//AD采集数组
   uint16 Mean_Val[4];   //均值
  static uint16 Slide_AD[5][8];//滑动数组
  uint16 Slide_Sum[4]={0};//滑动值和  
  for(i=0;i<5;i++)       //取AD值
  {
    ADraw[0]=ADC_Temp[0][i]=adc_once(ADC_P16,ADC_12BIT);
    ADraw[1]=ADC_Temp[1][i]=adc_once(ADC_P05,ADC_12BIT);
    ADraw[2]=ADC_Temp[2][i]=adc_once(ADC_P01,ADC_12BIT);
    ADraw[3]=ADC_Temp[3][i]=adc_once(ADC_P13,ADC_12BIT);
  }
  mid=adc_once(ADC_P15,ADC_12BIT); 
	zuo=adc_once(ADC_P16,ADC_12BIT); 
	you=adc_once(ADC_P13,ADC_12BIT); 
  for(k=0;k<4;k++)
  {
    for(i=0;i<4;i++)
    {
      for(j=0;j<5-i;j++)
      {
          if(ADC_Temp[k][j]>ADC_Temp[k][j+1])
          {
            temp=ADC_Temp[k][j];
            ADC_Temp[k][j]=ADC_Temp[k][j+1];
            ADC_Temp[k][j+1]=temp;
          }
        }
      }
   }
  
  
   for(i=0;i<4;i++)
   {
     Mean_Val[i]=(uint16)((float)(ADC_Temp[i][0]+ADC_Temp[i][1]+ADC_Temp[i][2]+ADC_Temp[i][3])/4.0);
   }
   for(k=0;k<8;k++)
   {
      Slide_AD[0][k]=Slide_AD[0][k+1];//滑动
      Slide_AD[1][k]=Slide_AD[1][k+1]; 
      Slide_AD[2][k]=Slide_AD[2][k+1]; 
      Slide_AD[3][k]=Slide_AD[3][k+1];

      Slide_Sum[0]+=Slide_AD[0][k];       //求和
      Slide_Sum[1]+=Slide_AD[1][k];
      Slide_Sum[2]+=Slide_AD[2][k];
      Slide_Sum[3]+=Slide_AD[3][k];

   }
   for(k=0;k<4;k++)
   {
      Slide_AD[k][7]=Mean_Val[k];
      Slide_Sum[k]+=Slide_AD[k][7];
   }
   for(k=0;k<4;k++)
   {
      Filter_Value[k]=Slide_Sum[k]>>3;
   } 
     for(i=0;i<4;i++)
  {
    Normalize_Value[i]=(float)(Filter_Value[i]-ADC_Min[i])/(float)(ADC_Max[i]-ADC_Min[i]);
    if(Normalize_Value[i]<0)Normalize_Value[i]=0.001;
    if(Normalize_Value[i]>8)Normalize_Value[i]=8;
    Normalize_Value[i]*=1000;
  }
}
void AD_Deviation_Calculate()//AD偏差计算
{

  Collect_ADC();//ad采集
    
  Last_Error_S = Error_S;
  
  Error_S =( sqrt(Normalize_Value[0]+Normalize_Value[1]) - sqrt(Normalize_Value[2]+Normalize_Value[3])  ) 
	                                                      / 
	             (Normalize_Value[0]+Normalize_Value[1]+Normalize_Value[2]+Normalize_Value[3])*10000; 
  Error_S = Error_S>500 ? 500 : Error_S<-500 ? -500 : Error_S;   
  Deviation_rate = Last_Error_S-Error_S;
	//Deviation_rate = Deviation_rate>1 ? 1 : Deviation_rate<-1?-1:Deviation_rate;



////////////////////////////////////////////////////////////////////////////////	
	
	
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//				 圆环漂移稳定出				  三岔甩尾随便进
//
//					
//
//
////////////////////////////////////////////////////////////////////////////////	

if(ADraw[0]+ADraw[1]+ADraw[2]+ADraw[3]<200)     z=1;		//丢线	
	
///////////////////////////////////圆环/////////////////////////////////////////


if(ADraw[0]+ADraw[1]+ADraw[2]+ADraw[3]>9500&&yuan==0)
{	
		delay_ms(130);				
    pwm_duty(PWMB_CH1_P74, 1120);
    delay_ms(200);
	  huang=0;
    gpio_mode(P7_7,1);
    delay_ms(50);
    gpio_mode(P7_7,0);
    delay_ms(50);	
	  gpio_mode(P7_7,1);
    delay_ms(50);
    gpio_mode(P7_7,0);
	  yuan=1;
}

if(yuan==1)
{
	if(huang>30)
		{
		  if(ADraw[3]>1000)
			{
				pwm_duty(PWMB_CH1_P74, 1080);
        delay_ms(350);
				gpio_mode(P7_7,1);
        delay_ms(30);
        gpio_mode(P7_7,0);
        yuan=0;
				four=0;
			}
	  }
}

	

/////////////////////////////////三岔////////////////////////////////

if(ADraw[0]>1400&&ADraw[1]<1000&&ADraw[2]<1000&&ADraw[3]>1400&&ADraw[0]<3000&&ADraw[3]<3000) //
{
 if(four>200)
 {
  if(f==0||f==3)//
  {
	 if(f==0)
     {  						
		   pwm_duty(PWMB_CH1_P74,1290 );//左
       delay_ms(100);
       f=1;
     }
     else 
      {
			  pwm_duty(PWMB_CH1_P74,1070);//右
        delay_ms(180);					 
        f=2;
      }
			gpio_mode(P7_7,1);
      delay_ms(100);  
      gpio_mode(P7_7,0);
			lin=0;
			p=0.3;
      d=0.5;
  }	
 }
}


if(f==1||f==2)//出三岔 
{
 if(lin>10)    
  {
		if(ADraw[0]+ADraw[1]+ADraw[2]+ADraw[3]>3500)
		 {
		  if(f==1) 
       {
			   pwm_duty(PWMB_CH1_P74,1250);//右
         delay_ms(30);     			
		   }
		   if(f==2)   
        {
			    pwm_duty(PWMB_CH1_P74,1150);//左
          delay_ms(30);    			 
			  }	 
				gpio_mode(P7_7,1);
        delay_ms(50); 
        gpio_mode(P7_7,0);
			  delay_ms(50);
			  f=3;   				 
			  p=0.48;
        d=0.5;			 
		 }        
   }		
}



if(P36==0)//干簧管停车
	{
		if(ting==0)
		{
			{
			   pwm_duty(PWMA_CH1P_P60,0);          
	       pwm_duty(PWMA_CH2P_P62,2000);       
	       pwm_duty(PWMA_CH3P_P64,2000);           
	       pwm_duty(PWMA_CH4P_P66,0);
			}
			delay_ms(30);
			pwm_duty(PWMB_CH1_P74,1180);
   		delay_ms(200);
			gpio_mode(P7_7,1);
      delay_ms(50); 
      gpio_mode(P7_7,0);
			ting=1;
		}
		else if(ting==1)
		{
			pwm_duty(PWMB_CH1_P74,1070);
			delay_ms(350);
		  {
			  pwm_duty(PWMA_CH1P_P60,0);          
	      pwm_duty(PWMA_CH2P_P62,3000);       
	      pwm_duty(PWMA_CH3P_P64,3000);           
	      pwm_duty(PWMA_CH4P_P66,0);
		  }
			delay_ms(300);
			z=2;
		}
	}		
		
}


