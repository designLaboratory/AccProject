#include "MKL46Z4.h"
#include "string.h"
#include "UART.h"


void UART_GPIO_init(PORT_Type *port,uint8_t number,uint8_t mux);
void int2string(int n, char s[]);

#define BUS_CLOCK 24000000u

#define UART1_ENABLE_TX 	UART1->C2 |= UART_C2_TE_MASK;			
#define UART1_DISABLE_TX 	UART1->C2 &= ~UART_C2_TE_MASK;		
#define UART1_ENABLE_RX 	UART1->C2 |= UART_C2_RE_MASK;			
#define UART1_DISABLE_RX 	UART1->C2 &= ~UART_C2_RE_MASK;

#define UART2_ENABLE_TX 	UART2->C2 |= UART_C2_TE_MASK;			
#define UART2_DISABLE_TX 	UART2->C2 &= ~UART_C2_TE_MASK;		
#define UART2_ENABLE_RX 	UART2->C2 |= UART_C2_RE_MASK;			
#define UART2_DISABLE_RX 	UART2->C2 &= ~UART_C2_RE_MASK;

volatile char UART1_TX_bufor[TX_BUFOR_SIZE];
volatile char UART1_RX_bufor[RX_BUFOR_SIZE];
volatile uint8_t UART1_head;
volatile uint8_t UART1_tail;
volatile uint8_t UART1_receive_flag;

volatile char UART2_TX_bufor[TX_BUFOR_SIZE];  // in use 
volatile char UART2_RX_bufor[RX_BUFOR_SIZE];
volatile uint8_t UART2_head;
volatile uint8_t UART2_tail;
volatile uint8_t UART2_receive_flag;



void UART1_init(uint32_t BAUD_RATE)
{
	uint16_t sbr=0;		// temp to store SBR value
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK		// clock enable
						 |  SIM_SCGC5_PORTB_MASK
						 |  SIM_SCGC5_PORTC_MASK
						 |  SIM_SCGC5_PORTD_MASK
						 |  SIM_SCGC5_PORTE_MASK;
	
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;						
	
	UART_GPIO_init(UART1_TX);		//init GPIO as UART pin
	UART_GPIO_init(UART1_RX);		//init GPIO as UART pin
	
	sbr = (BUS_CLOCK)/(16*BAUD_RATE);
	
	UART1->BDH |= UART_BDH_SBR(sbr>>8);		// writing to higher register 
	UART1->BDL = UART_BDL_SBR(sbr);		// writing to lower register

	UART1->C2 |= UART_C2_TIE_MASK;		// enabling TX interrupt									
	UART1->C2 |= UART_C2_RIE_MASK;		// enabling RX interrupt
	UART1_ENABLE_TX;		// enabling TX
	UART1->C2 |= UART_C2_RE_MASK;		// enabling RX
	
	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn,3);
	NVIC_EnableIRQ(UART1_IRQn);
}

void UART2_init(uint32_t BAUD_RATE)
{
	uint16_t sbr=0;		// temp to store SBR value
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK		// clock enable
						 |  SIM_SCGC5_PORTB_MASK
						 |  SIM_SCGC5_PORTC_MASK
						 |  SIM_SCGC5_PORTD_MASK
						 |  SIM_SCGC5_PORTE_MASK;
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;						
	
	UART_GPIO_init(UART2_TX);		//init GPIO as UART pin
	UART_GPIO_init(UART2_RX);		//init GPIO as UART pin
	
	sbr = (BUS_CLOCK)/(16*BAUD_RATE);
	
	UART2->BDH |= UART_BDH_SBR(sbr>>8);		// writing to higher register 
	UART2->BDL = UART_BDL_SBR(sbr);		// writing to lower register

	UART2->C2 |= UART_C2_TIE_MASK;		// enabling TX interrupt									
	UART2->C2 |= UART_C2_RIE_MASK;		// enabling RX interrupt
	UART2_ENABLE_TX;		// enabling RX
	UART2->C2 |= UART_C2_RE_MASK;			// enabling RX
	
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_SetPriority(UART2_IRQn,3);
	NVIC_EnableIRQ(UART2_IRQn);
}

void UART_send(UART_Type *UART_module,char *string)
{
	while( *string ) 	// copy data to right TX bufor
	{
		if(UART_module == UART1) { UART1_TX_bufor[UART1_tail++]=*string; string++;}
		if(UART_module == UART2) { UART2_TX_bufor[UART2_tail++]=*string; string++;}	
	}
	if(UART_module == UART1) 	// if TX bufor is empty -> start transmission

	{
		if( UART1_head == 0 ) {UART1_ENABLE_TX; UART_module->D = UART1_TX_bufor[UART1_head++];}
	}
	if(UART_module == UART2) 
	{
		if( UART2_head == 0 ) {UART2_ENABLE_TX; UART_module->D = UART2_TX_bufor[UART2_head++];}
	}
}


void UART_send_int(UART_Type *UART_module, int count)
{
	char bufor[11];
	int2string(count,bufor);
	UART_send(UART_module,bufor);
}
	
	
void UART_GPIO_init(PORT_Type *port,uint8_t number,uint8_t mux)
{
	port->PCR[number] |= PORT_PCR_MUX(mux);
}

void int2string(int n, char s[]) 
{ 
   char i,c,j; 
   int sign; 
   if ((sign = n) < 0) n = -n; 
   i = 0; 
   do { 
      s[i++] = n % 10 + '0'; 
   } while ((n /= 10) > 0); 
   if (sign < 0) 
      s[i++] = '-'; 
   s[i] = 0; 
   for (i = 0, j = strlen(s)-1; i < j; i++, j--) { 
      c = s[i]; 
      s[i] = s[j]; 
      s[j] = c; 
   } 
} 




void UART1_IRQHandler(void)
{
	if( UART1->S1 & UART_S1_TDRE_MASK)			// empty bufor interrupt
	{
		if( !UART1_tail ) {UART1_DISABLE_TX;}		// all data has been send, TX bufor empty
		if( UART1_head < UART1_tail-1) {	UART1->D = UART1_TX_bufor[UART1_head++]; }		// send next byte from TX bufor
			else {		// send last byte
						UART1->D = UART1_TX_bufor[UART1_head];
						UART1_head=0;								// bufor is empty, clear pointers
						UART1_tail=0;
					 }				
	}
}
	

void UART2_IRQHandler(void)
{
	if( UART2->S1 & UART_S1_TDRE_MASK)			// empty bufor interrupt
	{
		if( !UART2_tail ) {UART2_DISABLE_TX;}		// all data has been send, TX bufor empty
		if( UART2_head < UART2_tail-1) {	UART2->D = UART2_TX_bufor[UART2_head++]; }		// send next byte from TX bufor
			else {		// send last byte
						UART2->D = UART2_TX_bufor[UART2_head];
						UART2_head=0;		// bufor is empty, clear pointers		
						UART2_tail=0;
					 }				
	}
	
}
