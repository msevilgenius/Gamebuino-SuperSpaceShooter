/* 
 * File:   EnemyTypes.h
 * Author: Michael
 *
 * Created on 23 July 2014, 11:35
 */

#ifndef ENEMYTYPES_H
#define	ENEMYTYPES_H

#include <avr/pgmspace.h>

const byte dead_sprite[] PROGMEM = {
    0,0
};

const byte dead_movement[] PROGMEM = {
    0
};

const byte dead_shooting[] PROGMEM = {
    0
};

const byte basic_sprite[] PROGMEM = {
    7, 7, 
    B01111101,
    B10010001,
    B00111101,
    B01111001,
    B00111101,
    B10010001,
    B01111101
};

const byte basic_movement[] PROGMEM = {
    1, //numer of frames in the movement pattern
    -1, 0, // x movement, y movement
};

const byte basic_shooting[] PROGMEM = {
    1, //numer of different ### in the shooting pattern
    0b01000000, 16 // directions then delay in frames until next set of bullets
            //for directions each bit is a compass direction in this order : NW W SW S SE E NE N
            //so in this case it is W only
};

const byte spinner_sprite[] PROGMEM = {
    7, 7,
    B00000001,
    B00111001,
    B11111111,
    B10101011,
    B11111111,
    B00111001,
    B00000001
};

const byte spinner_movement[] PROGMEM = {
    1,
    -1, 0
};

const byte spinner_shooting[] PROGMEM = {
    8,
    0b10000000, 4,
    0b01000000, 4,
    0b00100000, 4,
    0b00010000, 4,
    0b00001000, 4,
    0b00000100, 4,
    0b00000010, 4,
    0b00000001, 4
};

const byte weaver_sprite[] PROGMEM = {
    7, 7,
    B00110001,
    B01000011,
    B11100101,
    B11111101,
    B11100101,
    B01000011,
    B00110001
};

const byte weaver_movement[] PROGMEM = {
    16, //numer of frames in the movement pattern
    -1, -1, // x movement, y movement
    -1, -1,
    -1, -1,
    -1, -1,
    -1, -1,
    -1, -1,
    -1, -1,
    -1, -1,
    -1, 1,
    -1, 1,
    -1, 1,
    -1, 1,
    -1, 1,
    -1, 1,
    -1, 1,
    -1, 1,
};

const byte weaver_shooting[] PROGMEM = {
    1,
    0b01000000, 24,
};

const byte *enemy_types[] PROGMEM = {
    dead_sprite, dead_movement, dead_shooting, //just to make the indexes work with the ENEMY_TYPE enum
    basic_sprite, basic_movement, basic_shooting,
    spinner_sprite, spinner_movement, spinner_shooting,
    weaver_sprite, weaver_movement, weaver_shooting
};

#endif	/* ENEMYTYPES_H */

