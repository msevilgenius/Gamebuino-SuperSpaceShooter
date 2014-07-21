/* 
 * File:   Bullet.h
 * Author: Michael
 *
 * Created on 21 July 2014, 20:08
 */

#ifndef BULLET_H
#define	BULLET_H

#include <Gamebuino.h>
#include "globals.h"


class Bullet {
public:
    Bullet();
    Bullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed);
    virtual ~Bullet();
    void update();
    bool isDead();
private:
    int8_t x;
    int8_t y;
    int8_t speed;
    DIRECTION direction;
    uint8_t age;

};

#endif	/* BULLET_H */

