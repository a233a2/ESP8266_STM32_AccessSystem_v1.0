#ifndef __LED_H
#define __LED_H	 
#include "sys.h"



#define PWM0 PBout(11)// PB11

#define LED0 PBout(5)// PB5

#define WIFI1  	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//∂¡»°

void LED_Init(void);//≥ı ºªØ

		 				    
#endif
