#ifndef _I2C_H_
#define _I2C_H_

#include <MKL46Z4.h>


#define SCL0 PORTE,24,5		// I2C0 pin port, pin number, multiplexer value
#define SDA0 PORTE,25,5		// I2C0 pin port, pin number, multiplexer value

#define SCL1 PORTE,1,6		// I2C1 pin port, pin number, multiplexer value
#define SDA1 PORTE,0,6		// I2C1 pin port, pin number, multiplexer value



void I2C0_init(void);		// init of I2C0
void I2C1_init(void);		// init of I2C1

void I2C_enable(I2C_Type *I2C_module);		// enable I2C module
void I2C_disable(I2C_Type *I2C_module);		// disable I2C module
void I2C_mode_TX(I2C_Type *I2C_module);		// mode: transmiter
void I2C_mode_RX(I2C_Type *I2C_module);		// mode: reciver

void I2C_start(I2C_Type *I2C_module);		// send start signal
void I2C_stop(I2C_Type *I2C_module);		// send stop signal
void I2C_restart(I2C_Type *I2C_module);		// send restart signal
void I2C_ack(I2C_Type *I2C_module);		// send ACK signal
void I2C_nack(I2C_Type *I2C_module);		// send NACK signal
uint8_t I2C_check_ACK(I2C_Type *I2C_module);		// check slave answer

void I2C_send(I2C_Type *I2C_module, uint8_t data);		// send byte
uint8_t I2C_read(I2C_Type *I2C_module);		// read byte
void I2C_wait(I2C_Type *I2C_module);		// wait for end of transmission

uint8_t I2C_read_byte(I2C_Type *I2C_module, uint8_t device_address, uint8_t read_register);		// reads one byte form slave devices
void I2C_write_byte(I2C_Type *I2C_module, uint8_t device_write_address, uint8_t write_register, uint8_t data);		// writes one byte to the pointed register 


#endif 

