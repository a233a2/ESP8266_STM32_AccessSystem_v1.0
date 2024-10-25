#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "rc522.h"
#include "led.h"
#include "oled.h"
#include "keyscan.h"
#include "key.h"
#include "exti.h"
#include "stm32f10x_flash.h"
#include "flash.h"
#include "stdio.h"
#include "pwm.h"

/*
Ӳ����������˵����
    ѡ��ť��PC5
    ȷ����ť��PA15
    ��������  PB5
	�����    PA1
    OLED��ʾ���� SCL��PC8     SDA��PC9
	RC522��������MISO: PA6    MOSI:PA0       SCK:PA2       SDA:PA4
	4*4���󰴼�����1����8����Ϊ��PA13,3,5,7  PC10,11,12,1  
*/

int a=0;
int DOOR;             //�ſ��صı�־λ 1Ϊ�� 0Ϊ��
int CARD=0,CARD1=1;   //��Ƭ������־
int a11=0,JD=0;
int b=0,c=0,d=0,b1=1,b2=1,c1=1,d1=1;     //�˵��жϱ�־λ!
int mima,newmima,t,t1=200,t2=200,t3=200,t4=200;
int flashmima=2222;	
extern int SB;
extern char card0_bit;
extern char card1_bit;
extern char card2_bit;
extern char card3_bit;
extern char card4_bit;
extern char card5_bit;


int main(void)
{
	LED0=0;	
    delay_init();	    	//��ʱ������ʼ��
	OLED_Init();            //��ʼ��OLED	
	KEY_Init();    			//��Ƭ���Դ�������	
	EXTIX_Init();		    //����ʹ�ö�ʱ���ж�	
    LED_Init();     		//�������������� 	
	KEY_BIGInit();          //������̳�ʼ��
    //uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200	
    RC522_Init();           //��ʼ����Ƶ��ģ��	
	PWM_Init();
		
while(1)
{
		Servo_SetAngle(180);		//�رն��
		if(SB==1){DOOR_OPEN();}	//��չ�Ŀ���ֵ
		SB=0;	
		OLED_ShowString(10,10,"   WELCOME",16); 
		OLED_ShowString(10,26,"   NFC ON",16); 
		OLED_ShowString(10,43," Press button",16); 
		OLED_Refresh();
		RC522_OPEN_DOOR();
		
if(a==1)
{
	OLED_Clear();
	a=0;	
	b=1;c=0;d=0;         //��һ��ѡ��
	while(b)             //���뿪��
	{
		OLED_ShowString(10,10,"Use >CODE",16); 
		OLED_ShowString(10,26,"     NFC",16); 
		OLED_ShowString(10,43,"     Admin",16); 
		OLED_Refresh();
		if(a==1)
		{
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			b=0;c=1;d=0;
			break;
		}		
		
		if(a==2)         //�������뿪�ų���
		{
			OLED_Clear();
			LED0=1;delay_ms(100);LED0=0;
			a=0;
			while(b)     //���뿪��   ֧����λ������
			{
				OLED_ShowString(10,10,"  Enter  the",16);
				OLED_ShowString(10,26,"   PassWord",16); 				
				OLED_Refresh();
				
				while(1)    //1
				{
					mima=0;
					t=key_can();
					if(t>=0&&t<=9)
					{
						t1=t;
						OLED_ShowNum(40,40,t1,1,16);
						OLED_Refresh(); 
					}
					if(t1!=200){break;}
				}
				
				while(1)  //2
				{
					delay_ms(100);
					t=key_can();
					if(t>=0&&t<=9)
					{
						t2=t;
						OLED_ShowNum(50,40,t2,1,16);
						OLED_Refresh(); 
					}
					if(t2!=200){break;}
				}	
				
				while(1)  //3
				{
					delay_ms(100);
					t=key_can();
					if(t>=0&&t<=9)
					{
						t3=t;
						OLED_ShowNum(60,40,t3,1,16);
						OLED_Refresh(); 
					}
					if(t3!=200){break;}
				}	
				
				while(1)  //4
				{
					delay_ms(100);
					t=key_can();
					if(t>=0&&t<=9)
					{
						t4=t;
						OLED_ShowNum(70,40,t4,1,16);
						OLED_Refresh(); 
						DOOR=1;
					}
					if(t4!=200){break;}
				}		
				while(1)    				 //�ж�����������ȷ���
				{
					mima = t1*1000+t2*100+t3*10+t4;
					if(mima==flashmima)
					{								
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;

										Servo_SetAngle(90);	//������ȷ���򿪶��
						
									OLED_Clear();
									OLED_ShowString(10,10,"  SUCCESS!",16);
                                    OLED_ShowString(10,26,"opened door",16); 						
									OLED_Refresh();	
									delay_ms(3000);	
									OLED_Clear();
									b=0,c=0,d=0;
									t1=200,t2=200,t3=200,t4=200;			//���			
									break;
					}
					if(mima!=flashmima)
					{
									LED0=1;           //4 ding! is ok
									delay_ms(500);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(500);			
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(500);
									LED0=0;						
									OLED_Clear();
									OLED_ShowString(10,10,"ERROR!",16); 				
									OLED_Refresh();
									delay_ms(3000);  //��ʱ3sչʾerror
									OLED_Clear();
									b=0;
									t1=200,t2=200,t3=200,t4=200;
									break;        //�ص����˵�����������������
					}
				 
				}
			}
		}
	}
	while(c)		//NFC����	
	{
		OLED_ShowString(10,10,"Use  CODE",16); 
		OLED_ShowString(10,26,"    >NFC",16); 
		OLED_ShowString(10,43,"     Admin",16);
		OLED_Refresh();			
		if(a==2)				//����NFCģʽ����
		{
			card0_bit==0;card1_bit==0;card2_bit==0;card3_bit==0;card4_bit==0;card5_bit==0;
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			while(c)    //NFC����
			{
				RC522_OPEN_DOOR();			// NFC���ų���
				OLED_ShowString(10,26,"     NFC  ",16); 
				OLED_Refresh();	
				if(a==2)
				{
					a=0;
					break;
				}
				if(card0_bit==1||card1_bit==1||card2_bit==1||card3_bit==1||card4_bit==1||card5_bit==1)
				{
					OLED_Clear();					
					OLED_ShowString(10,10,"  SUCCESS!",16);
                    OLED_ShowString(10,26," opende door",16); 
					OLED_Refresh();
					Servo_SetAngle(90);		//������ȷ���򿪶��			
					delay_ms(1000);
			        card0_bit=0;card1_bit=0;card2_bit=0;card3_bit=0;card4_bit=0;card5_bit=0;					
					break;
				}
				
			}				
		}
		if(a==1)
		{
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();			
			a=0;
			b=0;c=0;d=1;	
			break;
		}
	}
	while(d)		//����Աģʽ
	{
		OLED_ShowString(10,10,"Use  CODE",16); 
		OLED_ShowString(10,26,"     NFC",16); 
		OLED_ShowString(10,43,"    >Admin",16);
		OLED_Refresh();		
		if(a==1)
		{
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			b=1;c=0;d=0;	
//			break;
		}			
		if(a==2)				//�������Աģʽ
		{
			b1=1;
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			while(b1)    
			{
				OLED_ShowString(10,10,"  Enter  the",16);
				OLED_ShowString(10,26,"   PassWord",16); 
				OLED_Refresh();			
				while(1)    //1
				{
					mima=0;
					t=key_can();
					if(t>=0&&t<=9)
					{
						t1=t;
						OLED_ShowNum(40,45,t1,1,16);
						OLED_Refresh(); 
					}
					if(t1!=200){break;}
				}
				
				while(1)  //2
				{
					delay_ms(100);
					t=key_can();
					if(t>=0&&t<=9)
					{
						t2=t;
						OLED_ShowNum(50,45,t2,1,16);
						OLED_Refresh(); 
					}
					if(t2!=200){break;}
				}	
				
				while(1)  //3
				{
					delay_ms(100);
					t=key_can();
					if(t>=0&&t<=9)
					{
						t3=t;
						OLED_ShowNum(60,45,t3,1,16);
						OLED_Refresh(); 
					}
					if(t3!=200){break;}
				}	
				
				while(1)  //4
				{
					delay_ms(100);
					t=key_can();
					if(t>=0&&t<=9)
					{
						t4=t;
						OLED_ShowNum(70,45,t4,1,16);
						OLED_Refresh();    
					}
					d1=1;    //����Ա�˵���ڴ�
					b1=0;					//�ù���Աģʽ�������ʱֱ�ӻص����˵�
					b2=1;
					c1=1;
					CARD1=1;
					if(t4!=200){break;}
				}	
				
				while(1)     //��֤���������Ƿ���ȷ
				{
					mima = t1*1000+t2*100+t3*10+t4;
					if(mima==flashmima)   //������ȷ  �������Ա�˵�
					{				OLED_Clear();				
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
									b=1,c=0,d=0,a=0;

						while(b2) //����Ա�˵���while
						{
							while(b)
							{
								if(a==1)
								{
									LED0=1;delay_ms(100);LED0=0;
									b=0,c=1,d=0,a=0;
									OLED_Clear();
									break;
								}
									OLED_ShowString(10,10,">Reset Code",16);   				//����Ա11��ҳ�� 
									OLED_ShowString(10,26," Add/Move NFC",16); 
									OLED_ShowString(10,43,"    QUIT ",16); 				
									OLED_Refresh();	
								if(a==2)				//�����������
								{
										OLED_Clear();
																																											
										t1=200,t2=200,t3=200,t4=200;		
										while(c1)   //����������   ֧����λ������
										{
											OLED_ShowString(10,10,"NEW CODE",16);   								
											OLED_Refresh();
											
											while(1)    //1
											{
												mima=0;
												t=key_can();
												if(t>=0&&t<=9)
												{
													t1=t;
													OLED_ShowNum(40,40,t1,1,16);
													OLED_Refresh(); 
												}
												if(t1!=200){break;}
											}
											
											while(1)  //2
											{
												delay_ms(100);
												t=key_can();
												if(t>=0&&t<=9)
												{
													t2=t;
													OLED_ShowNum(50,40,t2,1,16);
													OLED_Refresh(); 
												}
												if(t2!=200){break;}
											}	
											
											while(1)  //3
											{
												delay_ms(100);
												t=key_can();
												if(t>=0&&t<=9)
												{
													t3=t;
													OLED_ShowNum(60,40,t3,1,16);
													OLED_Refresh(); 
												}
												if(t3!=200){break;}
											}	
											
											while(1)  //4
											{
												delay_ms(100);
												t=key_can();
												if(t>=0&&t<=9)
												{
													t4=t;
													OLED_ShowNum(70,40,t4,1,16);
													OLED_Refresh(); 
												}
												if(t4!=200){break;}
											}	
												while(1)
												{
													flashmima = t1*1000+t2*100+t3*10+t4;
													OLED_Clear();
													OLED_ShowString(10,10,"CODE UPDATA",16);   			
													OLED_Refresh();
													delay_ms(3000);
													OLED_Clear();
													b=0,c=0,d=0,a=0,b1=0,b2=0,c1=0;
													break;
												}				
									     }		
							       }		
							}
							while(c)
							{
								if(a==1)
								{
									LED0=1;delay_ms(100);LED0=0;
									b=0,c=0,d=1,a=0;
									OLED_Clear();
									break;
								}
									OLED_ShowString(10,10," Reset code",16);   				//����Ա12��ҳ�� 
									OLED_ShowString(10,26,">Add/Move NFC",16); 
									OLED_ShowString(10,43,"     QUIT  ",16); 				
									OLED_Refresh();	
								if(a==2)
								{
									a=0;b=1,c=0,d1=1;
									LED0=1;delay_ms(100);LED0=0;
									OLED_Clear();
							while(d1)     //����ԱNFC�˵���while
							{
									while(b)
									{
											CARD1=1;
											OLED_ShowString(10,10,">Add",16);   				//NFC����11���˵�
											OLED_ShowString(10,26," Remove",16); 
											OLED_Refresh();
										if(a==1)
										{
											a=0,b=0,c=0,d=1;
											OLED_Clear();
										}
										if(a==2)
										{

											OLED_Clear();
											while(CARD1)
											{
												RC522_READ_CARD();     //��ӿ�Ƭ����
											}
												OLED_Clear();
												d1=0;
												a=0;									//���뿨Ƭ���� ����ѭ��
												b=0;c=1,d=0;
										}
									}
									while(d)
									{
											OLED_ShowString(10,10," Add",16);   				//NFC����12���˵�
											OLED_ShowString(10,26,">Remove",16); 
											OLED_Refresh();		
										if(a==1)
										{
											a=0,b=1,c=0,d=0;
											OLED_Clear();
										}
										if(a==2)
										{
											a=0,d=0,d1=0,c=1;
											RC522_MOVE_CARD();											//ɾ����Ƭ����
											OLED_Clear();
										}										
									}
								}
							}								
																																				//���/ɾ��NFC����
							
							}							
							while(d)
							{
									if(a==1)
									{
										LED0=1;delay_ms(100);LED0=0;
										b=1,c=0,d=0,a=0;
										OLED_Clear();
										break;
									}							
										OLED_ShowString(10,10," Reset code",16);   				//����Ա13��ҳ�� 
										OLED_ShowString(10,26," Add/Move NFC",16); 
										OLED_ShowString(10,43,">    QUIT ",16); 				
										OLED_Refresh();	
									
									if(a==2)
									{
										LED0=1;delay_ms(100);LED0=0;												//�˳������˵�
										a=0;
										OLED_Clear();
										b=0,c=0,d=0,a=0,b1=0,b2=0;
									}
								
								}							
						}

							if(b==0&&c==0&&d==0)
							{
									OLED_Clear();
									t1=200,t2=200,t3=200,t4=200;						
									break;
							}
				}
					if(mima!=flashmima)   //�������!
					{
									LED0=1;           //4 ding! is ok
									delay_ms(500);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(500);			
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(500);
									LED0=0;						
									OLED_Clear();
									OLED_ShowString(10,10,"ERROR!",16); 				
									OLED_Refresh();
									delay_ms(3000);  //��ʱ3sչʾerror
									OLED_Clear();
									t1=200,t2=200,t3=200,t4=200;
									break;        //�ص����˵���������ѡ����������
					}
				 }
			  }  //while��b1��  �������Ա����...
		   }  //if��a==2��	  while��d�����ж�
	    }   //һ�� while��d��
     }   //��while
  }		
}   //int main
			
			
			
			
			

			
 

