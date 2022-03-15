#include "UART.h"

void UART1_Init(void) {
	// [TODO]
	// Enable USART1 clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	// set system clock as USART1 clock 
	RCC->CCIPR |= RCC_CCIPR_USART1SEL_0;
}

void UART2_Init(void) {
	// [TODO]
	// Enable USART2 clock
	RCC->APB1ENR1 |= RCC_APB1RSTR1_USART2RST;
	// set System Clock as USART clock
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
}

void UART1_GPIO_Init(void) {
	// [TODO]
	// PB6 PB7 alternative function
	GPIOB->MODER |= GPIO_MODER_MODE6_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE6_0;
	GPIOB->MODER |= GPIO_MODER_MODE7_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE7_0;
	
	// set up PB6 PB7 alternative function
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL6_3;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL7_3;	
	
	// PB6 PB7 push-pull state (set by default)
	
	// GPIO PB6 PB7 very high speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED7;
	
	//  both GPIO pins to use pull-up resistors for I/O
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6_1;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7_1;	
}

void UART2_GPIO_Init(void) {
	// [TODO]
	// PA2 PA3 alternative function
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE2_0;
	GPIOA->MODER |= GPIO_MODER_MODE3_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE3_0;
	// set up PA2 PA3 alternative function
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_3;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_3;
	
	// PA2 PA3 push-pull state (set by default)
	
	// GPIO PA2 PA3 very high speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
	
	//  both GPIO pins to use pull-up resistors for I/O
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3_1;
}

void USART_Init(USART_TypeDef* USARTx) {
	// [TODO]
	// disable
	USARTx->CR1 &= ~USART_CR1_UE; 
	// set word length to 8 bit (set by default)
	USARTx->CR1 &= ~USART_CR1_M0;
	USARTx->CR1 &= ~USART_CR1_M1;
	// oversample mode to oversample by 16 (set by default)
	USARTx->CR1 &= ~USART_CR1_OVER8;
	// number of stop bit = 1 (set by default)
	USARTx->CR1 &= ~USART_CR2_STOP;
	// baud rate to 9600
	USARTx->BRR = 8333;
	// enable transmitter and receiver
	USARTx->CR1 |= USART_CR1_TE;
	USARTx->CR1 |= USART_CR1_RE;
	// enable
	USARTx->CR1 |= USART_CR1_UE; 
}

uint8_t USART_Read (USART_TypeDef * USARTx) {
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE));  // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag 
}

void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR 
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USARTx->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag 	
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USARTx->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USARTx->ISR &= ~USART_ISR_TC;
}   

void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}
