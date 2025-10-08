#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define NUM_BUTTONS 6

typedef bool pinState_t;
typedef bool bool_t;

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
}debounceState_t;

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
	tick_t startTime;
	tick_t duration;
	bool_t running;
}delay_t;

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
	debounceState_t state;
	delay_t delay;
	bool_t pressed;
} button_t;

void debounceFSM_init(button_t * btn);
void debounceFSM_update(button_t * btn);
bool_t readKey(uint8_t i);

void delayInit(delay_t * delay , tick_t duration);

bool_t delayRead(delay_t * delay);

void delayWrite(delay_t * delay , tick_t duration);
