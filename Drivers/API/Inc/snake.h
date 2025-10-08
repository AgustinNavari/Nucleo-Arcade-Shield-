#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>



typedef struct {
    uint8_t x;
    uint8_t y;
} PositionXY_t;

typedef struct {
	PositionXY_t body[64];
    uint8_t length;
    uint8_t dir; // 0= arriba ,1 = derecha, 2=abajo,3=izquierda
} Snake_t;

typedef struct {
	PositionXY_t pos;
} Food_t;

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT
}SnakeDir_t;

void snakeInit(void);
void snakeUpdate(void) ;
