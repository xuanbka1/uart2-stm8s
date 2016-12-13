#include "stm8s.h"
#include <string.h>


#define PD_ODR *(unsigned char*)0x500A
#define PD_IDR *(unsigned char*)0x500B
#define PD_DDR *(unsigned char*)0x500C
#define PD_CR1 *(unsigned char*)0x500D
#define PD_CR2 *(unsigned char*)0x500E




/* CLOCK */
#define CLK_DIVR	*(unsigned char*)0x50C0
#define CLK_PCKENR1	*(unsigned char*)0x50C3
#define CLK_PCKENR2	*(unsigned char*)0x50C4



/* ------------------- USART ------------------- */
#define USART1_SR *(unsigned char*)0x5240
#define USART1_DR *(unsigned char*)0x5241
#define USART1_BRR1 *(unsigned char*)0x5242
#define USART1_BRR2 *(unsigned char*)0x5243
#define USART1_CR1 *(unsigned char*)0x5244
#define USART1_CR2 *(unsigned char*)0x5245
#define USART1_CR3 *(unsigned char*)0x5246
#define USART1_CR4 *(unsigned char*)0x5247
#define USART1_CR5 *(unsigned char*)0x5248
#define USART1_GTR *(unsigned char*)0x524A
#define USART1_PSCR *(unsigned char*)0x524B

/* USART_CR1 bits */
#define USART_CR1_R8 (1 << 7)
#define USART_CR1_T8 (1 << 6)
#define USART_CR1_UARTD (1 << 5)
#define USART_CR1_M (1 << 4)
#define USART_CR1_WAKE (1 << 3)
#define USART_CR1_PCEN (1 << 2)
#define USART_CR1_PS (1 << 1)
#define USART_CR1_PIEN (1 << 0)

/* USART_CR2 bits */
#define USART_CR2_TIEN (1 << 7)
#define USART_CR2_TCIEN (1 << 6)
#define USART_CR2_RIEN (1 << 5)
#define USART_CR2_ILIEN (1 << 4)
#define USART_CR2_TEN (1 << 3)
#define USART_CR2_REN (1 << 2)
#define USART_CR2_RWU (1 << 1)
#define USART_CR2_SBK (1 << 0)

/* USART_CR3 bits */
#define USART_CR3_LINEN (1 << 6)
#define USART_CR3_STOP2 (1 << 5)
#define USART_CR3_STOP1 (1 << 4)
#define USART_CR3_CLKEN (1 << 3)
#define USART_CR3_CPOL (1 << 2)
#define USART_CR3_CPHA (1 << 1)
#define USART_CR3_LBCL (1 << 0)

/* USART_SR bits */
#define USART_SR_TXE (1 << 7)
#define USART_SR_TC (1 << 6)
#define USART_SR_RXNE (1 << 5)
#define USART_SR_IDLE (1 << 4)
#define USART_SR_OR (1 << 3)
#define USART_SR_NF (1 << 2)
#define USART_SR_FE (1 << 1)
#define USART_SR_PE (1 << 0)


int uart_write(const char *str) {
	char i;
	for(i = 0; i < strlen(str); i++) {
		while(!(USART1_SR & USART_SR_TXE));
		USART1_DR = str[i];
	}
	return(i); // Bytes sent
}

int main() {
	unsigned long i = 0;

	CLK_DIVR = 0x00; // Set the frequency to 16 MHz
	CLK_PCKENR1 = 0xFF; // Enable peripherals

	GPIOD->DDR = 1<<6; // Put TX line on
	GPIOD->CR1 = 1<<6;

	USART1_CR2 = USART_CR2_TEN; // Allow TX & RX
	USART1_CR3 &= ~(USART_CR3_STOP1 | USART_CR3_STOP2); // 1 stop bit
	USART1_BRR2 = 0x00; USART1_BRR1 = 0x0D; // 9600 baud

	do {
		uart_write("sua GPIO!\n\r");
		for(i = 0; i < 14745; i++) { } // Sleep
	} while(1);
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

