#include "At24c256.h"

// saveScore guarda el puntaje
void saveScore(uint16_t score) {
    EEPROM_Write(score);
}
// saveScore levanta el valor guardado en la memoria
uint16_t loadScore(void) {
    return EEPROM_Read();
}
