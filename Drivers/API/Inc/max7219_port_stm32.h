#include "stdint.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi2;

void MAX7219_WriteRowAll(uint8_t row, uint8_t TR, uint8_t TL, uint8_t BL, uint8_t BR);
void updateDisplay16(void);
