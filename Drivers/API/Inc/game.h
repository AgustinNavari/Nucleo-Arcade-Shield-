#include <stdint.h>
#include <stdbool.h>
#include "max7219_port_stm32.h"
#include "boardConfig.h"
#include "max7219.h"

typedef enum {
    BOOT,        // Inicialización del sistema y recursos del juego
    MENU,        // Menú principal (selección o inicio del juego)
    PLAYING,     // Juego en ejecución
    PAUSED,      // Juego pausado temporalmente
    GAME_OVER,   // Fin del juego actual
    HSCORE       // Pantalla de puntuación máxima
} ArcadeState_t;

void arcadeFSM(void);
void systemInit(void);
void startScreen(void);

