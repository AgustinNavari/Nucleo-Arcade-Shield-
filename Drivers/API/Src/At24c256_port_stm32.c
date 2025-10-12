#include "At24c256_port_stm32.h"
#include "boardConfig.h"

extern I2C_HandleTypeDef hi2c1;

// EEPROM_Write escribe al modulo At24c256
void EEPROM_Write(uint16_t num) {
    uint8_t data[2];
    data[0] = (uint8_t)(num >> 8);   // byte alto
    data[1] = (uint8_t)(num & 0xFF); // byte bajo

    uint8_t addr[2];
    addr[0] = (uint8_t)(SCORE_ADDR >> 8);
    addr[1] = (uint8_t)(SCORE_ADDR & 0xFF);

    uint8_t tx[4] = {addr[0], addr[1], data[0], data[1]};

    HAL_I2C_Master_Transmit(&hi2c1, AT24C256_ADDR << 1, tx, 4, HAL_MAX_DELAY);

    // Esperar hasta que termine de escribir
    while (HAL_I2C_IsDeviceReady(&hi2c1, AT24C256_ADDR << 1, 1, 100) != HAL_OK);
}

//EEPROM_Read lee del modulo At24c256
uint16_t EEPROM_Read(void) {
    uint8_t addr[2];
    uint8_t data[2];
    addr[0] = (uint8_t)(SCORE_ADDR >> 8);
    addr[1] = (uint8_t)(SCORE_ADDR & 0xFF);

    HAL_I2C_Master_Transmit(&hi2c1, AT24C256_ADDR << 1, addr, 2, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, AT24C256_ADDR << 1, data, 2, HAL_MAX_DELAY);

    return ((uint16_t)data[0] << 8) | data[1];
}
