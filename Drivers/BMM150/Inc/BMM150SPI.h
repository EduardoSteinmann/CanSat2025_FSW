#ifndef _BMM150SPI_H_
#define _BMM150SPI_H_

#include "bmm150.h"

#include "stm32g4xx_hal.h"

bmm150_dev bmm150_spi_init(SPI_HandleTypeDef *spi_handle, GPIO_TypeDef *chip_select_port, uint16_t chip_select_gpio_pin);



#endif