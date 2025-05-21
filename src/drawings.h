#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spiAVR.h"
#include "ST7737.h"
#include "serial.h"
#ifndef DRAWINGS_H
#define DRAWINGS_H

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE  0x001F

const uint16_t ship_data[] = {
    COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, // Row 0
    COLOR_BLACK, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_BLACK, // Row 1
    COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_BLACK, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, // Row 2
    COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, // Row 3
    COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK  // Row 4
};

const int SHIP_WIDTH = 7;
const int SHIP_HEIGHT = 5;


void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    Send_Command(0x2A); //CASET (columns)
    Send_Data(0x00);
    Send_Data(x );
    Send_Data(0x00);
    Send_Data(x + 3 + w - 1);

    Send_Command(0x2B); //RASET (rows)
    Send_Data(0x00);
    Send_Data(y);
    Send_Data(0x00);
    Send_Data(y + 3 + h - 1);

    Send_Command(0x2C); //RAMWR (write to rows)
    serial_println(PORTB);
    //send every bit as one packet to lower latency
    SetPin(&PORTB, CS_PIN, 0); 
    SetPin(&PORTB, A0_PIN, 1);

    uint8_t colorHigh = color >> 8;
    uint8_t colorLow = color & 0xFF;
    serial_println(PORTB);
    for (int i = 0; i < w * h; i++) {
        
        SPI_SEND(colorHigh);
        SPI_SEND(colorLow);
    }

    SetPin(&PORTB, CS_PIN, 1);
    serial_println(PORTB);
}

void drawShip(uint8_t x, uint8_t y) {
    Send_Command(0x2A); //CASET (columns)
    Send_Data(0x00);
    Send_Data(x);
    Send_Data(0x00);
    Send_Data(x + SHIP_WIDTH - 1);

    Send_Command(0x2B); //RASET (rows)
    Send_Data(0x00);
    Send_Data(y);
    Send_Data(0x00);
    Send_Data(y + SHIP_HEIGHT - 1);

    Send_Command(0x2C); //RAMWR (write to rows)

    //send every bit as one packet to lower latency
    SetPin(&PORTB, CS_PIN, 0); 
    SetPin(&PORTB, A0_PIN, 1);

    for (int i = 0; i < (SHIP_HEIGHT * SHIP_WIDTH); i++) {
        uint16_t color = ship_data[i];
        SPI_SEND(color  >> 8);
        SPI_SEND(color & 0xFF);      
    }

    SetPin(&PORTB, CS_PIN, 1);
    
}

#endif
