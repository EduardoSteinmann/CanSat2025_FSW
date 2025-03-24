#include "BMM150SPI.h"
#include "stm32g4xx_hal.h"

#define BMM150_TIMEOUT_DURATION 10

static SPI_HandleTypeDef* spi_handle;

BMM150_INTF_RET_TYPE bmm150_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
	HAL_StatusTypeDef status = HAL_SPI_Receive(spi_handle, reg_data, length, BMM150_TIMEOUT_DURATION);

	return (BMM150_INTF_RET_TYPE)status;
}

BMM150_dev BMM150_spi_init(SPI_HandleTypeDef *spi_handle)
{
	BMM150_dev device = (BMM150_dev){ 0 };

	if (spi_handle == NULL)
	{
		device.ok = false;
		return device;
	}

	device.device = (struct bmm150_dev) {

	};
}
