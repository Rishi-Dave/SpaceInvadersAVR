#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spiAVR.h"
#include "ST7737.h"
#include "serial.h"
#include "font.h"
#include "Objects.h"
#include "pixelData.h"
#ifndef DRAWINGS_H
#define DRAWINGS_H






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
    //send every bit as one packet to lower latency
    SetPin(&PORTB, CS_PIN, 0); 
    SetPin(&PORTB, A0_PIN, 1);

    uint8_t colorHigh = color >> 8;
    uint8_t colorLow = color & 0xFF;
    for (int i = 0; i < w * h; i++) {
        
        SPI_SEND(colorHigh);
        SPI_SEND(colorLow);
    }

    SetPin(&PORTB, CS_PIN, 1);
}

void drawShip(Ship ship) {
    int x = ship.getX();
    int y = ship.getY();
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

void drawAlien(Alien alien) {
    int x = alien.getX();
    int y = alien.getY();
    Send_Command(0x2A); //CASET (columns)
    Send_Data(0x00);
    Send_Data(x);
    Send_Data(0x00);
    Send_Data(x + ALIEN_WIDTH - 1);

    Send_Command(0x2B); //RASET (rows)
    Send_Data(0x00);
    Send_Data(y);
    Send_Data(0x00);
    Send_Data(y + ALIEN_HEIGHT - 1);

    Send_Command(0x2C); //RAMWR (write to rows)

    //send every bit as one packet to lower latency
    SetPin(&PORTB, CS_PIN, 0); 
    SetPin(&PORTB, A0_PIN, 1);
    int state = alien.getState();
    for (int i = 0; i < (ALIEN_HEIGHT * ALIEN_WIDTH); i++) {
        uint16_t color = alien_data[state][i];
        SPI_SEND(color  >> 8);
        SPI_SEND(color & 0xFF);      
    }

    SetPin(&PORTB, CS_PIN, 1);
    
}


void drawBullet(Bullet* bullet) {
    int x = bullet->getX();
    int y = bullet->getY();
    Send_Command(0x2A); //CASET (columns)
    Send_Data(0x00);
    Send_Data(x);
    Send_Data(0x00);
    Send_Data(x + BULLET_WIDTH - 1);

    Send_Command(0x2B); //RASET (rows)
    Send_Data(0x00);
    Send_Data(y);
    Send_Data(0x00);
    Send_Data(y + BULLET_HEIGHT - 1);

    Send_Command(0x2C); //RAMWR (write to rows)

    //send every bit as one packet to lower latency
    SetPin(&PORTB, CS_PIN, 0); 
    SetPin(&PORTB, A0_PIN, 1);

    int state = bullet->getState();
    for (int i = 0; i < (BULLET_HEIGHT * BULLET_WIDTH); i++) {
        uint16_t color = bullet_data[state][i];
        SPI_SEND(color  >> 8);
        SPI_SEND(color & 0xFF);      
    }

    SetPin(&PORTB, CS_PIN, 1);
    
}

void my_lcd_set_pixel(int x, int y, uint16_t color) {
    Send_Command(0x2A); //CASET (columns)
    Send_Data(0x00);
    Send_Data(x);
    Send_Data(0x00);
    Send_Data(x + 1);

    Send_Command(0x2B); //RASET (rows)
    Send_Data(0x00);
    Send_Data(y);
    Send_Data(0x00);
    Send_Data(y +1);

    Send_Command(0x2C); //RAMWR (write to rows)

    //send every bit as one packet to lower latency
    SetPin(&PORTB, CS_PIN, 0); 
    SetPin(&PORTB, A0_PIN, 1);

    SPI_SEND(color  >> 8);
    SPI_SEND(color & 0xFF);

    SetPin(&PORTB, CS_PIN, 1);
}

void drawChar(int x, int y, uint16_t foreground_color, uint16_t background_color, uint8_t charCode) {

    const uint8_t* charBits = font_lookup_table[charCode];
    for (int row = 0; row < FONT_CHAR_HEIGHT; ++row) {
        uint8_t row_data = charBits[row]; // Read row data for this character

        for (int col = 0; col < FONT_CHAR_WIDTH; ++col) {
            // Check the appropriate bit for the pixel (leftmost of 5 bits)
            if ((row_data >> (FONT_CHAR_WIDTH - 1 - col)) & 0x01) {
                my_lcd_set_pixel(x + col, y + row, foreground_color);
            } else {
                my_lcd_set_pixel(x + col, y + row, background_color);
            }
        }
    }
}

void gameOver() {
    int gameover[] = {5,1,7,4,0,14,13,4,9};
    for(unsigned int i = 0; i < 9; i++){
        drawChar(i*10+ 10, 60, COLOR_RED, COLOR_BLACK, gameover[i]);
    }
}

void gameWin() {
    int gamewin[] = {15,14,16,0,12,6,8};
    for(unsigned int i = 0; i < 7; i++){
        drawChar(i*10+ 10, 60, COLOR_GREEN, COLOR_BLACK, gamewin[i]);
    }
}

bool Bullet::hit(Alien alien) {
    int aX = alien.getX();
    int aY = alien.getY();
    if(abs(x - aX) <= 15 && abs(y - aY) <=15) {
        return true;
    }   
return false;
}

Bullet::~Bullet() {
    fillRect(this->getX(), this->getY(), BULLET_WIDTH+2, BULLET_HEIGHT+2, COLOR_BLACK);
}

#endif
