#include "ICM42688PSPI.h"
#include "stm32g4xx_hal.h"

// #define ICM42688P_SPI &hspi1  // Change to match your SPI handle
// #define ICM42688P_CS_LOW() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
// #define ICM42688P_CS_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

static void icm42688p_write_reg(uint8_t reg, uint8_t data)
{
    uint8_t tx[2] = {reg, data};
    ICM42688P_CS_LOW();
    HAL_SPI_Transmit(ICM42688P_SPI, tx, 2, HAL_MAX_DELAY);
    ICM42688P_CS_HIGH();
}

static uint8_t icm42688p_read_reg(uint8_t reg)
{
    uint8_t tx = reg | 0x80;
    uint8_t rx = 0;
    ICM42688P_CS_LOW();
    HAL_SPI_Transmit(ICM42688P_SPI, &tx, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(ICM42688P_SPI, &rx, 1, HAL_MAX_DELAY);
    ICM42688P_CS_HIGH();
    return rx;
}

// Another init where device and pins can be set from input
//(SPI_HandleTypeDef *spi_handle, GPIO_TypeDef* cs_port, uint16_t cs_gpio_pin)
void icm42688p_init()
{
    osDelay(10);
    icm42688p_write_reg(0x4F, 0x04);  // Reset device
    osDelay(10);
    icm42688p_write_reg(0x11, 0x00);  // Power management
    icm42688p_write_reg(0x10, 0x0F);  // Gyro and accel config
}

void icm42688p_read_data(int16_t *accel, int16_t *gyro)
{
    uint8_t buffer[12];
    ICM42688P_CS_LOW();
    //This register should be correct
    uint8_t reg = 0x1F | 0x80;
    HAL_SPI_Transmit(ICM42688P_SPI, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(ICM42688P_SPI, buffer, 12, HAL_MAX_DELAY);
    ICM42688P_CS_HIGH();

    accel[0] = (buffer[0] << 8) | buffer[1];
    accel[1] = (buffer[2] << 8) | buffer[3];
    accel[2] = (buffer[4] << 8) | buffer[5];
    gyro[0] = (buffer[6] << 8) | buffer[7];
    gyro[1] = (buffer[8] << 8) | buffer[9];
    gyro[2] = (buffer[10] << 8) | buffer[11];
}

#endif
