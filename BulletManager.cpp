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

void BulletManager::createBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed){
    // not terribly efficient way to find an inactive bullet
    int8_t i = 0;
    while(!bullets[i].isDead() && i < MAX_BULLETS-1){
        i++;
    }
    Bullet newBullet(x, y, dir, speed);
    bullets[i] = newBullet;
}

void BulletManager::updateAndDraw(){
    for(int8_t i = 0;i < MAX_BULLETS;i++){
        if (!bullets[i].isDead()){
            bullets[i].update();
        }
    }
}