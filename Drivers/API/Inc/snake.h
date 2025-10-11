#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} PositionXY_t;

typedef enum{
	DEAD,
	ALIVE
}SnakeStatus_t;

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT
}SnakeDir_t;

typedef struct {
	PositionXY_t body[64];
    uint8_t length;
    SnakeDir_t dir;
    SnakeStatus_t snakeStatus;
} Snake_t;

typedef struct {
	PositionXY_t pos;
} Food_t;

extern uint16_t currentScore;




void snakeInit(void);
bool snakeUpdate(void);
