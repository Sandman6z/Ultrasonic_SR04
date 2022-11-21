#include "sys.h"
#include "delay.h"
#include "sr04.h"
#include "led.h"
#include "usart.h"
#include "oled.h"
#include "key.h"
#include "stdio.h"


//int main(void)
//{
//	delay_init();	    //��ʱ������ʼ��	  
//	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
//    SR04_Init();
//    uart_init(115200);
//	
//	float Length = 0;
//	
// 	while(1)
//	{
//		LED0 =!LED0;
//		Length = (SR04_Getlen()*340/2/10000);
//        printf ("����Ϊ%.2fcm \r\n",Length);
//        delay_ms(100);
//	}
//}


void Show_float(float x);

int main(void)
{
	vu8 key = 0;
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
  SR04_Init();
	OLED_Init();
	KEY_Init();
	
	float Length = 0;
	unsigned char kong[] = "       ";
	
	OLED_ShowCHinese(16,2,0,32,Welcome);
	OLED_ShowCHinese(32,2,1,32,Welcome);
	OLED_ShowCHinese(48,2,2,32,Welcome);
	OLED_ShowCHinese(64,2,3,32,Welcome);
	OLED_ShowCHinese(80,2,4,32,Welcome);
	OLED_ShowCHinese(96,2,5,32,Welcome);
  delay_ms(1000);

	
 	while(1)
	{
		LED0 =!LED0;
		key=KEY_Scan(0);	//�õ���ֵ
		if (key)
		{
			switch(key)
			{
				case KEY0_PRES:
					OLED_Clear();
					OLED_ShowCHinese(8,2,0,32,Distance);
					OLED_ShowCHinese(24,2,1,32,Distance);
					OLED_ShowCHinese(40,2,2,32,Distance);
					OLED_ShowCHinese(56,2,3,32,Distance);
					break;
			}
			while(1)
			{
				Length = (SR04_Getlen()*340/2/10000);
				OLED_ShowString(72,2,kong);
				Show_float(Length);
				delay_ms(100);
				key=KEY_Scan(0);	//�õ���ֵ
				if (key) break;
			}
		}else delay_ms(100);
	}
}

void Show_float(float x)
{
	int temp1 = (int)x;
	int temp2 = (int)((x-temp1)*10.0);
	int wei1 = 0,wei2 = 0,tmp;
	unsigned char dian[] = ".";
	unsigned char danwei[] = "cm";
	tmp = temp1;
	while(tmp != 0)
	{
		tmp/=10;
		wei1++;
	}
	tmp = temp2;
	while(tmp != 0)
	{
		tmp/=10;
		wei2++;
	}
	OLED_ShowNum(72,2,temp1,wei1,16);
	OLED_ShowString(72+wei1*8,2,dian);
	OLED_ShowNum(72+wei1*8+8,2,temp2,wei2,16);
	OLED_ShowString(72+wei1*8+8+wei2*8,2,danwei);
}



