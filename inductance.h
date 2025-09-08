#ifndef __inductance_H_
#define __inductance_H_
#include "headfile.h"
extern float Error_S;
extern float Deviation_rate;//Æ«²î±ä»¯ÂÊ
extern float Normalize_Value[4];
extern float Filter_Value[4];
extern uint16 ADC_Max[];
extern uint16 ADC_Min[];
extern void adc();
extern void Collect_ADC(); 
extern void AD_Deviation_Calculate();
extern void AD_xianshi();
extern void SEngine_out();
extern void Normalize_Valu();
extern uint16 Mean_Val[4];
extern int dat;
extern uint16 ADraw[4];
extern int z;
extern int huan;
extern int f;


#endif