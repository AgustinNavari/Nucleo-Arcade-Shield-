#include "resources.h"

#include "boardConfig.h"


static const uint32_t debounceDelay = 30; // determina el tiempo de duracion del delay

button_t buttons[NUM_BUTTONS] = {
    {GPIOA, GPIO_PIN_8, BUTTON_UP, {0, debounceDelay, false}, false}, // Back / Pause
    {GPIOA, GPIO_PIN_9, BUTTON_UP, {0, debounceDelay, false}, false}, // Select / Start
    {GPIOB, GPIO_PIN_4, BUTTON_UP, {0, debounceDelay, false}, false}, // Derecha
    {GPIOB, GPIO_PIN_5, BUTTON_UP, {0, debounceDelay, false}, false}, // Arriba
    {GPIOB, GPIO_PIN_6, BUTTON_UP, {0, debounceDelay, false}, false}, // Izquierda
    {GPIOC, GPIO_PIN_7, BUTTON_UP, {0, debounceDelay, false}, false}, // Abajo
};

static bool_t delayIsRunning(delay_t * delay){
	return delay->running;
}

void delayInit(delay_t * delay, tick_t duration){

	delay->duration = duration;
	delay->running = false;

}

bool_t delayRead(delay_t * delay){

	if (delay->running == false){
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	if ((delay->running == true) && (HAL_GetTick() - delay->startTime > delay->duration)){

		delay->running = false;
		return true; //si paso el tiempo devuelve "true"

	}else{
		return false; //si aun no paso el tiempo devuelve "false"
	}
}

void delayWrite(delay_t * delay, tick_t duration){

	if(delayIsRunning(delay)){
		delay->duration = duration;
	}
}

// debounceFSM_init carga el estado inicial en BUTTON_UP
void debounceFSM_init(button_t * btn){
	btn -> state = BUTTON_UP;
}

// debounceFSM_update maneja los cambios de estado
void debounceFSM_update(button_t * btn){

	bool pin = HAL_GPIO_ReadPin(btn -> port, btn -> pin); // lee el estado del pin

	switch(btn -> state){
		case BUTTON_UP:

			if(!pin){
				btn -> state = BUTTON_FALLING;
				delayInit(&btn->delay,debounceDelay);
				delayRead(&btn->delay);
			}
			break;

		case BUTTON_FALLING:

			if(delayRead(&btn->delay)==true){
				bool pin = HAL_GPIO_ReadPin(btn -> port, btn -> pin);
				if(!pin){										// si paso el tiempo y el boton continua apretado, se enciende el LED y cambia al estado BUTTON_DOWN
					btn->pressed = true; 						// buttonState se hace true cuando se confirma que el boton esta presionado
					btn -> state = BUTTON_DOWN;
				}else{btn -> state = BUTTON_UP;}
			}

			break;

		case BUTTON_DOWN:

			if(pin){
				btn -> state = BUTTON_RAISING;
				delayInit(&btn->delay,debounceDelay);
				delayRead(&btn->delay);
			}

			break;

		case BUTTON_RAISING:

			if(delayRead(&btn->delay)==true){
				bool pin = HAL_GPIO_ReadPin(btn -> port, btn -> pin);
				if(pin){										// si paso el tiempo y el boton continua suelto, se apaga el LED y cambia al estado BUTTON_UP
					btn -> state = BUTTON_UP;
				}else{
					btn -> state = BUTTON_DOWN;
				}
			}

			break;

		default:
			debounceFSM_init(btn);
			break;
	}
}

bool readKey(uint8_t i){												// readKey es una funcion publica a la que se le puede consultar por el estado del boton
	if(buttons[i].pressed){
		buttons[i].pressed = false;
		return true;
	}else{
		return false;
	}
}
