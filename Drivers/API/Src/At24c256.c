#include "At24c256.h"

void saveScore(uint16_t score) {
    EEPROM_Write(score);
}

uint16_t loadScore(void) {
    return EEPROM_Read();
}
