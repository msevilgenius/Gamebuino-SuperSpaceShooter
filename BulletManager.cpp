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

void BulletManager::enemyCreateBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed){
    // not terribly efficient way to find an inactive bullet
    int8_t i = 0;
    while(!enemyBullets[i].isDead() && i < MAX_ENEMY_BULLETS-1){
        i++;
    }
    Bullet newBullet(x, y, dir, speed, SRC_ENEMY);
    enemyBullets[i] = newBullet;
}

void BulletManager::playerCreateBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed){
    // not terribly efficient way to find an inactive bullet
    int8_t i = 0;
    while(!playerBullets[i].isDead() && i < MAX_PLAYER_BULLETS-1){
        i++;
    }
    Bullet newBullet(x, y, dir, speed, SRC_PLAYER);
    playerBullets[i] = newBullet;
}

void BulletManager::updateAndDraw(){
    for(int8_t i = 0;i < MAX_PLAYER_BULLETS;i++){
        if (!playerBullets[i].isDead()){
            playerBullets[i].update();
        }
    }
    for(int8_t i = 0;i < MAX_PLAYER_BULLETS;i++){
        if (!enemyBullets[i].isDead()){
            enemyBullets[i].update();
        }
    }
}