#include "game.h"
#include "max7219.h"
#include "boardConfig.h"
#include "snake.h"
#include "resources.h"
#include "At24c256.h"
#include <stdio.h>

static char textMenu1[] = "SNAKE";
static char textMenu2[] = "      PRESIONE START";
static char textPause1[]= "PAUSA";
static char textPause2[]= "     PAUSA";
static char textBlank[]= " ";
static char textHighscore[]= "HIGHSCORE";


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

		//MENU del juego. Scroll de texto y espera un input para jugar o mostrar el highscore
        case MENU:

        	scrollTextDual(0, textMenu1, 8, textMenu2);

        	if (readKey(START)){
        		arcadeState = PLAYING;
        		startScreen();
        		snakeInit();
        	}

        	if (readKey(BACK)){
        		arcadeState = HSCORE;
        		snakeInit();
        	}

            break;

        //PLAYING juego en curso
        case PLAYING:

        	if(snakeUpdate() == false){
        		if(currentScore > loadScore()){				//se guarda la puntuacion actual si es mayor a la puntuacion guardada mas alta
        			saveScore(currentScore);
        		}
        		startScreen();
        		arcadeState = GAME_OVER;
        	}

        	if (readKey(BACK)){								//presionar el boton de "back" pausa el juego
        		arcadeState = PAUSED;
        	}

            break;

        case PAUSED:

        	scrollTextDual(0, textPause1, 8, textPause2);
        	if (readKey(START)){
        		arcadeState = PLAYING;
        	}

            break;

        case GAME_OVER:

        	char text3[40];
        	sprintf(text3,"ACTUAL %u", currentScore);

        	scrollTextDual(0, text3, 8, textBlank);

        	if (readKey(START)) {
            	startScreen();
                arcadeState = HSCORE;
            }

            break;

        case HSCORE:

			char text8[40];
			sprintf(text8,"         %u", loadScore());
			scrollTextDual(0, textHighscore, 8, text8);

			if (readKey(START)) {
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
