#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Coordenadas
typedef struct {
    uint8_t x;
    uint8_t y;
} PositionXY_t;

// Estados posibles de la serpiente
typedef enum{
	DEAD,
	ALIVE
}SnakeStatus_t;

// Posibles 4 direcciones de movimiento de la serpiente
typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT
}SnakeDir_t;

// Cada serpiente tiene un cuerpo (16x16 = 256 de largo maximo), un largo, una direccion y un estado
typedef struct {
	PositionXY_t body[256];
    uint8_t length;
    SnakeDir_t dir;
    SnakeStatus_t snakeStatus;
} Snake_t;

// Cada "manzana" tiene una posicion
typedef struct {
	PositionXY_t pos;
} Food_t;

extern uint16_t currentScore;




void snakeInit(void);
bool snakeUpdate(void);
