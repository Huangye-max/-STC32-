#ifndef _bihuan_h
#define _bihuan_h

#include "headfile.h"

//������������
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04
//���巽������
#define SPEEDL_DIR     P35
#define SPEEDR_DIR     P53





typedef struct 
{
	int16 target_val;   //Ŀ��ֵ
	int16 err;          //ƫ��ֵ
	int16 err_last;     //��һ��ƫ��ֵ
	float p,i,d;     //pid
	int16 integral;     //����ֵ
	int16 output_val;   //���ֵ
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