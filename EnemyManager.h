/* 
 * File:   EnemyManager.h
 * Author: Michael
 *
 * Created on 22 July 2014, 12:05
 */

#ifndef ENEMYMANAGER_H
#define	ENEMYMANAGER_H

#include "globals.h"
#include "Enemy.h"

class EnemyManager {
public:
    EnemyManager();
    virtual ~EnemyManager();
    void reset();
    void update();
    void createEnemy(int8_t x, int8_t y, ENEMY_TYPE type);
    bool TestShot(int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t x3, int8_t y3);
private:
    Enemy enemies[MAX_ENEMIES];
};

#endif	/* ENEMYMANAGER_H */

