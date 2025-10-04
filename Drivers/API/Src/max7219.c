#include "max7219.h"

static uint8_t frameBuffer16[DISPLAY_ROWS][DISPLAY_COLS/8]; // representacion del display en RAM

// Se inicializan los 4 displays

void MAX7219_InitAll(void)
{

    MAX7219_WriteRowAll(MAX7219_SHUTDOWN, 0x01, 0x01, 0x01, 0x01); // 0x0C -> Shutdown | 0x01 -> Operacion Normal

    MAX7219_WriteRowAll(MAX7219_SCAN, 0x07, 0x07, 0x07, 0x07); // 0x0B -> Escaneo del Display (filas) | 0x07 -> Habilita las 8 filas

    MAX7219_WriteRowAll(MAX7219_MODE, 0x00, 0x00, 0x00, 0x00); // 0x09 -> Modo del Display (Matriz, 7 segmentos) | 0x00 -> Sin Decode (Matriz)

    MAX7219_WriteRowAll(MAX7219_BRIGHTNESS, 0x02, 0x02, 0x02, 0x02); // 0x0A -> Brillo del Display | 0x02 -> Configurable de 0 a 15 (PWM)

    MAX7219_WriteRowAll(MAX7219_TEST, 0x00, 0x00, 0x00, 0x00); // 0x0F -> Test del Display | 0x00 -> Test Apagado

    // Limpia la pantalla
    for (uint8_t row = 1; row <= MAX7219_ROWS; row++) {
        MAX7219_WriteRowAll(row, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    // Limpia el frameBuffer
    for (uint8_t row = 0; row < DISPLAY_ROWS ; row++){
    	frameBuffer16[row][0] = 0;
    	frameBuffer16[row][1] = 0;
    }
}


// enciende o apaga un pixel de la matriz
void setPixel16(uint8_t x, uint8_t y, bool on) {
    if (x >= DISPLAY_COLS || y >= DISPLAY_ROWS) return;  // fuera de rango

    uint8_t byteIndex = x / 8;       // 0 o 1
    uint8_t bitIndex  = x % 8;       // 0 a 7

    if (on)
        frameBuffer16[y][byteIndex] |=  (1 << bitIndex);
    else
        frameBuffer16[y][byteIndex] &= ~(1 << bitIndex);
}

// funcion auxiliar para "dar vuelta" los displays de abajo
static uint8_t reverseBits(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

// actualiza el display con lo que hay en el frameBuffer
void updateDisplay16(void)
{
    for (uint8_t y = 0; y < 8; y++) {
        uint8_t TL = frameBuffer16[y][1];
        uint8_t TR = frameBuffer16[y][0];
        uint8_t BL = reverseBits(frameBuffer16[15-y][1]);
        uint8_t BR = reverseBits(frameBuffer16[15-y][0]);

        MAX7219_WriteRowAll(y + 1, TR, TL, BL, BR);
    }
}

// desplaza lo que hay en el frameBuffer una posicion a la izquierda
void shiftLeft16(void){

	for(uint8_t y = 0 ; y < DISPLAY_ROWS ; y++){

		uint16_t combined = ((uint16_t)frameBuffer16[y][0] << 8) | frameBuffer16[y][1];

		uint16_t msb = (combined & 0x8000) >> 15;

		combined = (combined << 1) | msb;

		frameBuffer16[y][0] =  combined >> 8 & 0xFF;
		frameBuffer16[y][1] =  combined & 0xFF;
	}
}

// funcion auxiliar que busca un caracter en la lista de caracteres y devuelve un puntero a ese caracter
static const Chars5x7* findChar(char character){

	for(uint8_t k = 0 ; k < sizeof(font5x7) / sizeof(font5x7[0]) ; k++){
		if(font5x7[k].ch == character){
			return &font5x7[k];
		}
	}
	return &font5x7[0];
}

// dibuja un caracter con la esquina superior izquierda ubicada en (x,y)

void drawChar16(uint8_t x, uint8_t y, char character) {

	const Chars5x7* symbol = findChar(character);

    for (uint8_t column = 0; column < 5; column++) {
        uint8_t columnBits = symbol->col[column];

        for (uint8_t row = 0; row < 7; row++) {
            bool on = columnBits & (1 << row);
            setPixel16(x + (4- column), y + row, on);
        }
    }
}

void fill16(bool on)
{
    memset(frameBuffer16, on ? 0xFF : 0x00, sizeof(frameBuffer16));
}



