#include "stdint.h"
#include "stm32f4xx_hal.h"

#define AT24C256_ADDR 0x50 // 7-bit address
#define SCORE_ADDR    0x0000 // direccion donde se guarda la puntuacion

extern I2C_HandleTypeDef hi2c1;

//void EEPROM_Init(I2C_HandleTypeDef *hi2c1);
void EEPROM_Write(uint16_t score);
uint16_t EEPROM_Read(void);
