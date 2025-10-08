#include "snake.h"
#include "game.h"
#include "max7219.h"
#include "resources.h"

static Snake_t snake;
static Food_t food;
static SnakeDir_t snakeDir = UP;

static delay_t snakeSpeed = {0,250,false};

extern ArcadeState_t arcadeState;

void snakeInit(void) {

	delayInit(&snakeSpeed, 120);

    snake.length = 3;
    snake.dir = UP;
    snake.body[0] = (PositionXY_t){8, 8};
    snake.body[1] = (PositionXY_t){7, 8};
    snake.body[2] = (PositionXY_t){6, 8};
    food.pos = (PositionXY_t){rand() % 16,rand() % 16};
}


static void snakeMove(void) {


    PositionXY_t nextMove = snake.body[0];     // determina la proxima posicion de la cabeza

    switch (snakeDir) {
        case UP:
            if (nextMove.y > 0) nextMove.y--;
            break;
        case DOWN:
            if (nextMove.y < 15) nextMove.y++;
            break;
        case LEFT:
            if (nextMove.x > 0) nextMove.x++;
            break;
        case RIGHT:
            if (nextMove.x < 15) nextMove.x--;
            break;
        default:
        	snakeDir = UP;
            break;
    }


    if (nextMove.x < 0 || nextMove.x > 15 || nextMove.y < 0 || nextMove.y > 15) { //detecta si choca con paredes
        arcadeState = GAME_OVER;
    }

    for (int i = 1; i < snake.length; i++) { // detecta si choca con sigo misma
        if (snake.body[i].x == nextMove.x && snake.body[i].y == nextMove.y) {
            arcadeState = GAME_OVER;
            return;
        }
    }

    for (int k = snake.length - 1; k > 0; k--) {
        snake.body[k] = snake.body[k - 1];
    }

    snake.body[0] = nextMove;
}

static void snakeDraw(void) {

	fill16(0);

    for (int i = 0; i < snake.length; i++) {
        setPixel16(snake.body[i].x, snake.body[i].y, 1);
    }

    updateDisplay16(); // envía framebuffer al MAX7219
}


void snakeUpdate(void) {

    if (readKey(2) && snakeDir != LEFT) snakeDir = RIGHT;
    if (readKey(3) && snakeDir != DOWN) snakeDir = UP;
    if (readKey(4) && snakeDir != RIGHT) snakeDir = LEFT;
    if (readKey(5) && snakeDir != UP) snakeDir = DOWN;

    if ((HAL_GetTick() - snakeSpeed.startTime) >= snakeSpeed.duration) {
        snakeSpeed.startTime = HAL_GetTick();

        snakeMove();
        snakeDraw();
    }
}

