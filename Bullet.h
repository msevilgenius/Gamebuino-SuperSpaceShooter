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
    virtual ~Bullet();
    void init(int8_t x, int8_t y, DIRECTION dir, int8_t speed, byte source); // source = who shot the bullet
    void update();
    bool isDead();
private:
    void updateN();
    void updateNE();
    void updateE();
    void updateSE();
    void updateS();
    void updateSW();
    void updateW();
    void updateNW();
    void testCollision(int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t x3, int8_t y3);// co-ords of pixels of bullet
    byte source;
    int8_t x;
    int8_t y;
    int8_t speed;
    DIRECTION direction;
};

#endif	/* BULLET_H */

