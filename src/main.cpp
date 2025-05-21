
#include "drawings.h"



int main() {

  DDRB |= (1 << RST_PIN) | // PB0 as Output (RST)
          (1 << A0_PIN)  | // PB1 as Output (DC)
          (1 << CS_PIN)  | // PB2 as Output (CS/SS)
          (1 << PIN_MOSI)       | // PB3 as Output (MOSI)
          (1 << PIN_SCK);  

  PORTB |= (1 << RST_PIN) | // RST to HIGH
           (1 << A0_PIN)  | // DC to HIGH (idle data mode)
           (1 << CS_PIN);

  SPI_INIT();
  ST7735_init();
  serial_init(9600);

  fillRect(0,0,150,150, COLOR_BLACK);

  while(1) {
    drawShip(60,60);
    
    _delay_ms(1000);
  }
}
