#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Objects.h"
#ifndef HELPER_H
#define HELPER_H
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
              //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

void SetPin(volatile uint8_t *port, uint8_t pin, uint8_t state) {
    if (state) {
        *port |= (1 << pin); // Set bit to HIGH
    } else {
        *port &= ~(1 << pin); // Set bit to LOW
    }
}

int direction(int x, int y){
  if(x < 500 ){
    return 4;
  }
  else if(x > 600 ) {
    return 3;
  }

  else if(y < 500 ){
    return 1;
  }
  else if(y > 600) {
    return 2;
  }
  else{
    return 0;

  }

}
 
void ShiftLeft(Bullet** pArr, int index, int length)
{
  for (int i = index; i < length; i++)
  {
    Bullet* tmp = pArr[i - 1]; // Preserves the previous value
    pArr[i - 1] = pArr[i]; // Overwrites the previous position with the current value
    pArr[i] = tmp;         // Stores the previous value in the current position
                           // All in all the first value is swapped down the array until it is at the length - 1 position                        // and all the other values are swapped to the left.
  }
}



int nums[16] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011, 0b1110111, 0b0011111, 0b1001110, 0b0111101, 0b1001111, 0b1000111 }; 
// a  b  c  d  e  f  g

void outNum(int num){
	//
}



#endif