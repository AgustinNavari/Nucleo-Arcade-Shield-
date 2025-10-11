#include "game.h"
#include "max7219.h"
#include "max7219_port_stm32.h"
#include "boardConfig.h"
#include "snake.h"
#include "resources.h"
#include "At24c256.h"
#include <stdio.h>

ArcadeState_t arcadeState = BOOT;


void arcadeFSM(void)
{
    switch (arcadeState){

        case BOOT:

        startScreen();
		systemInit();
		arcadeState = MENU;

            break;

        case MENU:
        	char text1[] = "NUCLEO ARCADE SHIELD VO1";
        	char text2[] = "PRESIONE START PARA COMENZAR";
        	scrollTextDual(0, text1, 8, text2);
        	if (readKey(1)){
        		arcadeState = PLAYING;
        		snakeInit();
        	}
            break;

        case PLAYING:
        	if(snakeUpdate() == false){
        		if(currentScore > loadScore()){
        			saveScore(currentScore);
        		}
        		arcadeState = GAME_OVER;
        	}
            break;

        case PAUSED:

            break;

        case GAME_OVER:
        	char text3[40];
        	sprintf(text3,"TU PUNTUACION FUE: %u", currentScore);
        	char text4[40];
        	sprintf(text4,"LA PUNTUACION MAS ALTA ES: %u", loadScore());
        	scrollTextDual(0, text3, 8, text4);
            if (readKey(1)) {
                arcadeState = MENU;
            }

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
