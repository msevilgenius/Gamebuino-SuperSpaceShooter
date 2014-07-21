/* 
 * File:   Player.h
 * Author: Michael
 *
 * Created on 21 July 2014, 19:21
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include <Gamebuino.h>
#include "Bullets.h"
#include "globals.h"

class Player {
public:
    Player();
    virtual ~Player();
    void shoot();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void draw();
private:
    int8_t x;
    int8_t y;
    int8_t bullet_speed;
    int8_t last_bullet_time;
    byte abilities;
};

#endif	/* PLAYER_H */

