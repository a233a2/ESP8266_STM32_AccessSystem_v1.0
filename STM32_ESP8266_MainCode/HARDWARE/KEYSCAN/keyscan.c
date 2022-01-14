#include "keyscan.h"
#include "sys.h"
#include "delay.h"

void KEY_BIGInit(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7;//  ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOE3,4,5,6

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_1|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOB7,8,9,12.
	GPIO_SetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_1|GPIO_Pin_3);

}
int cheak;

u8 key_can(u8 mode)          
{  

//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������	
	H1=0;H2=0;H3=0;H4=0;	
	if(L1==1 && L2==1 && L3==1 && L3==1&& L4==1){return 200;}// �ް�������
	if((L1==0||L2==0||L3==0||L4==0))  //	if(key_up&&(L1==0||L2==0||L3==0||L4==0))
	{
		delay_ms(22);//ȥ���� 
//		key_up=0;
	  delay_ms(1);
		//��1��
		H1=0;H2=1;H3=1;H4=1;
		if(L1==0)return 13;
		if(L2==0)return 12;
		if(L3==0)return 11;
		if(L4==0)return 10;
	  //��2
		delay_ms(1);
		H1=1;H2=0;H3=1;H4=1;
		if(L1==0)return 15;
		if(L2==0)return 9;
		if(L3==0)return 6;
		if(L4==0)return 3;
		//��3
		delay_ms(1);
		H1=1;H2=1;H3=0;H4=1;
		if(L1==0)return 0;
		if(L2==0)return 8;
		if(L3==0)return 5;
		if(L4==0)return 2;
		//��4
		delay_ms(1);
		H1=1;H2=1;H3=1;H4=0;
		if(L1==0)return 14;
		if(L2==0)return 7;
		if(L3==0)return 4;
		if(L4==0)return 1;
	}
	else if(L1==1 && L2==1 && L3==1 && L3==1&& L4==1){return 200;}// �ް�������
	return 200;  																									//������� ����ܼ�����������1��2  ��keycan�����й� ���о�
}
