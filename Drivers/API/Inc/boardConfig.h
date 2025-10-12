#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX7219_CS_GPIO_Port GPIOC
#define MAX7219_CS_Pin GPIO_PIN_12

extern SPI_HandleTypeDef hspi2;
extern I2C_HandleTypeDef hi2c1;

void board_gpio_init(void);
void SPI2_Init(void);
void I2C1_Init(void);
void Error_Handler(void);
