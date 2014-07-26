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
    virtual ~Enemy();
    void init(int8_t x, int8_t y, ENEMY_TYPE type);
    void draw();
    void update();
    boolean isDead();
    HitBox getCollisionBox();
    void hit();
private:
    int8_t x;
    int8_t y;
    ENEMY_TYPE type;
};

#endif	/* ENEMY_H */

