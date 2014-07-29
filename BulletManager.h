/* 
 * File:   BulletManager.h
 * Author: Michael
 *
 * Created on 21 July 2014, 20:09
 */

#ifndef BULLETMANAGER_H
#define	BULLETMANAGER_H

#include "Bullet.h"
#include "globals.h"

class BulletManager {
private:
    Bullet bullets[MAX_BULLETS];
public:
    BulletManager();
    virtual ~BulletManager();
    void reset();
    void createBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed, byte src);
    void updateAndDraw();
};

#endif	/* BULLETMANAGER_H */

