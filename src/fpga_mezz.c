#include <stdio.h>
#include <stdlib.h>

/* mraa header */
#include "mraa/i2c.h"

#include "fpga_mezz.h"

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

u_int8_t check_version(mraa_i2c_context i2c)
{
    u_int8_t ret;

    ret = mraa_i2c_read_byte_data(i2c, REV_REG);
    if (ret == -1) {
        return EXIT_FAILURE;
    }
    
    return ret;
}

int test(mraa_i2c_context i2c)
{

    u_int8_t ret;
    mraa_result_t status = MRAA_SUCCESS;

    status = mraa_i2c_write_byte_data(i2c, 0x80, TEST_REG);
    if (status != MRAA_SUCCESS) {
        printf("MRAA ERROR\n");
    }

    usleep(100);

    ret = mraa_i2c_read_byte_data(i2c, TEST_REG);
    if (ret == -1) {
        return EXIT_FAILURE;
    }

    if(ret == 0x80)
    {
        return 0;
    }
    else
        return 1;
}

int pinMode(u_int8_t pin, u_int8_t mode, mraa_i2c_context i2c)
{
    u_int8_t ret;
    mraa_result_t status = MRAA_SUCCESS;
    
    if(pin >= 2 && pin <= 9)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_IO_CONF_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        if(mode == 0)
        {
            switch(pin)
            {
                case 2: ret &= ~(1UL << 5);
                        break;
                case 3: ret &= ~(1UL << 4);
                        break;
                case 4: ret &= ~(1UL << 3);
                        break;
                case 5: ret &= ~(1UL << 2);
                        break;
                case 6: ret &= ~(1UL << 1);
                        break;
                case 7: ret &= ~(1UL << 0);
                        break;
                case 8: ret &= ~(1UL << 7);
                        break;
                case 9: ret &= ~(1UL << 6);
                        break;
           }
        }
        else if(mode == 1)
        {
            switch(pin)
            {
                case 2: ret |= 1UL << 5;
                        break;
                case 3: ret |= 1UL << 4;
                        break;
                case 4: ret |= 1UL << 3;
                        break;
                case 5: ret |= 1UL << 2;
                        break;
                case 6: ret |= 1UL << 1;
                        break;
                case 7: ret |= 1UL << 0;
                        break;
                case 8: ret |= 1UL << 7;
                        break;
                case 9: ret |= 1UL << 6;
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret, ARD_IO_CONF_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

    else if((pin >= 10 && pin <= 15) || pin == 0 || pin == 1)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_0_FUNC_IO_CONF_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        if(mode == 0)
        {
            switch(pin)
            {
                case 10: ret &= ~(1UL << 5);
                        break;
                case 11: ret &= ~(1UL << 4);
                        break;
                case 12: ret &= ~(1UL << 3);
                        break;
                case 13: ret &= ~(1UL << 2);
                        break;
                case 1: ret &= ~(1UL << 1);
                        break;
                case 0: ret &= ~(1UL << 0);
                        break;
                case 15: ret &= ~(1UL << 7);
                        break;
                case 14: ret &= ~(1UL << 6);
                        break;
           }
        }
        else if(mode == 1)
        {
            switch(pin)
            {
                case 10: ret |= 1UL << 5;
                        break;
                case 11: ret |= 1UL << 4;
                        break;
                case 12: ret |= 1UL << 3;
                        break;
                case 13: ret |= 1UL << 2;
                        break;
                case 1: ret |= 1UL << 1;
                        break;
                case 0: ret |= 1UL << 0;
                        break;
                case 15: ret |= 1UL << 7;
                        break;
                case 14: ret |= 1UL << 6;
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret, ARD_0_FUNC_IO_CONF_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

    else if(pin == 16 || pin == 17)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_1_FUNC_IO_CONF_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        if(mode == 0)
        {
            switch(pin)
            {
                case 16: ret &= ~(1UL << 1);
                        break;
                case 17: ret &= ~(1UL << 0);
                        break;
           }
        }
        else if(mode == 1)
        {
            switch(pin)
            {
                case 16: ret |= 1UL << 1;
                        break;
                case 17: ret |= 1UL << 0;
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret, ARD_IO_CONF_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }
            
    else
        return 1;
}

int digitalWrite(u_int8_t pin, u_int8_t state, mraa_i2c_context i2c)
{
    u_int8_t ret_conf, ret_status;
    mraa_result_t status = MRAA_SUCCESS;
    
    if(pin >= 2 && pin <= 9)
    {
        ret_conf = mraa_i2c_read_byte_data(i2c, ARD_IO_CONF_REG);
        if (ret_conf == -1) {
            return EXIT_FAILURE;
        }

        ret_status = mraa_i2c_read_byte_data(i2c, ARD_IO_WR_REG);
        if (ret_status == -1) {
            return EXIT_FAILURE;
        }

        if(state == 0)
        {
            switch(pin)
            {
                case 2: ret_status &= ~(1UL << 5);
                        break;
                case 3: ret_status &= ~(1UL << 4);
                        break;
                case 4: ret_status &= ~(1UL << 3);
                        break;
                case 5: ret_status &= ~(1UL << 2);
                        break;
                case 6: ret_status &= ~(1UL << 1);
                        break;
                case 7: ret_status &= ~(1UL << 0);
                        break;
                case 8: ret_status &= ~(1UL << 7);
                        break;
                case 9: ret_status &= ~(1UL << 6);
                        break;
           }
        }
        else if(state == 1)
        {
            switch(pin)
            {
                case 2: if(((ret_conf >> 5) & 1U) == 0)
                            ret_status |= 1UL << 5;
                        else {
                            printf("Pin 2 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 3: if(((ret_conf >> 4) & 1U) == 0)
                            ret_status |= 1UL << 4;
                        else {
                            printf("Pin 3 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 4: if(((ret_conf >> 3) & 1U) == 0)
                            ret_status |= 1UL << 3;
                        else {
                            printf("Pin 4 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 5: if(((ret_conf >> 2) & 1U) == 0)
                            ret_status |= 1UL << 2;
                        else {
                            printf("Pin 5 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 6: if(((ret_conf >> 1) & 1U) == 0)
                            ret_status |= 1UL << 1;
                        else {
                            printf("Pin 6 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 7: if(((ret_conf >> 0) & 1U) == 0)
                            ret_status |= 1UL << 0;
                        else {
                            printf("Pin 7 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 8: if(((ret_conf >> 7) & 1U) == 0)
                            ret_status |= 1UL << 7;
                        else {
                            printf("Pin 8 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 9: if(((ret_conf >> 6) & 1U) == 0)
                            ret_status |= 1UL << 6;
                        else {
                            printf("Pin 9 not set as output :( \n");
                            return 1;
                        } 
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret_status, ARD_IO_WR_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

    else if((pin >= 10 && pin <= 15) || pin == 0 || pin == 1)
    {
        ret_conf = mraa_i2c_read_byte_data(i2c, ARD_0_FUNC_IO_CONF_REG);
        if (ret_conf == -1) {
            return EXIT_FAILURE;
        }

        ret_status = mraa_i2c_read_byte_data(i2c, ARD_0_FUNC_IO_WR_REG);
        if (ret_status == -1) {
            return EXIT_FAILURE;
        }

        if(state == 0)
        {
            switch(pin)
            {
                case 10: ret_status &= ~(1UL << 5);
                        break;
                case 11: ret_status &= ~(1UL << 4);
                        break;
                case 12: ret_status &= ~(1UL << 3);
                        break;
                case 13: ret_status &= ~(1UL << 2);
                        break;
                case 1: ret_status &= ~(1UL << 1);
                        break;
                case 0: ret_status &= ~(1UL << 0);
                        break;
                case 15: ret_status &= ~(1UL << 7);
                        break;
                case 14: ret_status &= ~(1UL << 6);
                        break;
           }
        }
        else if(state == 1)
        {
            switch(pin)
            {
                case 10: if(((ret_conf >> 5) & 1U) == 0)
                            ret_status |= 1UL << 5;
                        else {
                            printf("Pin 10 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 11: if(((ret_conf >> 4) & 1U) == 0)
                            ret_status |= 1UL << 4;
                        else {
                            printf("Pin 11 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 12: if(((ret_conf >> 3) & 1U) == 0)
                            ret_status |= 1UL << 3;
                        else {
                            printf("Pin 12 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 13: if(((ret_conf >> 2) & 1U) == 0)
                            ret_status |= 1UL << 2;
                        else {
                            printf("Pin 13 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 1: if(((ret_conf >> 1) & 1U) == 0)
                            ret_status |= 1UL << 1;
                        else {
                            printf("Pin 1 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 0: if(((ret_conf >> 0) & 1U) == 0)
                            ret_status |= 1UL << 0;
                        else {
                            printf("Pin 0 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 15: if(((ret_conf >> 7) & 1U) == 0)
                            ret_status |= 1UL << 7;
                        else {
                            printf("Pin 15 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 14: if(((ret_conf >> 6) & 1U) == 0)
                            ret_status |= 1UL << 6;
                        else {
                            printf("Pin 14 not set as output :( \n");
                            return 1;
                        } 
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret_status, ARD_0_FUNC_IO_WR_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

    else if(pin == 16 || pin == 17)
    {
        ret_conf = mraa_i2c_read_byte_data(i2c, ARD_1_FUNC_IO_CONF_REG);
        if (ret_conf == -1) {
            return EXIT_FAILURE;
        }

        ret_status = mraa_i2c_read_byte_data(i2c, ARD_1_FUNC_IO_WR_REG);
        if (ret_status == -1) {
            return EXIT_FAILURE;
        }

        if(state == 0)
        {
            switch(pin)
            {
                case 16: ret_status &= ~(1UL << 1);
                        break;
                case 17: ret_status &= ~(1UL << 0);
                        break;
           }
        }
        else if(state == 1)
        {
            switch(pin)
            {
                case 16: if(((ret_conf >> 1) & 1U) == 0)
                            ret_status |= 1UL << 1;
                        else {
                            printf("Pin 16 not set as output :( \n");
                            return 1;
                        } 
                        break;
                case 17: if(((ret_conf >> 0) & 1U) == 0)
                            ret_status |= 1UL << 0;
                        else {
                            printf("Pin 17 not set as output :( \n");
                            return 1;
                        } 
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret_status, ARD_1_FUNC_IO_WR_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

    else
        return 1;
}


int digitalRead(u_int8_t pin, mraa_i2c_context i2c)
{
    u_int8_t ret;
    mraa_result_t status = MRAA_SUCCESS;
    
    if(pin >= 2 && pin <= 9)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_IO_RD_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        switch(pin)
        {
            case 2: if(((ret >> 5) & 1U) == 0)
                        return 0;
                    else if(((ret >> 5) & 1U) == 1)
                            return 1;
                    break;
            case 3: if(((ret >> 4) & 1U) == 0)
                        return 0;
                    else if(((ret >> 4) & 1U) == 1)
                            return 1;
                    break;
            case 4: if(((ret >> 3) & 1U) == 0)
                        return 0;
                    else if(((ret >> 3) & 1U) == 1)
                            return 1;
                    break;
            case 5: if(((ret >> 2) & 1U) == 0)
                        return 0;
                    else if(((ret >> 2) & 1U) == 1)
                            return 1;
                    break;
            case 6: if(((ret >> 1) & 1U) == 0)
                        return 0;
                    else if(((ret >> 1) & 1U) == 1)
                        return 1;
                    break;
            case 7: if(((ret >> 0) & 1U) == 0)
                        return 0;
                    else if(((ret >> 0) & 1U) == 1)
                        return 1;
                    break;
            case 8: if(((ret >> 7) & 1U) == 0)
                        return 0;
                    else if(((ret >> 7) & 1U) == 1)
                        return 1;
                    break;
            case 9: if(((ret >> 6) & 1U) == 0)
                        return 0;
                    else if(((ret >> 6) & 1U) == 1)
                        return 1;
                    break;
                        break;
        }

    }

    else if((pin >= 10 && pin <= 15) || (pin == 0 || pin == 1))
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_0_FUNC_IO_RD_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        switch(pin)
        {
            case 10: if(((ret >> 5) & 1U) == 0)
                        return 0;
                    else if(((ret >> 5) & 1U) == 1)
                            return 1;
                    break;
            case 11: if(((ret >> 4) & 1U) == 0)
                        return 0;
                    else if(((ret >> 4) & 1U) == 1)
                            return 1;
                    break;
            case 12: if(((ret >> 3) & 1U) == 0)
                        return 0;
                    else if(((ret >> 3) & 1U) == 1)
                            return 1;
                    break;
            case 13: if(((ret >> 2) & 1U) == 0)
                        return 0;
                    else if(((ret >> 2) & 1U) == 1)
                            return 1;
                    break;
            case 1: if(((ret >> 1) & 1U) == 0)
                        return 0;
                    else if(((ret >> 1) & 1U) == 1)
                            return 1;
                    break;
            case 0: if(((ret >> 0) & 1U) == 0)
                        return 0;
                    else if(((ret >> 0) & 1U) == 1)
                            return 1;
                    break;
            case 15: if(((ret >> 7) & 1U) == 0)
                        return 0;
                    else if(((ret >> 7) & 1U) == 1)
                            return 1;
                    break;
            case 14: if(((ret >> 6) & 1U) == 0)
                        return 0;
                    else if(((ret >> 6) & 1U) == 1)
                            return 1;
                    break;
        }
    }

    else if(pin == 16 || pin == 17)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_1_FUNC_IO_RD_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        switch(pin)
        {
            case 16: if(((ret >> 1) & 1U) == 0)
                        return 0;
                    else if(((ret >> 1) & 1U) == 1)
                        return 1;
                    break;
            case 17: if(((ret >> 0) & 1U) == 0)
                        return 0;
                    else if(((ret >> 0) & 1U) == 1)
                        return 1;
                    break;
        }
    }

    else
        return 100;
}


int pinFunction(u_int8_t func_type, u_int8_t func, mraa_i2c_context i2c)
{
    u_int8_t ret;
    mraa_result_t status = MRAA_SUCCESS;

    if(func_type >= 0 && func_type <= 2)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_0_FUNC_IO_SEL_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        if(func == 0)
        {
            switch(func_type)
            {
                case 0: ret &= ~(1UL << 7);
                        ret &= ~(1UL << 6);
                        break;
                case 1: ret &= ~(1UL << 5);
                        ret &= ~(1UL << 4);
                        ret &= ~(1UL << 3);
                        ret &= ~(1UL << 2);
                        break;
                case 2: ret &= ~(1UL << 0);
                        ret &= ~(1UL << 1);
                        break;
            }
        }
        if(func == 1)
        {
            switch(func_type)
            {
                case 0: ret |= 1UL << 7;
                        ret |= 1UL << 6;
                        break;
                case 1: ret |= 1UL << 5;
                        ret |= 1UL << 4;
                        ret |= 1UL << 3;
                        ret |= 1UL << 2;
                        break;
                case 2: ret |= 1UL << 0;
                        ret |= 1UL << 1;
                        break;
            }
        }

        status = mraa_i2c_write_byte_data(i2c, ret, ARD_0_FUNC_IO_SEL_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

    else if(func_type == 3)
    {
        ret = mraa_i2c_read_byte_data(i2c, ARD_1_FUNC_IO_SEL_REG);
        if (ret == -1) {
            return EXIT_FAILURE;
        }

        if(func == 0)
        {
            ret &= ~(1UL << 0);
            ret &= ~(1UL << 1);
        }
        else if(func == 1)
        {
            ret |= 1UL << 0;
            ret |= 1UL << 1;
        }

        status = mraa_i2c_write_byte_data(i2c, ret, ARD_1_FUNC_IO_SEL_REG);
        if (status != MRAA_SUCCESS) {
          printf("MRAA ERROR\n");
         }
    }

}
