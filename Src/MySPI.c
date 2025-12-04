#include "MySPI.h"
#include "stm32f103xe.h"
#include "MyDefines.h"

void MatrixSPI_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;														// Включение тактирования SPI1 (матрица)

	GPIOA->CRL |= GPIO_CRL_MODE5_1 | GPIO_CRL_CNF5_1 | GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1;
	GPIOA->CRL &= ~(GPIO_CRL_MODE5_0 | GPIO_CRL_CNF5_0 | GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_0);
	
	SPI1->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE/*| SPI_CR1_LSBFIRST*/;	// Bidirectional data mode|transmit-only mode | LSB transmitted first
	SPI1->CR1 |= SPI_CR1_BR_Msk | SPI_CR1_MSTR| SPI_CR1_SSM | SPI_CR1_SSI;	// fPCLK/256 | Master configuration | Software slave management enabled | The value of this bit is forced onto the
																																					//NSS pin and the IO value of the NSS pin is ignored.	
	SPI1->CR2 |= SPI_CR2_TXEIE;
	SPI1->CR1 |= SPI_CR1_SPE;
	__enable_irq ();
	NVIC_EnableIRQ(SPI1_IRQn);
}





//*
