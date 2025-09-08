#ifndef _bihuan_h
#define _bihuan_h

#include "headfile.h"

//定义脉冲引脚
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04
//定义方向引脚
#define SPEEDL_DIR     P35
#define SPEEDR_DIR     P53





typedef struct 
{
	int16 target_val;   //目标值
	int16 err;          //偏差值
	int16 err_last;     //上一个偏差值
	float p,i,d;     //pid
	int16 integral;     //积分值
	int16 output_val;   //输出值
}PID;

extern 		PID pidl;
extern 		PID pidr;


extern		int16 templ_pluse ;
extern		int16 tempr_pluse ;

extern		uint8 fazhi;
extern		uint16 djduty;

extern int32 pwml;
extern int32 pwmr;

void bmq();
void pidlz();
void pingmu();
void anniu();
void shibie();

#endif