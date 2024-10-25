#include "sys.h"
#include "rc522.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
#include "led.h"
#include "oled.h"
#include "pwm.h"
#include "stm32f10x_flash.h"


unsigned char CT[2];
unsigned char SN[4]; 

unsigned char DATA[16];			//�������
unsigned char RFID[16];			
unsigned char card0_bit=0;
unsigned char card1_bit=0;
unsigned char card2_bit=0;
unsigned char card3_bit=0;
unsigned char card4_bit=0;
unsigned char card5_bit=0;
unsigned char total=0;
unsigned char card_0[4];
unsigned char card_1[4];
unsigned char card_2[4];
unsigned char card_3[4];
unsigned char card_4[4];
unsigned char card_5[4];
u8 KEY_A[6]= {0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY_B[6]= {0xff,0xff,0xff,0xff,0xff,0xff};
u8 AUDIO_OPEN[6] = {0xAA, 0x07, 0x02, 0x00, 0x09, 0xBC};

unsigned char RFID1[16]= {0x10,0x20,0x30,0x40,0x50,0x60,0xff,0x07,0x80,0x29,0x01,0x02,0x03,0x04,0x05,0x06};
unsigned char RFID2[16]= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};

u8 KEY_A1[6]= {0x10,0x20,0x30,0x40,0x50,0x60};
u8 KEY_A2[6]= {0x00,0x00,0x00,0x00,0x00,0x00};
u8 KEY_B1[6]= {0x01,0x02,0x03,0x04,0x05,0x06};
u8 KEY_B2[6]= {0x10,0x20,0x30,0x00,0x00,0x00};
u8 KEY_B3[6]= {0x01,0x02,0x03,0x00,0x00,0x00};

unsigned char DATA0[16]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char DATA1[16]= {0x12,0x34,0x56,0x78,0x9A,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char status;

unsigned char addr=0x08;



extern int DOOR;							
extern int CARD;						 
extern int CARD1;		
#define   RC522_DELAY()  delay_us( 20 )

extern int JD;
void DOOR_OPEN(void) 
{
			int i;
			for(i=0;i<100;i++)
			{
				JD++;
				delay_ms(10);		
			}
			for(i=100;i>0;i--)
			{
				JD--;
				delay_ms(10);		
			}	
			JD=0;
			DOOR=0;
}


void RC522_MOVE_CARD(void)
{
	int i;
		OLED_Init();
	for(i=0;i<4;i++)
	{
			card_0[i]=0;
			card_1[i]=0;
			card_2[i]=0;
			card_3[i]=0;
			card_4[i]=0;
			card_5[i]=0;
	}
				LED0=1;           //2 ding! is ok
				delay_ms(100);
				LED0=0;
				delay_ms(100);			
				LED0=1;
				delay_ms(100);			
				LED0=0;
				LED0=1;           //2 ding! is ok
				delay_ms(100);
				LED0=0;
				delay_ms(100);			
				LED0=1;
				delay_ms(100);			
				LED0=0;
		OLED_Clear();	
		OLED_ShowString(7,28," All Remove",16);	
		OLED_Refresh();
		delay_ms(1000);		
		OLED_Clear();	
		OLED_ShowString(7,28," All Remove",16);	
		OLED_Refresh();
		delay_ms(1000);	
		OLED_Clear();	
		OLED_ShowString(7,28," All Remove",16);	
		OLED_Refresh();
		delay_ms(1000);			
}

void RC522_READ_CARD(void)
{
		int i;
		OLED_Init();
		OLED_ShowString(7,28,"PUT CARD ON..",16);	
		OLED_Refresh();	
	  status = PcdRequest(PICC_REQALL,CT);	
		if(status==MI_OK)
    {
	    status=MI_ERR;
			status = PcdAnticoll(SN);
			ShowID(SN);
			if(CARD==6)
			{
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD FULL!",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;	
			}			
			if(CARD==5)
			{
				for(i=0;i<4;i++)
				{
						card_5[i]=SN[i];
						CARD=6;
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD 6 IS ON",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;
				}			
			}
			if(CARD==4)
			{
				for(i=0;i<4;i++)
				{
						card_4[i]=SN[i];
						CARD=5;
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD 5 IS ON",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;
				}			
			}
			if(CARD==3)
			{
				for(i=0;i<4;i++)
				{
						card_3[i]=SN[i];
						CARD=4;
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD 4 IS ON",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;
				}			
			}
			if(CARD==2)
			{
				for(i=0;i<4;i++)
				{
						card_2[i]=SN[i];
						CARD=3;
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD 3 IS ON",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;
				}				
			}
			if(CARD==1)
			{
				for(i=0;i<4;i++)
				{
						card_1[i]=SN[i];
						CARD=2;
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD 2 IS ON",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;
				}				
			}
			if(CARD==0)
			{
				for(i=0;i<4;i++)
				{
						card_0[i]=SN[i];
						CARD=1;
						OLED_Clear();	
						OLED_ShowString(7,28,"CARD 1 IS ON",16);	
						OLED_Refresh();		
						delay_ms(1000);
						CARD1=0;
				}
			}	
		}
}


void RC522_OPEN_DOOR(void)
{

	  status = PcdRequest(PICC_REQALL,CT);
	  if(status==MI_OK)
    {
        status=MI_ERR;
				status = PcdAnticoll(SN);
				ShowID(SN);
				 if((SN[0]==card_0[0])&&(SN[1]==card_0[1])&&(SN[2]==card_0[2])&&(SN[3]==card_0[3]))
				 {
						 card0_bit=1;
						 printf("\r\nThe User is:card_0\r\n");
						 DOOR_OPEN();
					 				LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
				 }				
        if((SN[0]==card_1[0])&&(SN[1]==card_1[1])&&(SN[2]==card_1[2])&&(SN[3]==card_1[3]))
        {
            card1_bit=1;
            printf("\r\nThe User is:card_1\r\n");
						 DOOR_OPEN();
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
        }
        if((SN[0]==card_2[0])&&(SN[1]==card_2[1])&&(SN[2]==card_2[2])&&(SN[3]==card_2[3]))
        {
            card2_bit=1;
            printf("\r\nThe User is:card_2\r\n");
						DOOR_OPEN();
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
        }

        if((SN[0]==card_3[0])&&(SN[1]==card_3[1])&&(SN[2]==card_3[2])&&(SN[3]==card_3[3]))
        {
            card3_bit=1;
            printf("\r\nThe User is:card_3\r\n");
					  DOOR_OPEN();
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
        }
        if((SN[0]==card_4[0])&&(SN[1]==card_4[1])&&(SN[2]==card_4[2])&&(SN[3]==card_4[3]))
        {
            card4_bit=1;
            printf("\r\nThe User is:card_4\r\n");
						DOOR_OPEN();
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
        }			
        if((SN[0]==card_5[0])&&(SN[1]==card_5[1])&&(SN[2]==card_5[2])&&(SN[3]==card_5[3]))
        {
            card5_bit=1;
            printf("\r\nThe User is:card_5\r\n");
						DOOR_OPEN();
									LED0=1;           //2 ding! is ok
									delay_ms(100);
									LED0=0;
									delay_ms(100);			
									LED0=1;
									delay_ms(100);			
									LED0=0;
        }
    }
}


void RC522_Handle(void)
{
    u8 i = 0;
    status = PcdRequest(PICC_REQALL,CT);

   

    if(status==MI_OK)
    {
        status=MI_ERR;
        status = PcdAnticoll(SN);
    }

    if (status==MI_OK)
    {
        status = MI_ERR;
        ShowID(SN); 

        if((SN[0]==card_0[0])&&(SN[1]==card_0[1])&&(SN[2]==card_0[2])&&(SN[3]==card_0[3]))
        {
            card0_bit=1;
            printf("\r\nThe User is:card_0\r\n");
        }
        if((SN[0]==card_1[0])&&(SN[1]==card_1[1])&&(SN[2]==card_1[2])&&(SN[3]==card_1[3]))
        {
            card1_bit=1;
            printf("\r\nThe User is:card_1\r\n");
        }
        if((SN[0]==card_2[0])&&(SN[1]==card_2[1])&&(SN[2]==card_2[2])&&(SN[3]==card_2[3]))
        {
            card2_bit=1;
            printf("\r\nThe User is:card_2\r\n");
        }

        if((SN[0]==card_3[0])&&(SN[1]==card_3[1])&&(SN[2]==card_3[2])&&(SN[3]==card_3[3]))
        {
            card3_bit=1;
            printf("\r\nThe User is:card_3\r\n");
        }
        if((SN[0]==card_4[0])&&(SN[1]==card_4[1])&&(SN[2]==card_4[2])&&(SN[3]==card_4[3]))
        {
            card4_bit=1;
            printf("\r\nThe User is:card_4\r\n");
        }
        //total = card1_bit+card2_bit+card3_bit+card4_bit+card0_bit;
        status = PcdSelect(SN);
    }
    else
    {
    }

    if(status == MI_OK)
    {
        status = MI_ERR;
        // ��֤A��Կ ���ַ ���� SN
        // ע�⣺�˴��Ŀ��ַ0x0B��2����3���飬�˿��ַֻ��Ҫָ��ĳһ�����Ϳ����ˣ���2����Ϊ0x08-0x0B�����Χ����Ч����ֻ�ܶ���֤�����������ж�д����
        status = PcdAuthState(KEYA, 0x0B, KEY_A, SN);
        if(status == MI_OK)//��֤�ɹ�
        {
            printf("PcdAuthState(A) success\r\n");
        }
        else
        {
            printf("PcdAuthState(A) failed\r\n");
        }
        // ��֤B��Կ ���ַ ���� SN
        status = PcdAuthState(KEYB, 0x0B, KEY_B, SN);
        if(status == MI_OK)//��֤�ɹ�
        {
            printf("PcdAuthState(B) success\r\n");
        }
        else
        {
            printf("PcdAuthState(B) failed\r\n");
        }
    }

    if(status == MI_OK)//��֤�ɹ�
    {
        status = MI_ERR;
        // ��ȡM1��һ������ ���ַ ��ȡ������ ע�⣺��Ϊ������֤��������2����������ֻ�ܶ�2���������ݽ��ж�д����0x08-0x0B�����Χ��������Χ��ȡʧ�ܡ�
        status = PcdRead(addr, DATA);
        if(status == MI_OK)//�����ɹ�
        {
            // printf("RFID:%s\r\n", RFID);
            printf("DATA:");
            for(i = 0; i < 16; i++)
            {
                printf("%02x", DATA[i]);
            }
            printf("\r\n");
        }
        else
        {
            printf("PcdRead() failed\r\n");
        }
    }

    if(status == MI_OK)//�����ɹ�
    {
        status = MI_ERR;
        printf("Write the card after 1 second. Do not move the card!!!\r\n");
        delay_ms(1000);
        // status = PcdWrite(addr, DATA0);
        // д���ݵ�M1��һ��
        status = PcdWrite(addr, DATA1);
        if(status == MI_OK)//д���ɹ�
        {
            printf("PcdWrite() success\r\n");
        }
        else
        {
            printf("PcdWrite() failed\r\n");
            delay_ms(3000);
        }
    }

    if(status == MI_OK)//д���ɹ�
    {
        status = MI_ERR;
        // ��ȡM1��һ������ ���ַ ��ȡ������
        status = PcdRead(addr, DATA);
        if(status == MI_OK)//�����ɹ�
        {
            // printf("DATA:%s\r\n", DATA);
            printf("DATA:");
            for(i = 0; i < 16; i++)
            {
                printf("%02x", DATA[i]);
            }
            printf("\r\n");
        }
        else
        {
            printf("PcdRead() failed\r\n");
        }
    }

    if(status == MI_OK)//�����ɹ�
    {
        status = MI_ERR;
        printf("RC522_Handle() run finished after 1 second!\r\n");
        delay_ms(1000);
    }
}

// ���Գ���1�����0x0F�� ��֤KEY_A��KEY_B �� дRFID1 ��֤KEY_A1��KEY_B1 �� дRFID2
void RC522_Handle1(void)
{
    u8 i = 0;
    unsigned char test_addr=0x0F;
    status = PcdRequest(PICC_REQALL,CT);//Ѱ��

    // printf("\r\nstatus>>>>>>%d\r\n", status);

    if(status==MI_OK)// Ѱ���ɹ�
    {
        status=MI_ERR;
        status = PcdAnticoll(SN);// ����ײ ���UID ����SN
    }

    if (status==MI_OK)// ����ײ�ɹ�
    {
        status = MI_ERR;
        ShowID(SN); // ���ڴ�ӡ����ID�� UID

        // �ѵ�����Ϊ�������ж��𡣡���
        if((SN[0]==card_0[0])&&(SN[1]==card_0[1])&&(SN[2]==card_0[2])&&(SN[3]==card_0[3]))
        {
            card0_bit=1;
            printf("\r\nThe User is:card_0\r\n");
        }
        if((SN[0]==card_1[0])&&(SN[1]==card_1[1])&&(SN[2]==card_1[2])&&(SN[3]==card_1[3]))
        {
            card1_bit=1;
            printf("\r\nThe User is:card_1\r\n");
        }

        status = PcdSelect(SN);
    }
    else
    {
    }

    if(status == MI_OK)//ѡ���ɹ�
    {
        status = MI_ERR;
        // ��֤A��Կ ���ַ ���� SN
        // ע�⣺�˴��Ŀ��ַ0x0F��3����3���飬�˿��ַֻ��Ҫָ��ĳһ�����Ϳ����ˣ���3����Ϊ0x0C-0x0F�����Χ����Ч����ֻ�ܶ���֤�����������ж�д����
        status = PcdAuthState(KEYA, test_addr, KEY_A, SN);
        if(status == MI_OK)//��֤�ɹ�
        {
            printf("PcdAuthState(A) success\r\n");
        }
        else
        {
            printf("PcdAuthState(A) failed\r\n");
            status = MI_OK;
            goto P1;
        }
        // ��֤B��Կ ���ַ ���� SN
        status = PcdAuthState(KEYB, test_addr, KEY_B, SN);
        if(status == MI_OK)//��֤�ɹ�
        {
            printf("PcdAuthState(B) success\r\n");
        }
        else
        {
            printf("PcdAuthState(B) failed\r\n");
        }
    }

    if(status == MI_OK)//��֤�ɹ�
    {
        status = MI_ERR;
        // ��ȡM1��һ������ ���ַ ��ȡ������ ע�⣺��Ϊ������֤��������3����������ֻ�ܶ�2���������ݽ��ж�д����0x0C-0x0F�����Χ��������Χ��ȡʧ�ܡ�
        status = PcdRead(test_addr, DATA);
        if(status == MI_OK)//�����ɹ�
        {
            // printf("RFID:%s\r\n", RFID);
            printf("DATA:");
            for(i = 0; i < 16; i++)
            {
                printf("%02x", DATA[i]);
            }
            printf("\r\n");
        }
        else
        {
            printf("PcdRead() failed\r\n");
        }
    }

    if(status == MI_OK)//�����ɹ�
    {
        status = MI_ERR;
        // д���ݵ�M1��һ��
        status = PcdWrite(test_addr, RFID1);
        if(status == MI_OK)//д���ɹ�
        {
            printf("PcdWrite(RFID1) success\r\n");
        }
        else
        {
            printf("PcdWrite(RFID1) failed\r\n");
            delay_ms(3000);
        }
    }

P1:
    if(status == MI_OK)//д���ɹ�
    {
        status = MI_ERR;
        // ��֤A��Կ ���ַ ���� SN
        // ע�⣺�˴��Ŀ��ַ0x0F��3����3���飬�˿��ַֻ��Ҫָ��ĳһ�����Ϳ����ˣ���3����Ϊ0x0C-0x0F�����Χ����Ч����ֻ�ܶ���֤�����������ж�д����
        status = PcdAuthState(KEYA, test_addr, KEY_A1, SN);
        if(status == MI_OK)//��֤�ɹ�
        {
            printf("PcdAuthState(A1) success\r\n");
        }
        else
        {
            printf("PcdAuthState(A1) failed\r\n");
        }
        // ��֤B��Կ ���ַ ���� SN
        status = PcdAuthState(KEYB, test_addr, KEY_B1, SN);
        if(status == MI_OK)//��֤�ɹ�
        {
            printf("PcdAuthState(B1) success\r\n");
        }
        else
        {
            printf("PcdAuthState(B1) failed\r\n");
        }
    }

    if(status == MI_OK)//��֤�ɹ�
    {
        status = MI_ERR;
        // ��ȡM1��һ������ ���ַ ��ȡ������ ע�⣺��Ϊ������֤��������3����������ֻ�ܶ�2���������ݽ��ж�д����0x0C-0x0F�����Χ��������Χ��ȡʧ�ܡ�
        status = PcdRead(test_addr, DATA);
        if(status == MI_OK)//�����ɹ�
        {
            // printf("RFID:%s\r\n", RFID);
            printf("DATA:");
            for(i = 0; i < 16; i++)
            {
                printf("%02x", DATA[i]);
            }
            printf("\r\n");
        }
        else
        {
            printf("PcdRead() failed\r\n");
        }
    }

    if(status == MI_OK)//�����ɹ�
    {
        status = MI_ERR;
        // д���ݵ�M1��һ��
        status = PcdWrite(test_addr, RFID2);
        if(status == MI_OK)//д���ɹ�
        {
            printf("PcdWrite(RFID2) success\r\n");
        }
        else
        {
            printf("PcdWrite(RFID2) failed\r\n");
            delay_ms(3000);
        }
    }

    if(status == MI_OK)//д���ɹ�
    {
        status = MI_ERR;
        // ��ȡM1��һ������ ���ַ ��ȡ������
        status = PcdRead(test_addr, DATA);
        if(status == MI_OK)//�����ɹ�
        {
            // printf("DATA:%s\r\n", DATA);
            printf("DATA:");
            for(i = 0; i < 16; i++)
            {
                printf("%02x", DATA[i]);
            }
            printf("\r\n");
        }
        else
        {
            printf("PcdRead() failed\r\n");
        }
    }

    if(status == MI_OK)//�����ɹ�
    {
        status = MI_ERR;
        printf("RC522_Handle1() run finished after 1 second!\r\n");
        delay_ms(1000);
    }
}

// ���������ݱ��Ƴ��򣬽���ѧϰ�ο�������Ƿ�ʹ�� ���card_0�����ƽ�
void RC522_data_break(void)
{
    // ���ƵĿ��ַ
    unsigned char break_addr = 0x13;
    u8 i = 0;
    u8 break_KEY[6]= {0, 0, 0, 0, 0, 0};
    // �����ַ�����
/*    u8 key_arr[257] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
        96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
        208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
        224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
        240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
    };
*/
	
	u8 key_arr2[257] = {
		255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 
		239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 
		223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 
		207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, 
		191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 
		175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 
		159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 
		143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 
		127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 
		111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 
		95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 
		79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 
		63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 
		47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 
		31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 
		15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
	};
	
    // �±�
    u8 arr[6] = {0, 0, 0, 0, 0, 0};

    /*
    for(int i = 0; i <= 255; i++)
    {
        printf("%d, ", i);
    }
    */

    status = PcdRequest(PICC_REQALL,CT);//Ѱ��

    // printf("\r\nstatus>>>>>>%d\r\n", status);

    if(status==MI_OK)// Ѱ���ɹ�
    {
        status=MI_ERR;
        status = PcdAnticoll(SN);// ����ײ ���UID ����SN
    }

    if (status==MI_OK)// ����ײ�ɹ�
    {
        status = MI_ERR;
        ShowID(SN); // ���ڴ�ӡ����ID�� UID

        // �ѵ�����Ϊ�������ж��𡣡���
        if((SN[0]==card_0[0])&&(SN[1]==card_0[1])&&(SN[2]==card_0[2])&&(SN[3]==card_0[3]))
        {
            card0_bit=1;
            printf("\r\nThe User is:card_0\r\n");
        }
        else
        {
            printf("\r\nThe User isn't:card_0\r\n");
            return;
        }

        status = PcdSelect(SN);
    }
    else
    {
    }

    if(status == MI_OK)//ѡ���ɹ�
    {
        status = MI_ERR;

        // ���ɷ��� ������ �Ҵ������һ�� ȫ������� ��Ҫѭ��281���ڴ� �ҵ�stm32 1�����ѭ��5�� �Ǿ�Ҫ 56������ 155��Сʱ 177����
        for(arr[0] = 0; arr[0] <= 255; arr[0]++)
        {
            for(arr[1] = 0; arr[1] <= 255; arr[1]++)
            {
                for(arr[2] = 0; arr[2] <= 255; arr[2]++)
                {
                    for(arr[3] = 0; arr[3] <= 255; arr[3]++)
                    {
                        for(arr[4] = 0; arr[4] <= 255; arr[4]++)
                        {
                            for(arr[5] = 0; arr[5] <= 255; arr[5]++)
                            {
                                // printf("%x%x%x%x%x%x, ", key_arr[arr[0]], key_arr[arr[1]], key_arr[arr[2]], key_arr[arr[3]], key_arr[arr[4]], key_arr[arr[5]]);
                                break_KEY[0] = key_arr2[arr[0]];
                                break_KEY[1] = key_arr2[arr[1]];
                                break_KEY[2] = key_arr2[arr[2]];
                                break_KEY[3] = key_arr2[arr[3]];
                                break_KEY[4] = key_arr2[arr[4]];
                                break_KEY[5] = key_arr2[arr[5]];

                                // ��֤A��Կ ���ַ ���� SN
                                // ע�⣺�˴��Ŀ��ַ0x0F��3����3���飬�˿��ַֻ��Ҫָ��ĳһ�����Ϳ����ˣ���3����Ϊ0x0C-0x0F�����Χ����Ч����ֻ�ܶ���֤�����������ж�д����
                                status = PcdAuthState(KEYA, break_addr, break_KEY, SN);
                                if(status == MI_OK)//��֤�ɹ�
                                {
                                    printf("PcdAuthState(A) success\r\n");
                                    goto P1;
                                }
                                else
                                {
                                    // printf("PcdAuthState(A) failed\r\n");
                                    printf(".");
                                }

                                // ��֤B��Կ ���ַ ���� SN
                                status = PcdAuthState(KEYB, break_addr, break_KEY, SN);
                                if(status == MI_OK)//��֤�ɹ�
                                {
                                    printf("PcdAuthState(B) success\r\n");
                                    goto P1;
                                }
                                else
                                {
                                    // printf("PcdAuthState(B) failed\r\n");
                                    printf(",");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

P1:
    if(status == MI_OK)//��֤�ɹ�
    {
        status = MI_ERR;
        // ��ȡM1��һ������ ���ַ ��ȡ������ ע�⣺��Ϊ������֤��������3����������ֻ�ܶ�2���������ݽ��ж�д����0x0C-0x0F�����Χ��������Χ��ȡʧ�ܡ�
        status = PcdRead(break_addr, DATA);
        if(status == MI_OK)//�����ɹ�
        {
            // printf("RFID:%s\r\n", RFID);
            printf("DATA:");
            for(i = 0; i < 16; i++)
            {
                printf("%02x", DATA[i]);
            }
            printf("\r\n");
        }
        else
        {
            printf("PcdRead() failed\r\n");
        }
    }

    delay_ms(3000);
}

void RC522_Init ( void )
{
    SPI1_Init();

    RC522_Reset_Disable();

    RC522_CS_Disable();

    PcdReset ();

    M500PcdConfigISOType ( 'A' );//���ù�����ʽ

}

void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE );//PORTA��Bʱ��ʹ��
    RCC_APB1PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE );												//SPI1ʱ��ʹ��

    // SDA   PA4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��PF0��PF1

    // SCK    PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // MISO				PA6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // MOSI   PA0
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // RST   PC2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  					//����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;																	//����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;															//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;																		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    // SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    // SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;																	//����ͬ��ʱ�ӵĵ�һ�������أ��½������ݱ�����
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;																		//����ͬ��ʱ�ӵĵڶ��������أ����������ݱ�����
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;																			//NSS�ź���Ӳ����NSS�ܽţ�����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    // RC522 SPIͨѶʱ��������СΪ100ns	��Ƶ�����Ϊ10MHZ
    // RC522 �������½��ر仯
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;					//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256����������36M/256=140.625KHz
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;														//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;																			//CRCֵ����Ķ���ʽ
    SPI_Init(SPI1, &SPI_InitStructure); 						 															//����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

    SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
}


/*
 * ��������SPI_RC522_SendByte
 * ����  ����RC522����1 Byte ����
 * ����  ��byte��Ҫ���͵�����
 * ����  : RC522���ص�����
 * ����  ���ڲ�����
 */
void SPI_RC522_SendByte ( u8 byte )
{
    u8 counter;

    for(counter=0; counter<8; counter++)
    {
        if ( byte & 0x80 )
            RC522_MOSI_1 ();
        else
            RC522_MOSI_0 ();

        RC522_DELAY();
        RC522_SCK_0 ();
        RC522_DELAY();
        RC522_SCK_1();
        RC522_DELAY();

        byte <<= 1;
    }
}


/*
 * ��������SPI_RC522_ReadByte
 * ����  ����RC522����1 Byte ����
 * ����  ����
 * ����  : RC522���ص�����
 * ����  ���ڲ�����
 */
u8 SPI_RC522_ReadByte ( void )
{
    u8 counter;
    u8 SPI_Data;

    for(counter=0; counter<8; counter++)
    {
        SPI_Data <<= 1;

        RC522_SCK_0 ();

        RC522_DELAY();

        if ( RC522_MISO_GET() == 1)
            SPI_Data |= 0x01;

        RC522_DELAY();

        RC522_SCK_1 ();

        RC522_DELAY();
    }

//	printf("****%c****",SPI_Data);
    return SPI_Data;
}


/*
 * ��������ReadRawRC
 * ����  ����RC522�Ĵ���
 * ����  ��ucAddress���Ĵ�����ַ
 * ����  : �Ĵ����ĵ�ǰֵ
 * ����  ���ڲ�����
 */
u8 ReadRawRC ( u8 ucAddress )
{
    u8 ucAddr, ucReturn;

    ucAddr = ( ( ucAddress << 1 ) & 0x7E ) | 0x80;

    RC522_CS_Enable();

    SPI_RC522_SendByte ( ucAddr );

    ucReturn = SPI_RC522_ReadByte ();

    RC522_CS_Disable();

    return ucReturn;
}


/*
 * ��������WriteRawRC
 * ����  ��дRC522�Ĵ���
 * ����  ��ucAddress���Ĵ�����ַ
 *         ucValue��д��Ĵ�����ֵ
 * ����  : ��
 * ����  ���ڲ�����
 */
void WriteRawRC ( u8 ucAddress, u8 ucValue )
{
    u8 ucAddr;

    ucAddr = ( ucAddress << 1 ) & 0x7E;

    RC522_CS_Enable();

    SPI_RC522_SendByte ( ucAddr );

    SPI_RC522_SendByte ( ucValue );

    RC522_CS_Disable();
}


/*
 * ��������SetBitMask
 * ����  ����RC522�Ĵ�����λ
 * ����  ��ucReg���Ĵ�����ַ
 *         ucMask����λֵ
 * ����  : ��
 * ����  ���ڲ�����
 */
void SetBitMask ( u8 ucReg, u8 ucMask )
{
    u8 ucTemp;

    ucTemp = ReadRawRC ( ucReg );

    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask
}


/*
 * ��������ClearBitMask
 * ����  ����RC522�Ĵ�����λ
 * ����  ��ucReg���Ĵ�����ַ
 *         ucMask����λֵ
 * ����  : ��
 * ����  ���ڲ�����
 */
void ClearBitMask ( u8 ucReg, u8 ucMask )
{
    u8 ucTemp;

    ucTemp = ReadRawRC ( ucReg );

    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask
}


/*
 * ��������PcdAntennaOn
 * ����  ����������
 * ����  ����
 * ����  : ��
 * ����  ���ڲ�����
 */
void PcdAntennaOn ( void )
{
    u8 uc;

    uc = ReadRawRC ( TxControlReg );

    if ( ! ( uc & 0x03 ) )
        SetBitMask(TxControlReg, 0x03);
}


/*
 * ��������PcdAntennaOff
 * ����  ���ر�����
 * ����  ����
 * ����  : ��
 * ����  ���ڲ�����
 */
void PcdAntennaOff ( void )
{
    ClearBitMask ( TxControlReg, 0x03 );
}


/*
 * ��������PcdRese
 * ����  ����λRC522
 * ����  ����
 * ����  : ��
 * ����  ���ⲿ����
 */
void PcdReset ( void )
{
    RC522_Reset_Disable();

    delay_us ( 1 );

    RC522_Reset_Enable();

    delay_us ( 1 );

    RC522_Reset_Disable();

    delay_us ( 1 );

    WriteRawRC ( CommandReg, 0x0f );

    while ( ReadRawRC ( CommandReg ) & 0x10 );

    delay_us ( 1 );

    WriteRawRC ( ModeReg, 0x3D );            //���巢�ͺͽ��ճ���ģʽ ��Mifare��ͨѶ��CRC��ʼֵ0x6363

    WriteRawRC ( TReloadRegL, 30 );          //16λ��ʱ����λ
    WriteRawRC ( TReloadRegH, 0 );			 //16λ��ʱ����λ

    WriteRawRC ( TModeReg, 0x8D );		      //�����ڲ���ʱ��������

    WriteRawRC ( TPrescalerReg, 0x3E );			 //���ö�ʱ����Ƶϵ��

    WriteRawRC ( TxAutoReg, 0x40 );				   //���Ʒ����ź�Ϊ100%ASK
}


/*
 * ��������M500PcdConfigISOType
 * ����  ������RC522�Ĺ�����ʽ
 * ����  ��ucType��������ʽ
 * ����  : ��
 * ����  ���ⲿ����
 */
void M500PcdConfigISOType ( u8 ucType )
{
    if ( ucType == 'A')                     //ISO14443_A
    {
        ClearBitMask ( Status2Reg, 0x08 );

        WriteRawRC ( ModeReg, 0x3D );//3F

        WriteRawRC ( RxSelReg, 0x86 );//84

        WriteRawRC( RFCfgReg, 0x7F );   //4F

        WriteRawRC( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec)

        WriteRawRC ( TReloadRegH, 0 );

        WriteRawRC ( TModeReg, 0x8D );

        WriteRawRC ( TPrescalerReg, 0x3E );

        delay_us ( 2 );

        PcdAntennaOn ();//������
    }
}


/*
 * ��������PcdComMF522
 * ����  ��ͨ��RC522��ISO14443��ͨѶ
 * ����  ��ucCommand��RC522������
 *         pInData��ͨ��RC522���͵���Ƭ������
 *         ucInLenByte���������ݵ��ֽڳ���
 *         pOutData�����յ��Ŀ�Ƭ��������
 *         pOutLenBit���������ݵ�λ����
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ڲ�����
 */
char PcdComMF522 ( u8 ucCommand, u8 * pInData, u8 ucInLenByte, u8 * pOutData, u32 * pOutLenBit )
{
    char cStatus = MI_ERR;
    u8 ucIrqEn   = 0x00;
    u8 ucWaitFor = 0x00;
    u8 ucLastBits;
    u8 ucN;
    u32 ul;

    switch ( ucCommand )
    {
    case PCD_AUTHENT:		//Mifare��֤
        ucIrqEn   = 0x12;		//���������ж�����ErrIEn  ���������ж�IdleIEn
        ucWaitFor = 0x10;		//��֤Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ
        break;

    case PCD_TRANSCEIVE:		//���շ��� ���ͽ���
        ucIrqEn   = 0x77;		//����TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
        ucWaitFor = 0x30;		//Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ�� �����жϱ�־λ
        break;

    default:
        break;
    }

    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );		//IRqInv��λ�ܽ�IRQ��Status1Reg��IRqλ��ֵ�෴
    ClearBitMask ( ComIrqReg, 0x80 );			//Set1��λ����ʱ��CommIRqReg������λ����
    WriteRawRC ( CommandReg, PCD_IDLE );		//д��������
    SetBitMask ( FIFOLevelReg, 0x80 );			//��λFlushBuffer����ڲ�FIFO�Ķ���дָ���Լ�ErrReg��BufferOvfl��־λ�����

    for ( ul = 0; ul < ucInLenByte; ul ++ )
        WriteRawRC ( FIFODataReg, pInData [ ul ] );    		//д���ݽ�FIFOdata

    WriteRawRC ( CommandReg, ucCommand );					//д����

    if ( ucCommand == PCD_TRANSCEIVE )
        SetBitMask(BitFramingReg,0x80);  				//StartSend��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч

    ul = 1000;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms

    do 														//��֤ ��Ѱ���ȴ�ʱ��
    {
        ucN = ReadRawRC ( ComIrqReg );							//��ѯ�¼��ж�
        ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );		//�˳�����i=0,��ʱ���жϣ���д��������

    ClearBitMask ( BitFramingReg, 0x80 );					//��������StartSendλ

    if ( ul != 0 )
    {
        if ( ! (( ReadRawRC ( ErrorReg ) & 0x1B )) )			//�������־�Ĵ���BufferOfI CollErr ParityErr ProtocolErr
        {
            cStatus = MI_OK;

            if ( ucN & ucIrqEn & 0x01 )					//�Ƿ�����ʱ���ж�
                cStatus = MI_NOTAGERR;

            if ( ucCommand == PCD_TRANSCEIVE )
            {
                ucN = ReadRawRC ( FIFOLevelReg );			//��FIFO�б�����ֽ���

                ucLastBits = ReadRawRC ( ControlReg ) & 0x07;	//�����յ����ֽڵ���Чλ��

                if ( ucLastBits )
                    * pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;   	//N���ֽ�����ȥ1�����һ���ֽڣ�+���һλ��λ�� ��ȡ����������λ��
                else
                    * pOutLenBit = ucN * 8;   					//�����յ����ֽ������ֽ���Ч

                if ( ucN == 0 )
                    ucN = 1;

                if ( ucN > MAXRLEN )
                    ucN = MAXRLEN;

                for ( ul = 0; ul < ucN; ul ++ )
                    pOutData [ ul ] = ReadRawRC ( FIFODataReg );
            }
        }
        else
            cStatus = MI_ERR;
//			printf(ErrorReg);
    }

    SetBitMask ( ControlReg, 0x80 );           // stop timer now
    WriteRawRC ( CommandReg, PCD_IDLE );

    return cStatus;
}


/*
 * ��������PcdRequest
 * ����  ��Ѱ��
 * ����  ��ucReq_code��Ѱ����ʽ
 *                     = 0x52��Ѱ��Ӧ�������з���14443A��׼�Ŀ�
 *                     = 0x26��Ѱδ��������״̬�Ŀ�
 *         pTagType����Ƭ���ʹ���
 *                   = 0x4400��Mifare_UltraLight
 *                   = 0x0400��Mifare_One(S50)
 *                   = 0x0200��Mifare_One(S70)
 *                   = 0x0800��Mifare_Pro(X))
 *                   = 0x4403��Mifare_DESFire
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdRequest ( u8 ucReq_code, u8 * pTagType )
{
    char cStatus;
    u8 ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ClearBitMask ( Status2Reg, 0x08 );	//����ָʾMIFARECyptol��Ԫ��ͨ�Լ����п�������ͨ�ű����ܵ����
    WriteRawRC ( BitFramingReg, 0x07 );	//	���͵����һ���ֽڵ� ��λ
    SetBitMask ( TxControlReg, 0x03 );	//TX1,TX2�ܽŵ�����źŴ��ݾ����͵��Ƶ�13.56�������ز��ź�

    ucComMF522Buf [ 0 ] = ucReq_code;		//���� ��Ƭ������

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE,	ucComMF522Buf, 1, ucComMF522Buf, & ulLen );	//Ѱ��

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )	//Ѱ���ɹ����ؿ�����
    {
        * pTagType = ucComMF522Buf [ 0 ];
        * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
    }
    else
        cStatus = MI_ERR;

    return cStatus;
}


/*
 * ��������PcdAnticoll
 * ����  ������ײ
 * ����  ��pSnr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdAnticoll ( u8 * pSnr )
{
    char cStatus;
    u8 uc, ucSnr_check = 0;
    u8 ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ClearBitMask ( Status2Reg, 0x08 );		//��MFCryptol Onλ ֻ�гɹ�ִ��MFAuthent����󣬸�λ������λ
    WriteRawRC ( BitFramingReg, 0x00);		//�����Ĵ��� ֹͣ�շ�
    ClearBitMask ( CollReg, 0x80 );			//��ValuesAfterColl���н��յ�λ�ڳ�ͻ�����

    /*
    �ο�ISO14443Э�飺https://blog.csdn.net/wowocpp/article/details/79910800
    PCD ���� SEL = ��93����NVB = ��20�������ֽ�
    ��ʹ���е��ڳ���PICC����������UID CLn��ΪӦ��
    */
    ucComMF522Buf [ 0 ] = 0x93;	//��Ƭ����ͻ����
    ucComMF522Buf [ 1 ] = 0x20;

    // ���Ͳ��������� ���յ����ݴ洢��ucComMF522Buf
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//�뿨Ƭͨ��

    if ( cStatus == MI_OK)		//ͨ�ųɹ�
    {
        // �յ���UID ����pSnr
        for ( uc = 0; uc < 4; uc ++ )
        {
            * ( pSnr + uc )  = ucComMF522Buf [ uc ];			//����UID
            ucSnr_check ^= ucComMF522Buf [ uc ];
        }

        if ( ucSnr_check != ucComMF522Buf [ uc ] )
            cStatus = MI_ERR;

    }

    SetBitMask ( CollReg, 0x80 );

    return cStatus;
}


/*
 * ��������CalulateCRC
 * ����  ����RC522����CRC16
 * ����  ��pIndata������CRC16������
 *         ucLen������CRC16�������ֽڳ���
 *         pOutData����ż�������ŵ��׵�ַ
 * ����  : ��
 * ����  ���ڲ�����
 */
void CalulateCRC ( u8 * pIndata, u8 ucLen, u8 * pOutData )
{
    u8 uc, ucN;

    ClearBitMask(DivIrqReg, 0x04);

    WriteRawRC(CommandReg, PCD_IDLE);

    SetBitMask(FIFOLevelReg, 0x80);

    for ( uc = 0; uc < ucLen; uc ++)
        WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );

    WriteRawRC ( CommandReg, PCD_CALCCRC );

    uc = 0xFF;

    do
    {
        ucN = ReadRawRC ( DivIrqReg );
        uc --;
    } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );

    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );
}


/*
 * ��������PcdSelect
 * ����  ��ѡ����Ƭ
 * ����  ��pSnr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdSelect ( u8 * pSnr )
{
    char cStatus;
    u8 uc;
    u8 ucComMF522Buf [ MAXRLEN ];
    u32  ulLen;

    // ����ײ 0x93
    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
    // ����û�г�ͻ��PCD ָ��NVBΪ70����ֵ��ʾPCD������������UID CLn����40λUID CLn ƥ���PICC����SAK��ΪӦ��
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;

    // 3 4 5 6λ���UID����7λһֱ��򡣡���
    for ( uc = 0; uc < 4; uc ++ )
    {
        ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
        ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }

    // CRC(ѭ������У��)
    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );

    ClearBitMask ( Status2Reg, 0x08 );

    // ���Ͳ���������
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x18 ) )
        cStatus = MI_OK;
    else
        cStatus = MI_ERR;

    return cStatus;
}


/*
 * ��������PcdAuthState
 * ����  ����֤��Ƭ����
 * ����  ��ucAuth_mode��������֤ģʽ
 *                     = KEYA (0x60)����֤A��Կ
 *                     = KEYB (0x61)����֤B��Կ
 *         u8 ucAddr�����ַ
 *         pKey������
 *         pSnr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdAuthState ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr )
{
    char cStatus;
    u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;

    for ( uc = 0; uc < 6; uc ++ )
        ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );

    for ( uc = 0; uc < 6; uc ++ )
        ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );

    // printf("char PcdAuthState ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr )\r\n");
    // printf("before PcdComMF522() ucComMF522Buf:%s\r\n", ucComMF522Buf);

    // ��֤��Կ����
    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );

    // printf("after PcdComMF522() ucComMF522Buf:%s\r\n", ucComMF522Buf);

    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
    {
//			if(cStatus != MI_OK)
//					printf("666")	;
//			else
//				printf("888");
        cStatus = MI_ERR;
    }

    return cStatus;
}


/*
 * ��������PcdWrite
 * ����  ��д���ݵ�M1��һ��
 * ����  ��u8 ucAddr�����ַ
 *         pData��д������ݣ�16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdWrite ( u8 ucAddr, u8 * pData )
{
    char cStatus;
    u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ucComMF522Buf [ 0 ] = PICC_WRITE;
    ucComMF522Buf [ 1 ] = ucAddr;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
        cStatus = MI_ERR;

    if ( cStatus == MI_OK )
    {
        memcpy(ucComMF522Buf, pData, 16);
        for ( uc = 0; uc < 16; uc ++ )
            ucComMF522Buf [ uc ] = * ( pData + uc );

        CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );

        cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );

        if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
            cStatus = MI_ERR;

    }
    return cStatus;
}


/*
 * ��������PcdRead
 * ����  ����ȡM1��һ������
 * ����  ��u8 ucAddr�����ַ
 *         pData�����������ݣ�16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdRead ( u8 ucAddr, u8 * pData )
{
    char cStatus;
    u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ucComMF522Buf [ 0 ] = PICC_READ;
    ucComMF522Buf [ 1 ] = ucAddr;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
        for ( uc = 0; uc < 16; uc ++ )
            * ( pData + uc ) = ucComMF522Buf [ uc ];
    }
    else
        cStatus = MI_ERR;

    return cStatus;
}


/*
 * ��������PcdHalt
 * ����  �����Ƭ��������״̬
 * ����  ����
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdHalt( void )
{
    u8 ucComMF522Buf [ MAXRLEN ];
    u32  ulLen;

    ucComMF522Buf [ 0 ] = PICC_HALT;
    ucComMF522Buf [ 1 ] = 0;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
    PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    return MI_OK;
}

// UIDΪ��Ҫ�޸ĵĿ���UID key_type��0ΪKEYA����0ΪKEYB KEYΪ��Կ RW:1�Ƕ���0��д data_addrΪ�޸ĵĵ�ַ dataΪ��������
void IC_RW ( u8 * UID, u8 key_type, u8 * KEY, u8 RW, u8 data_addr, u8 * data )
{
	char status;
	u8 i = 0;
    u8 ucArray_ID [ 4 ] = { 0 };//�Ⱥ���IC�������ͺ�UID(IC�����к�)

    status = PcdRequest ( 0x52, ucArray_ID );//Ѱ��
	if(status == MI_OK)
		ShowID(ucArray_ID);
	else
		return;

    status = PcdAnticoll ( ucArray_ID );//����ײ
	if(status != MI_OK)
		return;

    status = PcdSelect ( UID );//ѡ����
	if(status != MI_OK)
	{
		printf("UID don't match\r\n");
		return;
	}
		
	if(0 == key_type)
		status = PcdAuthState ( KEYA, data_addr, KEY, UID );//У��
	else
		status = PcdAuthState ( KEYB, data_addr, KEY, UID );//У��

	if(status != MI_OK)
	{
		printf("KEY don't match\r\n");
		return;
	}
	
    if ( RW )//��дѡ��1�Ƕ���0��д
    {
		status = PcdRead ( data_addr, data );
		if(status == MI_OK)
		{
			printf("data:");
			for(i = 0; i < 16; i++)
            {
                printf("%02x", data[i]);
            }
            printf("\r\n");
		}
		else
		{
			printf("PcdRead() failed\r\n");
			return;
		}
	}
    else
	{
        status = PcdWrite ( data_addr, data );
		if(status == MI_OK)
		{
			printf("PcdWrite() finished\r\n");
		}
		else
		{
			printf("PcdWrite() failed\r\n");
			return;
		}
	}

    status = PcdHalt ();
	if(status == MI_OK)
	{
		printf("PcdHalt() finished\r\n");
	}
	else
	{
		printf("PcdHalt() failed\r\n");
		return;
	}
}

// ��ʾ���Ŀ��ţ���ʮ��������ʾ
void ShowID(u8 *p)
{
    u8 num[9];
    u8 i;

    for(i=0; i<4; i++)
    {
        num[i*2] = p[i] / 16;
        num[i*2] > 9 ? (num[i*2] += '7') : (num[i*2] += '0');
        num[i*2+1] = p[i] % 16;
        num[i*2+1] > 9 ? (num[i*2+1] += '7') : (num[i*2+1] += '0');
    }
    num[8] = 0;
    printf("ID>>>%s\r\n", num);
}

//�ȴ����뿪
void WaitCardOff(void)
{
    char status;
    unsigned char	TagType[2];

    while(1)
    {
        status = PcdRequest(REQ_ALL, TagType);
        if(status)
        {
            status = PcdRequest(REQ_ALL, TagType);
            if(status)
            {
                status = PcdRequest(REQ_ALL, TagType);
                if(status)
                {
                    return;
                }
            }
        }
        delay_ms(1000);
    }
}

