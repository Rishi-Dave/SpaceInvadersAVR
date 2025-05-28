#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spiAVR.h"
#include "helper.h"

#ifndef ST7735_H
#define St7735_H

#define RST_PIN  0 // Assuming PB0
#define A0_PIN   1 // Assuming PB1
#define CS_PIN   2 // Assuming PB2

void Send_Command(uint8_t cmd) {
    SetPin(&PORTB, A0_PIN, 0); // DC low (command mode)
    SetPin(&PORTB, CS_PIN, 0); // CS low (select device)
    SPI_SEND(cmd);
    SetPin(&PORTB, CS_PIN, 1);
}

void Send_Data(uint8_t data) {
    SetPin(&PORTB, A0_PIN, 1); // DC low (command mode)
    SetPin(&PORTB, CS_PIN, 0); // CS low (select device)
    SPI_SEND(data);
    SetPin(&PORTB, CS_PIN, 1);
}

void HardwareReset(){
    SetPin(&PORTB, RST_PIN, 0);
    _delay_ms(200);
    SetPin(&PORTB, RST_PIN, 1);;
    _delay_ms(200);
}
void ST7735_init(){
    HardwareReset();
 
    Send_Command(0x01); // SWRESET (Software Reset)
    _delay_ms(150);

    Send_Command(0x11); // SLPOUT (Sleep Out)
    _delay_ms(200);

    Send_Command(0x3A); // COLMOD (Color Mode)
    Send_Data(0x05); //for 18 bit color mode. You can pick any color mode you want
    _delay_ms(10);

    Send_Command(0x29); // DISPON (Display On)
    _delay_ms(200);     
    
    Send_Command(0x36); // MADCTL
    Send_Data(0xC0);        
    _delay_ms(10);
}


#endif