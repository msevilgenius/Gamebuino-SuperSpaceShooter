/* 
 * File:   globals.h
 * Author: Michael
 *
 * Created on 21 July 2014, 20:40
 */

#ifndef GLOBALS_H
#define	GLOBALS_H
#include <Gamebuino.h>

enum DIRECTION {DIR_N, DIR_NE, DIR_E, DIR_SE, DIR_S, DIR_SW, DIR_W, DIR_NW};
enum ENEMY_TYPE {DEAD, BASIC};

typedef struct {
    int8_t x;
    int8_t y;
    int8_t w;
    int8_t h;
}HitBox;
    
#define MAX_PLAYER_BULLETS 25
#define MAX_ENEMY_BULLETS 70
#define BULLET_SIZE 3
#define DIAG_BULLET_SIZE 2
#define MAX_ENEMIES 10

#define SRC_PLAYER 0
#define SRC_ENEMY 1

#endif	/* GLOBALS_H */

