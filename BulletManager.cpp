/* 
 * File:   Bullets.cpp
 * Author: Michael
 * 
 * Created on 21 July 2014, 20:09
 */

#include "BulletManager.h"

BulletManager::BulletManager() {
}

BulletManager::~BulletManager() {
}

void BulletManager::createBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed, byte src){
    // not terribly efficient way to find an inactive bullet
    // looks through array of bullets until it finds one not in existance, or just the last one in the array
    int8_t i = 0;
    while(!bullets[i].isDead() && i < MAX_BULLETS-1){
        i++;
    }
    bullets[i].init(x, y, dir, speed, src);
}



void BulletManager::updateAndDraw(){
    for(int8_t i = 0;i < MAX_BULLETS;i++){
        if (!bullets[i].isDead()){
            bullets[i].update();
        }
    }
}