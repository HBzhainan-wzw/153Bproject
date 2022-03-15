#include "sys.h"  
#include "stdio.h"
#include "usart.h"	  
#include "motor.h" 

//IO��ʼ��

void MOTOR_Init(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; 
	//GPIOB����15��14��13��12��11��10��9��8��
	// output moder
	// DIR
	GPIOB->MODER &= ~GPIO_MODER_MODE8;
	GPIOB->MODER &= GPIO_MODER_MODE8_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED8;
	// STEP
	GPIOB->MODER &= ~GPIO_MODER_MODE9;
	GPIOB->MODER &= GPIO_MODER_MODE9_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED9;
  // ENABLE
	GPIOB->MODER &= ~GPIO_MODER_MODE13;
	GPIOB->MODER &= GPIO_MODER_MODE13_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	// set high
	GPIOB->ODR |= 1 << 9;
	GPIOB->ODR |= 1 << 8;
	
}
//ϸ��
//  x==1 ȫ��
//  x==2 �벽 
//  x==4 1/4��
//  x==8 1/8��
//  x==16 1/16��
//void Step_Micr(uint16_t x)
//{
//	switch(x)
//	{
//		case 1:Full_step;
//		break;
//		case 2:Half_step;break;
//		case 4:Quarter_step;break;
//		case 8:Eighth_step;break;
//		case 16:Sixteenth_step;break;
//		default:break;
//    }   
//}
//����
//dir:FALSE��תTRUE��ת
//period ����
//step   ����
void Step_Control(uint8_t dir,uint16_t period,uint32_t steps)
{
	uint32_t i;
	for(i=0; i <= steps;i++)
	{
		DIR = dir;
		STEP = 1;
		STEP = 0;
		// delay period
		uint16_t j = 0;
		while(j < period){
			j++;
		}
	}
}
//�˺����ɱ���
//  0 ����
//  1 ����
void Step_Enable()
{
	ENABLE = 0;
}

