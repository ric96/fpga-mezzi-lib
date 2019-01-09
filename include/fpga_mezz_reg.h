#pragma once

// Firmware Virsion 1.0 Specific Registers
#define FPGA_MEZZI_ADDR 0x6f
#define REV_REG 0x00
#define TEST_REG 0x01

// Start Arduino Header Specific Registers
// GPIO Only Pins
#define ARD_IO_CONF_REG 0x10
#define ARD_IO_RD_REG 0x11
#define ARD_IO_WR_REG 0x12

// Multifunction I/O Pins Bank 0
#define ARD_0_FUNC_IO_SEL_REG 0x13
#define ARD_0_FUNC_IO_CONF_REG 0x14
#define ARD_0_FUNC_IO_WR_REG 0x15
#define ARD_0_FUNC_IO_RD_REG 0x16

// Multifunction I/O Pins Bank 1
#define ARD_1_FUNC_IO_SEL_REG 0x17
#define ARD_1_FUNC_IO_CONF_REG 0x18
#define ARD_1_FUNC_IO_WR_REG 0x19
#define ARD_1_FUNC_IO_RD_REG 0x1a
// End Arduino Header Specific Registers

// Start Raspberry Pi Header Specific Registers
// GPIO Only Pins Bank 0
#define RPI_IO_CONF_REG_0 0x30
#define RPI_IO_RD_REG_0 0x32
#define RPI_IO_WR_REG_0 0x34

// GPIO Only Pins Bank 1
#define RPI_IO_CONF_REG_1 0x31
#define RPI_IO_RD_REG_1 0x33
#define RPI_IO_WR_REG_1 0x35

// Multifunction I/O Pins Bank 0
#define RPI_0_FUNC_IO_SEL_REG 0x36
#define RPI_0_FUNC_IO_CONF_REG 0x37
#define RPI_0_FUNC_IO_WR_REG 0x38
#define RPI_0_FUNC_IO_RD_REG 0x39

// Multifunction I/O Pins Bank 1
#define RPI_1_FUNC_IO_SEL_REG 0x3a
#define RPI_1_FUNC_IO_CONF_REG 0x3b
#define RPI_1_FUNC_IO_WR_REG 0x3c
#define RPI_1_FUNC_IO_RD_REG 0x3d
// Start Raspberry Pi Header Specific Registers

// On-Board LEDs and DIP Switches
#define LED_REG 0xa0
#define SWITCH_REG 0xa1
