/* 
 * File:   Enemy.h
 * Author: Michael
 *
 * Created on 22 July 2014, 09:10
 */

#ifndef ENEMY_H
#define	ENEMY_H

#include "Globals.h"
#include "BulletManager.h"
#include <Gamebuino.h>

class Enemy {
public:
    Enemy();
    Enemy(int8_t x, int8_t y, ENEMY_TYPE type);
    Enemy(const Enemy& orig);
    virtual ~Enemy();
    void draw();
    void update();
    boolean isDead();
private:
    int8_t x;
    int8_t y;
    ENEMY_TYPE type;
};

#endif	/* ENEMY_H */

