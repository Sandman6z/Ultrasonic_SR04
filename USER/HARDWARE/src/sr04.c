#include "sr04.h"

float time = 0;

void SR04_Init(void)
{
	/* ��ʼ��Trip */
	GPIO_InitTypeDef  GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //Trip-->PC1�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //Echo-->PC2�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC2
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1); //Trip������
	GPIO_ResetBits(GPIOC,GPIO_Pin_2); //EchoҲ����
	TIM4_Init(65535,71);
}


void TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
	
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�

	TIM_Cmd(TIM4, DISABLE);  //�ر�TIMx	����ʱ�ٿ�				 
}


float SR04_Getlen(void)
{
	Trip = 1;
	delay_us(20);
	Trip = 0;
	
	while(Echo == 0)
	{
		TIM_SetCounter(TIM4,0);
		TIM_Cmd(TIM4, DISABLE);
	}
	while(Echo == 1)
	{
		TIM_Cmd(TIM4, ENABLE);
	}
	time = TIM_GetCounter(TIM4);
	return time;
}





