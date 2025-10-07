#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX7219_CS_GPIO_Port GPIOC
#define MAX7219_CS_Pin GPIO_PIN_12

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC

#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

void board_gpio_init(void);
