#include "snake.h"
#include "game.h"
#include "max7219.h"
#include "resources.h"
#include "stm32f4xx_hal.h"

static Snake_t snake;
static Food_t food;
static delay_t snakeSpeed;
uint16_t currentScore;
extern ArcadeState_t arcadeState;

static void spawnFood(void) {
    uint8_t valid = 0;
    while (!valid) {
        food.pos.x = rand() % DISPLAY_COLS;
        food.pos.y = rand() % DISPLAY_ROWS;
        valid = 1;
        for (int i = 0; i < snake.length; i++) {
            if (food.pos.x == snake.body[i].x && food.pos.y == snake.body[i].y) {
                valid = 0;
                break;
            }
        }
    }
}

//snakeInit inicializa una nueva serpiente
void snakeInit(void) {

	delayInit(&snakeSpeed, 120);
    snake.length = 3;
    snake.dir = UP;
    snake.snakeStatus = ALIVE;
    snake.body[0] = (PositionXY_t){8, 8};
    snake.body[1] = (PositionXY_t){7, 8};
    snake.body[2] = (PositionXY_t){6, 8};
    currentScore = snake.length;
    fill16(0);
    spawnFood();

    for (int i = 0; i < snake.length; i++) {
        setPixel16(snake.body[i].x, snake.body[i].y, 1);
    }
    updateDisplay16();

}

// snakeMove se encarga del movimiento de la serpiente y validar si esta no choca
static void snakeMove(void) {

    PositionXY_t nextMove = snake.body[0];     // seteamos nextMove en la "cabeza" de la serpiente
    snake.snakeStatus = ALIVE;

    switch (snake.dir) { // movemos la cabeza segun corresponda
        case UP:
            nextMove.y--;
            break;
        case DOWN:
            nextMove.y++;
            break;
        case LEFT:
            nextMove.x++;
            break;
        case RIGHT:
            nextMove.x--;
            break;
        default:
        	snake.dir = UP;
            break;
    }

    if (nextMove.x < 0 || nextMove.x > 15 || nextMove.y < 0 || nextMove.y > 15) { //validamos que la nueva posicion de la cabeza este dentro del tablero
    	snake.snakeStatus = DEAD;
    	return; }


    for (int i = 1; i < snake.length; i++) { // detecta si choca con sigo misma
        if (snake.body[i].x == nextMove.x && snake.body[i].y == nextMove.y) {
        	snake.snakeStatus = DEAD;
        	return;
        }
    }

    if((nextMove.x == food.pos.x) && (nextMove.y == food.pos.y)){ // si pasa por la comida, suma puntos, aumenta la longitud y spawnea una nueva "manzana"
    	snake.length += 1;
    	currentScore += 1;
    	spawnFood();
    }


    for (uint8_t k = snake.length - 1; k > 0; k--) { //movemos la serpiente
        snake.body[k] = snake.body[k - 1];
    }

    snake.body[0] = nextMove; //movemos la cabeza
}

//dibuja la serpiente en pantalla
static void snakeDraw(void) {

	fill16(0);

    for (int i = 0; i < snake.length; i++) {
        setPixel16(snake.body[i].x, snake.body[i].y, 1);
    }
    setPixel16(food.pos.x, food.pos.y, 1);
    updateDisplay16();
}

//snakeUpdate devuelve true si la serpiente sigue viva o false si la serpiente choco.
bool snakeUpdate(void) {

	if (snake.snakeStatus == DEAD){
		return false;
	}
// segun el boton que se presione cambia la direccion de la serpiente. Aca se valida que la serpiente no pueda "volver sobre si misma"
    if (readKey(2) && snake.dir != LEFT) snake.dir = RIGHT;
    if (readKey(3) && snake.dir != DOWN) snake.dir = UP;
    if (readKey(4) && snake.dir != RIGHT) snake.dir = LEFT;
    if (readKey(5) && snake.dir != UP) snake.dir = DOWN;

//si paso el "Tick" de la serpiente la actualiza
    if ((HAL_GetTick() - snakeSpeed.startTime) >= snakeSpeed.duration) {
        snakeSpeed.startTime = HAL_GetTick();

        snakeMove();
        snakeDraw();
        return true;

    }
    return true;
}



