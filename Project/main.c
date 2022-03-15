
#include <stdint.h>  
#include "motor.h" 
#include "stm32l476xx.h"



void initMotor(int step_pin)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; // enable the GPIOA clock
    GPIOB->MODER |= (0x1 << (step_pin * 2)); // set to output
    GPIOB->OTYPER = 0x00; // push-pull mode
    GPIOB->PUPDR |= (0x2 << (step_pin * 2)); // pull down the pin specified
    GPIOB->ODR = 0x00; // set output register to 0 across all pins
}
 
void stepMotor(int step_pin)
{
    GPIOB->ODR |= (1 << step_pin); // output to the pin specified
    GPIOB->ODR &= ~(1 << step_pin); // reset the output back to 0
}

int main(void)
{
    initMotor(8); // initialise the motor
    unsigned long a = 0;
    while (1)
    {
        if (a == 50000)
        {
            stepMotor(8); // output a pulse to the driver to step the motor, attached to PA2
            a = 0;
        }
        a++;
    }
}
