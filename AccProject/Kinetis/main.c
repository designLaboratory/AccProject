#include "MKL46Z4.h"
#include "I2C.h"
#include "UART.h"
#include "MPU6050.h"


#define GREEN_LED 5
#define GREEN_LED_MASK (1<<GREEN_LED)

#define RED_LED 29
#define RED_LED_MASK (1<<RED_LED)

void GPIO(void); // LED initialization
void CRLF(void) { UART_send(UART2, "\r\n"); }

int main(void)
{
	SystemCoreClockUpdate();		// SysTick init
	SysTick_Config(SystemCoreClock / 10);		// freq = 10hz

	UART2_init(115200); // UART module init

	GPIO();		// LED init

	if (MPU6050_init())		// check MPU init
	{
		PTE->PDOR &= ~(RED_LED_MASK);
	}

	while (1)
	{
		// do nothing
	}
}

void GPIO(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[RED_LED] |= PORT_PCR_MUX(1);
	PTE->PDDR |= (RED_LED_MASK);
	PTE->PDOR |= (RED_LED_MASK);
	PORTD->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	PTD->PDDR |= (GREEN_LED_MASK);
	PTD->PDOR |= (GREEN_LED_MASK);
}

void SysTick_Handler(void)
{
	int16_t raw_data[3];		// temp array to store MPU data

	MPU6050_get_raw_accel_data(raw_data); // reading accel measurments

	UART_send(UART2, "X");
	UART_send_int(UART2, raw_data[0]);  //x
	//UART_send(UART2, "XDATA");
	CRLF(); //enter 
	UART_send(UART2, "Y");
	//UART_send(UART2, "YDATA");
	UART_send_int(UART2, raw_data[1]);
	CRLF();  //y
	UART_send(UART2, "Z");
	//UART_send(UART2, "ZDATA");
	UART_send_int(UART2, raw_data[2]);
	CRLF();  //z
//			UART_send(UART2, "X");
//			UART_send(UART2, "Z");
//			UART_send(UART2, "C");
//			UART_send(UART2, "D");
}

