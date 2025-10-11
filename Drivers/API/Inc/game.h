#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BOOT,        // Inicialización del sistema y recursos del juego
    MENU,        // Menú principal (selección o inicio del juego)
    PLAYING,     // Juego en ejecución
    PAUSED,      // Juego pausado temporalmente
    GAME_OVER,   // Fin del juego actual
    HSCORE       // Pantalla de puntuación máxima
} ArcadeState_t;

extern ArcadeState_t arcadeState;


void arcadeFSM(void);
void systemInit(void);
void startScreen(void);

