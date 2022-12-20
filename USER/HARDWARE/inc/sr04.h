#ifndef __SR04_H
#define __SR04_H
#include "sys.h"
#include "delay.h"


#define Trip PBout(0)
#define Echo PBin(1)

extern float time;

void SR04_Init(void);
void TIM4_Init(u16 arr,u16 psc);
float SR04_Getlen(void);



#endif







