#ifndef __KEY_SCAN
#define __KEY_SCAN
#include "sys.h"

//extern u8 key_can(void);//��ʼ��

extern u8 KEY_can(u8 mode);  	//����ɨ�躯��		

void KEY_BIGInit(void);//IO��ʼ��


#define L1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)//��ȡ����
#define L2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//
#define L3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//
#define L4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)// 
 
#define H1 PCout(10)
#define H2 PCout(11)
#define H3 PCout(12)
#define H4 PCout(1)
//#define S1 	'1'	
//#define S2	'2'	
//#define S3  '3'
//#define S4 	'11'	
//#define S5	'4'	
//#define S6  '5'	
//#define S7 	'6'
//#define S8	'12'	
//#define S9 	'7'
//#define S10	'8'	
//#define S11 '9'
//#define S12	'13'	
//#define S13 'C'	
//#define S14 'D'	
//#define S15	'0'	
//#define S16 '0'

//#define S1 	'1'	
//#define S2	'2'	
//#define S3  '3'
//#define S4 	'A'	
//#define S5	'4'	
//#define S6  '5'	
//#define S7 	'6'
//#define S8	'B'	
//#define S9 	'7'
//#define S10	'8'	
//#define S11 '9'
//#define S12	'C'	
//#define S13 '*'	
//#define S14 '0'	
//#define S15	'#'	
//#define S16 'D'
//void KEY_BIGInit(void);//IO��ʼ��
//void key_can(u8 mode);  	//����ɨ�躯��				
//	
#endif
