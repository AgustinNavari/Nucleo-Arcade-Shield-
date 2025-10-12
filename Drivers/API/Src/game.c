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
        	scrollTextDual(0, text1, 8, text2,false);
        	if (readKey(1)){
        		arcadeState = PLAYING;
        		snakeInit();
        	}
        	if (readKey(0)){
        		arcadeState = HSCORE;
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
        	if (readKey(0)){
        		arcadeState = PAUSED;
        	}

            break;

        case PAUSED:

        	char text5[] = "PAUSA";
        	char text6[] = "     PAUSA";
        	scrollTextDual(0, text5, 8, text6,true);
        	if (readKey(1)){
        		arcadeState = PLAYING;
        	}

            break;

        case GAME_OVER:
        	char text3[40];
        	sprintf(text3,"ACTUAL %u", currentScore);
        	char text4[40];
        	sprintf(text4,"MAX %u", loadScore());
        	scrollTextDual(0, text3, 8, text4,true);
            if (readKey(1)) {
                arcadeState = MENU;
            }

            break;

        case HSCORE:

           	char text7[40];
			sprintf(text7,"HIGHSCORE");
			char text8[40];
			sprintf(text8,"       %u", loadScore());
			scrollTextDual(0, text7, 8, text8,true);
            if (readKey(1)) {
                arcadeState = MENU;
            }
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

    fill16(0);
    updateDisplay16();

    for (uint8_t x = 0; x < 16; x++) {
        for (uint8_t y = 0; y < 16; y++) {
            setPixel16(x, y, 1);
        }
        updateDisplay16();
        HAL_Delay(50);
    }
    HAL_Delay(100);
}
