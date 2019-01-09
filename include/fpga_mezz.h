#pragma once

/* Register Defination */
#include "fpga_mezz_reg.h"

#define ARD_I2C_0_FUNC 0
#define ARD_SPI_FUNC 1
#define ARD_UART_FUNC 2
#define ARD_I2C_1_FUNC 3

#define I2C_BUS 0

#define INPUT 1
#define OUTPUT 0

#define HIGH 1
#define LOW 0

#define FUNC_PASSTHROUGH 0
#define FUNC_GPIO 1

u_int8_t check_version(mraa_i2c_context i2c);

int test(mraa_i2c_context i2c);

int pinMode(u_int8_t pin, u_int8_t mode, mraa_i2c_context i2c);

int digitalWrite(u_int8_t pin, u_int8_t state, mraa_i2c_context i2c);


int digitalRead(u_int8_t pin, mraa_i2c_context i2c);


int pinFunction(u_int8_t func_type, u_int8_t func, mraa_i2c_context i2c);
