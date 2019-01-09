#include <stdio.h>
#include <stdlib.h>

/* mraa header */
#include "mraa/i2c.h"

#include "fpga_mezz.h"

int main()
{
    mraa_result_t status = MRAA_SUCCESS;
    mraa_i2c_context i2c;

    mraa_init();
    i2c = mraa_i2c_init(I2C_BUS);

    int input;

    if (i2c == NULL) {
        fprintf(stderr, "Failed to initialize I2C\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }

    /* set slave address */
    status = mraa_i2c_address(i2c, FPGA_MEZZI_ADDR);
    if (status != MRAA_SUCCESS) {
    }

    u_int8_t ver;
    ver = check_version(i2c);
    printf("Version %hhu\n",&ver);

    if(test(i2c)==0)
        printf("Test Passed\n");
    
    pinMode(7,OUTPUT,i2c);
    pinMode(6,OUTPUT,i2c);
    pinMode(5,OUTPUT,i2c);
    pinMode(4,OUTPUT,i2c);

    pinFunction(ARD_I2C_0_FUNC,FUNC_PASSTHROUGH,i2c);
    pinFunction(ARD_SPI_FUNC,FUNC_GPIO,i2c);
    pinMode(13,INPUT,i2c);

    digitalWrite(7,HIGH,i2c);
    digitalWrite(4,HIGH,i2c);

    while(1)
    {
        input = digitalRead(13,i2c);
        if(input == LOW)
        {
            digitalWrite(6,HIGH,i2c);
            digitalWrite(5,LOW,i2c);
        }
        else if(input == HIGH)
        {
            digitalWrite(6,LOW,i2c);
            digitalWrite(5,HIGH,i2c);
        }
        printf("%d\n",input);
        usleep(100);
    }
}