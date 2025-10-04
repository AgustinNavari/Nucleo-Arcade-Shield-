#include "max7219_port_stm32.h"
#include "boardConfig.h"

static void MAX7219_Select(void)   { HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET); }
static void MAX7219_Deselect(void) { HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET); }

void MAX7219_WriteRowAll(uint8_t row, uint8_t TR, uint8_t TL, uint8_t BL, uint8_t BR)
{
    // Recordá: el primer par de bytes que mandamos termina en el módulo más LEJANO (BL)
    uint8_t frame[8] = {
        row, BR,   // Display 4 (más lejano)
        row, BL,   // Display 3
        row, TL,   // Display 2
        row, TR    // Display 1 (más cercano al micro)
    };

    MAX7219_Select();
    HAL_SPI_Transmit(&hspi2, frame, sizeof(frame), HAL_MAX_DELAY);
    MAX7219_Deselect();
}





