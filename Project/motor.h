#include "sys.h"  
#include "stdio.h"
#include "usart.h"	  

#define DIR PBout(9) 		//dir
#define STEP PBout(8)		//step
#define MS3 PBout(12)		//MS3
#define MS2 PBout(11)		//MS2
#define MS1 PBout(10)		//MS1
#define ENABLE PBout(13)//ENABLE
//œ∏∑÷∫Í∂®“Â
#define Full_step {MS1 = 0;MS2 = 0;MS3 = 0;}                  
#define Half_step {MS1 = 1;MS2 = 0;MS3 = 0;}
#define Quarter_step {MS1 = 0;MS2 = 1;MS3 = 0;} 
#define Eighth_step {MS1 = 1;MS2 = 1;MS3 = 0;}
#define Sixteenth_step {MS1 = 1;MS2 = 1;MS3 = 1;} 

void MOTOR_Init(void);
void Step_Micr(uint16_t x);
void Step_Enable(void);
void Step_Control(uint8_t dir,uint16_t period,uint32_t steps);
