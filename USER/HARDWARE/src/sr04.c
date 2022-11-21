#include "sr04.h"

float time = 0;

void SR04_Init(void)
{
	/* 初始化Trip */
	GPIO_InitTypeDef  GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //Trip-->PC1端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //Echo-->PC2端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //下拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC2
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1); //Trip先拉低
	GPIO_ResetBits(GPIOC,GPIO_Pin_2); //Echo也拉低
	TIM4_Init(65535,71);
}


void TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

	TIM_Cmd(TIM4, DISABLE);  //关闭TIMx	，到时再开				 
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





