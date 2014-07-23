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
    Bullet enemyBullets[MAX_ENEMY_BULLETS];
    Bullet playerBullets[MAX_PLAYER_BULLETS];
public:
    BulletManager();
    virtual ~BulletManager();
    void playerCreateBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed);
    void enemyCreateBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed);
    void updateAndDraw();
};

#endif	/* BULLETMANAGER_H */

