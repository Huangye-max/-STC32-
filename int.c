#include "int.h"

//������������
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04

void int_int()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();			//��ʼ���Ĵ���
	//�˴���д�û�����(���磺�����ʼ�������)
	
	pit_timer_ms(TIM_1, 20);     
	//NVIC_SetPriority(TIM_4, 0);		
	adc();                       //ADC��ʼ��
	lcd_init();                  //Һ����ʼ��
  lcd_clear(YELLOW);
  delay_init(); 	
	motor_init();	
  pwm_init(PWMB_CH1_P74, 50, 740);
	ctimer_count_init(SPEEDL_PLUSE);	//���������ʼ����ʱ��0��Ϊ�ⲿ����
	ctimer_count_init(SPEEDR_PLUSE);	//�������ҳ�ʼ����ʱ��3��Ϊ�ⲿ����
	wireless_uart_init();
	//���ж������
	EnableGlobalIRQ();		//�������ж�
}	