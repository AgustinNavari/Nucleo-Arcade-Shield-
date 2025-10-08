#include "game.h"
#include "max7219.h"
#include "max7219_port_stm32.h"
#include "boardConfig.h"
#include "snake.h"


ArcadeState_t arcadeState = BOOT;



void arcadeFSM(void)
{
    switch (arcadeState){

        case BOOT:

		systemInit();
		startScreen();
		snakeInit();
		arcadeState = PLAYING;

            break;

        case MENU:

            break;

        case PLAYING:
        	snakeUpdate();
            break;

        case PAUSED:

            break;

        case GAME_OVER:
        	fill16(1);
        	updateDisplay16();
        	HAL_Delay(1000);
        	arcadeState = BOOT;

            break;

        case HSCORE:

            break;

        default:
            arcadeState = BOOT;
            break;
    }
}

void systemInit(void)
{
    // Inicializa el hardware necesario
	board_gpio_init();
	MAX7219_InitAll();
}

void startScreen(void){

    for(uint8_t k = 0 ; k < 20 ; k++){

    	for(uint8_t x = 0; x < DISPLAY_ROWS ; x++){
        	setPixel16(x, x, 1);
        }
    	updateDisplay16();
    	shiftLeft16();
    	HAL_Delay(100);
    }
    fill16(0);
    updateDisplay16();
}
