#ifndef FONT_H
#define FONT_H
#include <stdint.h>


const int FONT_CHAR_WIDTH  = 8;
const int FONT_CHAR_HEIGHT = 7;
const int GAMEOVER_LIST = 9;
const int FONT_START = ' ';
const int FONT_END = 'Z';
// Space ' '
const uint8_t FONT_SPACE[] = {
    0b00000000, //   . . . . . . . .
    0b00000000, //   . . . . . . . .
    0b00000000, //   . . . . . . . .
    0b00000000, //   . . . . . . . .
    0b00000000, //   . . . . . . . .
    0b00000000, //   . . . . . . . .
    0b00000000  //   . . . . . . . .
};

const uint8_t FONT_A[] = {
    0b00011100, // . . X X X . . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00111110, // . X X X X X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00000000  // (Spacing row)
};

// 'B'
const uint8_t FONT_B[] = {
    0b00111000, // . X X X . . . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00111000, // . X X X . . . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00111000  // . X X X . . . .
};

// 'C'
const uint8_t FONT_C[] = {
    0b00011100, // . . X X X . . .
    0b00100010, // . X . . . X . .
    0b00100000, // . X . . . . . .
    0b00100000, // . X . . . . . .
    0b00100000, // . X . . . . . .
    0b00100010, // . X . . . X . .
    0b00011100  // . . X X X . . .
};


// 'E'
const uint8_t FONT_E[] = {
    0b00111100, // . X X X X . . .
    0b00100000, // . X . . . . . .
    0b00100000, // . X . . . . . .
    0b00111000, // . X X X . . . .
    0b00100000, // . X . . . . . .
    0b00100000, // . X . . . . . .
    0b00111100  // . X X X X . . .
};


// 'G'
const uint8_t FONT_G[] = {
    0b00011100, // . . X X X . . .
    0b00100010, // . X . . . X . .
    0b00100000, // . X . . . . . .
    0b00101110, // . X . X X X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00011100  // . . X X X . . .
};


// 'I'
const uint8_t FONT_I[] = {
    0b00111000, // . X X X . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00111000  // . X X X . . . .
};



uint8_t FONT_M[] = {
    0b00111110, //   . X X X X X . .
    0b00101010, //   . X . X . X . .
    0b00101010, //   . X . X . X . .
    0b00101010, //   . X . X . X . .
    0b00100010, //   . X . . . X . .
    0b00100010, //   . X . . . X . .
    0b00000000  //   . . . . . . . .
};

// 'N'
const uint8_t FONT_N[] = {
    0b00100010, // . X . . . X . .
    0b00110010, // . X X . . X . .
    0b00101010, // . X . X . X . .
    0b00100110, // . X . . X X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00000000  // (Spacing row)
};

uint8_t FONT_O[] = {
    0b00011100, //   . . X X X . . .
    0b00100010, //   . X . . . X . .
    0b00100010, //   . X . . . X . .
    0b00100010, //   . X . . . X . .
    0b00100010, //   . X . . . X . .
    0b00100010, //   . X . . . X . .
    0b00011100  //   . . X X X . . .
};

uint8_t FONT_R[] = {
    0b00111100, //   . X X X X . . .
    0b00100010, //   . X . . . X . .
    0b00100010, //   . X . . . . X .
    0b00111000, //   . X . . . . X .
    0b00100100, //   . X X X X X . .
    0b00100010, //   . X . . . . X .
    0b00100001  //   . X . . . . .X (assuming a straight leg for R)
};

// 'S'
const uint8_t FONT_S[] = {
    0b00011110, // . . X X X X . .
    0b00100000, // . X . . . . . .
    0b00100000, // . X . . . . . .
    0b00011100, // . . X X X . . .
    0b00000010, // . . . . . X . .
    0b00000010, // . . . . . X . .
    0b00111100  // . X X X X . . .
};

// 'T'
const uint8_t FONT_T[] = {
    0b00111110, // . X X X X X . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00010000, // . . X . . . . .
    0b00000000  // (Spacing row)
};

// 'U'
const uint8_t FONT_U[] = {
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00011100  // . . X X X . . .
};


// 'W'
const uint8_t FONT_W[] = {
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00101010, // . X . X . X . .
    0b00101010, // . X . X . X . .
    0b00010100, // . . X . X . . .
    0b00000000  // (Spacing row - this W is 5 pixels wide)
};



const uint8_t FONT_V[] = {
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00010100, // . . X . X . . .
    0b00001000  // . . . X . . . .
};

const uint8_t FONT_Y[] = {
    0b00100010, // . X . . . X . .
    0b00100010, // . X . . . X . .
    0b00010100, // . . X . X . . .
    0b00001000, // . . . X . . . .
    0b00001000, // . . . X . . . .
    0b00001000, // . . . X . . . .
    0b00000000  // (Spacing row)
};


const uint8_t* font_lookup_table[18];

void initializeFontLookup() {
    // Clear all entries to point to the FONT_SPACE bitmap initially.
    // This makes sure any character not explicitly mapped will display as a space.
    font_lookup_table[0] = FONT_SPACE;
    font_lookup_table[1] = FONT_A;
    font_lookup_table[2] = FONT_B;
    font_lookup_table[3] = FONT_C;
    font_lookup_table[4] = FONT_E;
    font_lookup_table[5] = FONT_G;
    font_lookup_table[6] = FONT_I;
    font_lookup_table[7] = FONT_M;
    font_lookup_table[8] = FONT_N;
    font_lookup_table[9] = FONT_R;
    font_lookup_table[10] = FONT_S;
    font_lookup_table[11] = FONT_T;
    font_lookup_table[12] = FONT_W;
    font_lookup_table[13] = FONT_V;
    font_lookup_table[14] = FONT_O;
    font_lookup_table[15] = FONT_Y;
    font_lookup_table[16] = FONT_U;
}

#endif