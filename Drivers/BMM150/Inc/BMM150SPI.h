#ifndef _BMM150SPI_H_
#define _BMM150SPI_H_

#include "bmm150.h"

#include "stm32g4xx_hal.h"

typedef struct BMM150_dev
{
	bool ok;
	struct bmm150_dev device;
} BMM150_dev;

typedef struct BMM150_mag_data
{
	int8_t error;
	struct bmm150_mag_data data;
} BMM150_mag_data;

/**
   * @brief  Initializes MS5607 Sensor
   * @param  SPI Handle address
   * @param  GPIO Port Definition
   * @param  GPIO Pin
   * @retval Initialization status:
   *           - 0: Was not abe to communicate with sensor
   *           - 1: MS5607_STATE_READY: Sensor initialized OK and ready to use
   */
BMM150_dev BMM150_spi_init(SPI_HandleTypeDef *spi_handle);

BMM150_mag_data BMM150_read_mag_data(BMM150_dev* const device);

#endif
