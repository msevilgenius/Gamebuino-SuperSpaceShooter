/* 
 * File:   Bullets.h
 * Author: Michael
 *
 * Created on 21 July 2014, 20:09
 */

#ifndef BULLETS_H
#define	BULLETS_H

#include "Bullet.h"
#include "globals.h"

class Bullets {
private:
    Bullet bullets[MAX_BULLETS];
public:
    Bullets();
    virtual ~Bullets();
    void createBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed);
    void updateAndDraw();

};

#endif	/* BULLETS_H */

