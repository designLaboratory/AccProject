#include "MKL46Z4.h"
#include "I2C.h"

void GPIO_init(PORT_Type *port, uint8_t number, uint8_t mux);


void I2C0_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK			// enable clock	 		
		| SIM_SCGC5_PORTB_MASK
		| SIM_SCGC5_PORTC_MASK
		| SIM_SCGC5_PORTD_MASK
		| SIM_SCGC5_PORTE_MASK;

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	GPIO_init(SCL1);		// init GPIO as I2C pins
	GPIO_init(SDA1);

	I2C0->F = 0x20;		// BAUD RATE == 300[kbps]
	I2C0->C1 |= I2C_C1_IICEN_MASK;		// enable I2C0
}

void I2C1_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK		// enable clock	 					
		| SIM_SCGC5_PORTB_MASK
		| SIM_SCGC5_PORTC_MASK
		| SIM_SCGC5_PORTD_MASK
		| SIM_SCGC5_PORTE_MASK;

	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;

	GPIO_init(SCL1);		// init GPIO as I2C pins
	GPIO_init(SDA1);

	I2C1->F = 0x20;		// BAUD RATE == 300[kbps]
	I2C1->C1 |= I2C_C1_IICEN_MASK;		// enable I2C1
}

void I2C_enable(I2C_Type *I2C_module)
{
	I2C_module->C1 |= I2C_C1_IICEN_MASK;		// enable I2C				
}

void I2C_disable(I2C_Type *I2C_module)
{
	I2C_module->C1 &= ~I2C_C1_IICEN_MASK;		// disable I2C
}

void I2C_mode_TX(I2C_Type *I2C_module)
{
	I2C_module->C1 |= I2C_C1_TX_MASK;		// I2C as transmiter
}

void I2C_mode_RX(I2C_Type *I2C_module)
{
	I2C_module->C1 &= ~I2C_C1_TX_MASK;		// I2C as receiver
}

void I2C_start(I2C_Type *I2C_module)
{
	//I2C1->C1 |= I2C_C1_TX_MASK;		// I2C as transmiter
	I2C_mode_TX(I2C_module);
	I2C1->C1 |= I2C_C1_MST_MASK;		// I2C master, START signal genrator
}

void I2C_stop(I2C_Type *I2C_module)
{
	I2C1->C1 &= ~I2C_C1_MST_MASK;		// I2C slave, STOP signal generator
	//I2C1->C1 &= ~I2C_C1_TX_MASK;		// I2C as receiver
	I2C_mode_RX(I2C_module);
}

void I2C_restart(I2C_Type *I2C_module)
{
	I2C_module->C1 |= I2C_C1_RSTA_MASK;					// I2C generate repeated start signal
}

void I2C_ack(I2C_Type *I2C_module)
{
	I2C_module->C1 &= ~I2C_C1_TXAK_MASK;				// I2C send ACK to slave
}

void I2C_nack(I2C_Type *I2C_module)
{
	I2C_module->C1 |= I2C_C1_TXAK_MASK;					// I2C send NACK to slave
}

uint8_t I2C_check_ACK(I2C_Type *I2C_module)
{
	if (!(I2C_module->S & I2C_S_RXAK_MASK)) return 0;   	// ACK
	else return 1;		// NACK
}

void I2C_send(I2C_Type *I2C_module, uint8_t data)
{
	I2C_module->D = data;												// send one byte to I2C
}

uint8_t I2C_read(I2C_Type *I2C_module)
{
	uint8_t data;													// read one byte from I2C
	data = I2C_module->D;
	return data;
}

void I2C_wait(I2C_Type *I2C_module)
{
	while (!(I2C_module->S & I2C_S_IICIF_MASK)) {}		// wait to the end of transmission
	I2C_module->S |= I2C_S_IICIF_MASK;		// clear flag
}

uint8_t I2C_read_byte(I2C_Type *I2C_module, uint8_t device_address, uint8_t read_register)
{
	uint8_t data;		// temp variable to store data

	I2C_enable(I2C_module);
	I2C_start(I2C_module);

	I2C_send(I2C_module, device_address);
	I2C_wait(I2C_module);
	I2C_check_ACK(I2C_module);

	I2C_send(I2C_module, read_register);
	I2C_wait(I2C_module);
	I2C_check_ACK(I2C_module);

	I2C_restart(I2C_module);
	I2C_send(I2C_module, device_address + 1);
	I2C_wait(I2C_module);
	I2C_check_ACK(I2C_module);

	I2C_mode_RX(I2C_module);
	data = I2C_read(I2C_module);
	I2C_nack(I2C_module);
	I2C_wait(I2C_module);
	data = I2C_read(I2C_module);

	I2C_stop(I2C_module);
	I2C_disable(I2C_module);

	return data;
}


void I2C_write_byte(I2C_Type *I2C_module, uint8_t device_write_address, uint8_t write_register, uint8_t data)
{
	I2C_enable(I2C_module);
	I2C_start(I2C_module);

	I2C_send(I2C_module, device_write_address);
	I2C_wait(I2C_module);
	I2C_check_ACK(I2C_module);

	I2C_send(I2C_module, write_register);
	I2C_wait(I2C_module);
	I2C_check_ACK(I2C_module);

	I2C_send(I2C_module, data);
	I2C_wait(I2C_module);
	I2C_check_ACK(I2C_module);

	I2C_stop(I2C_module);
	I2C_disable(I2C_module);
}

void GPIO_init(PORT_Type *port, uint8_t number, uint8_t mux)
{
	port->PCR[number] |= PORT_PCR_MUX(mux) | PORT_PCR_DSE_MASK;		// init GPIO as I2C pins
}





