#include "max7219_port_stm32.h"
#include "boardConfig.h"

// estas funciones controlan el CS
static void MAX7219_Select(void)   { HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET); }
static void MAX7219_Deselect(void) { HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET); }

// MAX7219_WriteRowAll envia la informacio de una fila (row, de 1 a 8) a los 4 MAX7219. El primer frame que se envia termina en el ultumo max
void MAX7219_WriteRowAll(uint8_t row, uint8_t TR, uint8_t TL, uint8_t BL, uint8_t BR)
{
    uint8_t frame[8] = {
        row, BR,   // Display 4 (mas lejos del micro)
        row, BL,   // Display 3
        row, TL,   // Display 2
        row, TR    // Display 1 (mas cercano al micro)
    };

    MAX7219_Select();
    HAL_SPI_Transmit(&hspi2, frame, sizeof(frame), HAL_MAX_DELAY);
    MAX7219_Deselect(); // fija "latchea" la informacion en los displays
}

// cada max7219 recibe 2 frames. El primer frame es la direccion del registro que se quiere modificar. Por ejemplo el registro 0000 0001 controla la primer fila.
// el segundo frame contiene la informacion. Por ejemplo si enviamos al resgistro anterior 1111 1111 encendemos toda la fila.



