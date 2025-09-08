#include "int.h"

//定义脉冲引脚
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04

void int_int()
{
    WTST = 0;               //设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快
    
	DisableGlobalIRQ();		//关闭总中断
	
    //sys_clk可选值:35000000，30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 35000000;     //设置系统频率为35MHz
    
	board_init();			//初始化寄存器
	//此处编写用户代码(例如：外设初始化代码等)
	
	pit_timer_ms(TIM_1, 20);     
	//NVIC_SetPriority(TIM_4, 0);		
	adc();                       //ADC初始化
	lcd_init();                  //液晶初始化
  lcd_clear(YELLOW);
  delay_init(); 	
	motor_init();	
  pwm_init(PWMB_CH1_P74, 50, 740);
	ctimer_count_init(SPEEDL_PLUSE);	//编码器左初始化定时器0作为外部计数
	ctimer_count_init(SPEEDR_PLUSE);	//编码器右初始化定时器3作为外部计数
	wireless_uart_init();
	//总中断最后开启
	EnableGlobalIRQ();		//开启总中断
}	