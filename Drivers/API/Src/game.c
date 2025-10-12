#include "game.h"
#include "max7219.h"
#include "boardConfig.h"
#include "snake.h"
#include "resources.h"
#include "At24c256.h"
#include <stdio.h>

ArcadeState_t arcadeState = BOOT;

//arcadeFSM controla los diferentes posibles estados del juego.
void arcadeFSM(void)
{
    switch (arcadeState){

    	//BOOT inicializa el HW y muestra la animacion de inicio
        case BOOT:
			systemInit();
			startScreen();
			arcadeState = MENU;
			break;

        case MENU:
        	char text1[] = "SNAKE";
        	char text2[] = "PRESIONE START";
        	scrollTextDual(0, text1, 8, text2,false);
        	if (readKey(1)){
        		arcadeState = PLAYING;
        		startScreen();
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
        		startScreen();
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
        	sprintf(text4,"HIGHSCORE %u", loadScore());
        	scrollTextDual(0, text3, 8, text4,true);
            if (readKey(1)) {
            	startScreen();
                arcadeState = MENU;
            }

            break;

        case HSCORE:

        	char text7[] = "HIGHSCORE";
			char text8[40];
			sprintf(text8,"         %u", loadScore());
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

// Inicializa el hardware necesario
void systemInit(void)
{
	board_gpio_init();
	I2C1_Init();
	SPI2_Init();
	MAX7219_InitAll();
}


// startScreen es una animacion para cuando se inicia el juego o se cambia de pantalla
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

}
