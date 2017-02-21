#ifndef UART_H_
#define UART_H_

#include "MKL46Z4.h" 

#define UART1_TX PORTE,0,3		// UART port,pin number,multiplexer value
#define UART1_RX PORTE,1,3		// UART port,pin number,multiplexer value

#define UART2_TX PORTE,16,3		// UART port,pin number,multiplexer value
#define UART2_RX PORTE,17,3		// UART port,pin number,multiplexer value

#define TX_BUFOR_SIZE 128
#define RX_BUFOR_SIZE 128




void UART1_init(uint32_t BAUD_RATE);
void UART2_init(uint32_t BAUD_RATE);

void UART_send(UART_Type *UART_module,char *string);
void UART_send_int(UART_Type *UART_module, int count);



#endif

