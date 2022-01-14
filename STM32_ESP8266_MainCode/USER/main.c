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
//作者邮箱 sunjiyi666@foxmail.com 有任何问题可咨询
//本项目由网络开源资源经本人二次开发做成 转载请标明出处

int a=0;
int DOOR;   //门开关的标志位 1为开 0为关
int CARD=0,CARD1=1;   //卡片数量标志
int a11=0,JD=0;
extern int SB;
extern char card0_bit;
extern char card1_bit;
extern char card2_bit;
extern char card3_bit;
extern char card4_bit;
extern char card5_bit;
int main(void)
{
		
//	int *pointermima;
	int b=0,c=0,d=0,b1=1,b2=1,c1=1,d1=1;     //菜单判断标志位!
	int mima,newmima,t,t1=200,t2=200,t3=200,t4=200;
	int flashmima=1111;	
    delay_init();	    	 //延时函数初始化
		OLED_Init();        //初始化OLED	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	
    RC522_Init();       //初始化射频卡模块	
	
		KEY_Init();    			//单片机自带按键初	
		EXTIX_Init();				//按键使用定时器中断	
	
    LED_Init();     		 //用来驱动蜂鸣器 	
		KEY_BIGInit();     //矩阵键盘初始化

		TIM3_Int_Init(9,71);	 //1us周期 判断wifi	
	
		TIM2_Int_Init(1999,359);	 //10MS  判断WiFi
	
//		TIM4_Int_Init(9,71);	
		
    uart_init(115200);	 	//串口初始化为115200	
		
		LED0=0;	
		a=0;
while(1)
{
	
			if(SB==1)
			{
				DOOR_OPEN();
				SB=0;
			}	
	
	
	
		OLED_ShowString(10,10,"WELCOME 416",16); 
		OLED_ShowString(10,26,"WiFi/NFC ON",16); 
		OLED_ShowString(10,43,"PRESS 0",16); 
		OLED_Refresh();
//		WIFI_OPEN_DOOR();
		RC522_OPEN_DOOR();
if(a==1)
{
	OLED_Clear();
	a=0;	
	b=1;c=0;d=0; //进一级选择
	while(b)     //密码开门
	{
		OLED_ShowString(10,10,">SECRET CODE",16); 
		OLED_ShowString(10,26," NFC-RFID  1",16); 
		OLED_ShowString(10,43," ATTENDANT",16); 
		OLED_Refresh();
		if(a==1)
		{
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			b=0;c=1;d=0;
			break;
		}		
		
		if(a==2)     //进入密码开门程序
		{
			OLED_Clear();
			LED0=1;delay_ms(100);LED0=0;
			a=0;
			while(b)   //密码开门   支持四位数密码
			{
				OLED_ShowString(10,10,"ENTER...",16); 				
				OLED_Refresh();
				
				while(1)    //1
				{
					mima=0;
					t=key_can();
					if(t>=0&&t<=9)
					{
						t1=t;
						OLED_ShowNum(20,40,t1,1,16);
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
						OLED_ShowNum(30,40,t2,1,16);
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
						OLED_ShowNum(40,40,t3,1,16);
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
						OLED_ShowNum(50,40,t4,1,16);
						OLED_Refresh(); 
						DOOR=1;
					}
					if(t4!=200){break;}
				}		
				while(1)    				 //判断输入密码正确与否
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
//									while(DOOR)
//									{
										DOOR_OPEN();	
//									}
									OLED_Clear();
									OLED_ShowString(10,10,"SUCCESS!",16); 				
									OLED_Refresh();	
									delay_ms(3000);	
									OLED_Clear();
									b=0,c=0,d=0;
									t1=200,t2=200,t3=200,t4=200;			//清除			
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
									delay_ms(3000);  //延时3s展示error
									OLED_Clear();
									b=0;
									t1=200,t2=200,t3=200,t4=200;
									break;        //回到主菜单界面重新输入密码
					}
				 
				}
			}
		}
	}
	while(c)		//NFC开门	
	{
		OLED_ShowString(10,10," SECRET CODE",16); 
		OLED_ShowString(10,26,">NFC-RFID  1",16); 
		OLED_ShowString(10,43," ATTENDANT",16); 
		OLED_Refresh();			
		if(a==2)				//进入NFC模式开门
		{
			card0_bit==0;card1_bit==0;card2_bit==0;card3_bit==0;card4_bit==0;card5_bit==0;
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			while(c)    //NFC开门
			{
				RC522_OPEN_DOOR();			// NFC开门程序
				OLED_ShowString(10,26,"NFC IS OPEN",16); 
				OLED_Refresh();	
				if(a==2)
				{
					a=0;
					break;
				}
				if(card0_bit==1||card1_bit==1||card2_bit==1||card3_bit==1||card4_bit==1||card5_bit==1)
				{
					OLED_Clear();					
					OLED_ShowString(10,26,"SUCCESS!",16); 
					OLED_Refresh();
					DOOR_OPEN();					
					delay_ms(1000);
			card0_bit==0;card1_bit==0;card2_bit==0;card3_bit==0;card4_bit==0;card5_bit==0;					
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
	while(d)		//管理员模式
	{
		OLED_ShowString(10,10," SECRET CODE",16); 
		OLED_ShowString(10,26," NFC-RFID  1",16); 
		OLED_ShowString(10,43,">ATTENDANT",16); 
		OLED_Refresh();		
		if(a==1)
		{
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			b=1;c=0;d=0;	
//			break;
		}			
		if(a==2)				//进入管理员模式
		{
			b1=1;
			LED0=1;delay_ms(100);LED0=0;
			OLED_Clear();
			a=0;
			while(b1)    
			{
				OLED_ShowString(10,10,"Enter the",16);
				OLED_ShowString(10,26,"PassWord",16); 
				OLED_Refresh();			
				while(1)    //1
				{
					mima=0;
					t=key_can();
					if(t>=0&&t<=9)
					{
						t1=t;
						OLED_ShowNum(20,45,t1,1,16);
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
						OLED_ShowNum(30,45,t2,1,16);
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
						OLED_ShowNum(40,45,t3,1,16);
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
						OLED_ShowNum(50,45,t4,1,16);
						OLED_Refresh();    
					}
					d1=1;    //管理员菜单入口处
					b1=0;					//让管理员模式密码错误时直接回到主菜单
					b2=1;
					c1=1;
					CARD1=1;
					if(t4!=200){break;}
				}	
				
				while(1)     //验证管理密妈正确吗
				{
					mima = t1*1000+t2*100+t3*10+t4;
					if(mima==flashmima)   //密码正确  进入管理员菜单
					{				OLED_Clear();				
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
									b=1,c=0,d=0,a=0;

						while(b2) //管理员菜单总while
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
									OLED_ShowString(10,10,">RESET SECRET",16);   				//管理员11级页面 
									OLED_ShowString(10,26," ADD/MOVE NFC",16); 
									OLED_ShowString(10,43," QUIT    2",16); 				
									OLED_Refresh();	
								if(a==2)				//重置密码程序
								{
										OLED_Clear();
																																											
										t1=200,t2=200,t3=200,t4=200;		
										while(c1)   //输入新密码   支持四位数密码
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
													OLED_ShowNum(20,40,t1,1,16);
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
													OLED_ShowNum(30,40,t2,1,16);
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
													OLED_ShowNum(40,40,t3,1,16);
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
													OLED_ShowNum(50,40,t4,1,16);
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
									OLED_ShowString(10,10," RESET SECRET",16);   				//管理员12级页面 
									OLED_ShowString(10,26,">ADD/MOVE NFC",16); 
									OLED_ShowString(10,43," QUIT    2",16); 				
									OLED_Refresh();	
								if(a==2)
								{
									a=0;b=1,c=0,d1=1;
									LED0=1;delay_ms(100);LED0=0;
									OLED_Clear();
							while(d1)     //管理员NFC菜单总while
							{
									while(b)
									{
											CARD1=1;
											OLED_ShowString(10,10,">ADD",16);   				//NFC管理11级菜单
											OLED_ShowString(10,26," REMOVE",16); 
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
												RC522_READ_CARD();     //添加卡片程序
											}
												OLED_Clear();
												d1=0;
												a=0;									//读入卡片结束 跳出循环
												b=0;c=1,d=0;
										}
									}
									while(d)
									{
											OLED_ShowString(10,10," ADD",16);   				//NFC管理12级菜单
											OLED_ShowString(10,26,">REMOVE",16); 
											OLED_Refresh();		
										if(a==1)
										{
											a=0,b=1,c=0,d=0;
											OLED_Clear();
										}
										if(a==2)
										{
											a=0,d=0,d1=0,c=1;
											RC522_MOVE_CARD();											//删除卡片程序
											OLED_Clear();
										}										
									}
								}
							}								
																																				//添加/删除NFC程序
							
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
										OLED_ShowString(10,10," RESET SECRET",16);   				//管理员13级页面 
										OLED_ShowString(10,26," ADD/MOVE NFC",16); 
										OLED_ShowString(10,43,">QUIT    2",16); 				
										OLED_Refresh();	
									
									if(a==2)
									{
										LED0=1;delay_ms(100);LED0=0;												//退出到主菜单
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
					if(mima!=flashmima)   //密码错误!
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
									delay_ms(3000);  //延时3s展示error
									OLED_Clear();
									t1=200,t2=200,t3=200,t4=200;
									break;        //回到主菜单界面重新选择输入密码
					}
				 
				}
			}  //while（b1）  输入管理员立马...

		}  //if（a==2）	  while（d）的判断
	}   //一级 while（d）
}   //总while

}	

	
}   //int main
			
			
			
			
			

			
 

