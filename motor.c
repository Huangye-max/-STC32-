#include "headfile.h"
int v=6500;
int glkl=3.17;
int bdcl=6.63;
int v_v;
int v_l;
int v_r;

 
void motor_init()//包涵电机驱动初始化和速度检测初始化
{
    pwm_init(PWMA_CH1P_P60, 17000, 0); //初始化定时器1  使用A18引脚  初始化频率为17Khz
    pwm_init(PWMA_CH2P_P62, 17000, 0); //初始化定时器1  使用A20引脚  初始化频率为17Khz
	  pwm_init(PWMA_CH3P_P64, 17000, 0);
	  pwm_init(PWMA_CH4P_P66, 17000, 0);
}

void sanchabiansu()
{
	if(f==1||f==2)		v=6500;
	else    v=4000;
}

void time_to_go()
{
	sanchabiansu();
	if(Error_S>20)		v_v=v-Error_S*bdcl;		//弯道减速
  else if(Error_S<(-20)) v_v=v+Error_S*bdcl;
	else  v_v=v;
	
	if(Error_S>20)		v_r=v_v+Error_S*glkl;		//后轮差速
  else if(Error_S<(-20)) v_l=v_v-Error_S*glkl;
	else 
		{
			v_r=v_v;
			v_l=v_v;
    }
}

void motor_out()
{
	time_to_go();
	pwm_duty(PWMA_CH1P_P60,v_l);           
	pwm_duty(PWMA_CH2P_P62,0);       
	pwm_duty(PWMA_CH3P_P64,0);           
	pwm_duty(PWMA_CH4P_P66,v_r);       
}



/*uint16  dat;
uint16  dat2;
int     speed_you=1000;      //目标速度
int     speed_zuo=1000;
float   k=0.55;                 //3.43		
float   I=0.5;								 //0.05
int     speed_I_you=0;       //I的累加存储
int     speed_I_zuo=0;
int     limit_you_I=3000;    //I的限幅
int     limit_zuo_I=3000;
int     speed_pc_you=0;      
int     speed_pc_zuo=0;     //两轮的偏差
int     out_you;             
int     out_zuo;            //用于输出速度的变量

	
	
void motor_init()//包涵电机驱动初始化和速度检测初始化
{
    pwm_init(PWMA_CH1P_P60, 17000, 0); //初始化定时器1  使用A18引脚  初始化频率为17Khz
    pwm_init(PWMA_CH2P_P62, 17000, 0); //初始化定时器1  使用A20引脚  初始化频率为17Khz	
	  pwm_init(PWMA_CH3P_P64, 17000, 0); //初始化定时器1  使用A18引脚  初始化频率为17Khz
    pwm_init(PWMA_CH4P_P66, 17000, 0); //初始化定时器1  使用A20引脚  初始化频率为17Khz
	  
}
 
	void motor_out()
 {    
    dat  = ctimer_count_read(CTIM0_P34);//编码器采集    
	  ctimer_count_clean(CTIM0_P34);//清空内存   
	 
	  dat2 = ctimer_count_read(CTIM3_P04);	  
	  ctimer_count_clean(CTIM3_P04);
	 
	  dat=dat*4;
	  dat2=dat2*4;
	 
	 
	  speed_pc_you=speed_you-dat;//进行偏差计算   
	  speed_pc_zuo=speed_zuo-dat2;
	 
	  speed_I_you+=speed_pc_you;//偏差进行累加       
	 	speed_I_zuo+=speed_pc_zuo;
	 
	 
	 
	  if(speed_I_you>limit_you_I) 
				speed_I_you=limit_you_I;  		//Xian Fu
	  if(speed_I_zuo>limit_zuo_I) 
				speed_I_zuo=limit_zuo_I;
	 
	  out_you = speed_you+speed_pc_you*k+speed_I_you*I;	    	 
	  out_zuo = speed_zuo+speed_pc_zuo*k+speed_I_zuo*I;
	  R_motor_out(out_you);
	  L_motor_out(out_zuo);
 }
 
 void L_motor_out(int a)
 {  
   pwm_duty(PWMA_CH1P_P60,0);           
	 pwm_duty(PWMA_CH2P_P62,a);    
 }

 void R_motor_out(int b)
 {  
    pwm_duty(PWMA_CH3P_P64,0);           
	  pwm_duty(PWMA_CH4P_P66,b);       
 }*/
 

 